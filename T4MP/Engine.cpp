#define _WINSOCKAPI_ 
#include "Engine.h"
#include "Hook.h"
#include "t4net.h"
#include <windows.h>
#include <stdio.h>

T4Network t4net;
TurokEngine tengine;

bool spawned = false;
DWORD screen_effect_ret = 0x00000000; 
__declspec(naked) void screen_effect_osd() // Fix crash when new player is taking damage, since we don't have a camera for them ecx here will be null we need to account for that.
{
	__asm
	{
		pop screen_effect_ret;
		
		PUSHAD
		PUSHFD
		
		cmp ecx,0
		jz ret_null

		POPFD
		POPAD
		
		mov eax,[esp+4]
		test eax,eax
		push screen_effect_ret //return normally
		ret
			

		ret_null:
			POPFD
			POPAD
			push 0x004EE815 //return where I want instead
			ret
	}
}

/*
	We need to control the initial value set to the loop as well.
*/
DWORD osd_health_fix_ret_2 = 0;
__declspec(naked) void osd_health_fix2()
{
	__asm {
		pop osd_health_fix_ret_2
		/*
		.text:0050E293                 mov     edi, [ebp+0E8h]
		.text:0050E299                 cmp     edi, [ebp+0ECh]
		.text:0050E29F                 jz      short loc_50E2F5
		*/
		mov edi,[ebp+0xE8]
		check_osd:
			mov ecx,[edi] // we can use ecx and not have to restore it because the operation just after this overwrites it
			mov ecx,[ecx]
			cmp ecx,0x00658CE0
			jz avoid_dmplayer
			push osd_health_fix_ret_2
			ret

		avoid_dmplayer:
			add edi, 4
			jmp check_osd

		
	}
}

/*
	We control the loop and attempt to skip the things related to the additional players,
	will probably need to add additional entries here for other screen effects but it should fix at least the health and ammo displays.
*/
DWORD osd_health_fix_ret = 0;
__declspec(naked) void osd_health_fix() 
{
	__asm {
		pop osd_health_fix_ret;	
		add edi,4 // we noped this and moved it up
		PUSHAD
		PUSHFD
		
		check_osd:
			mov eax, [ebp + 0x0EC]
			cmp eax, edi // if edi has reached the end let the game handle it.
			jz return_normal

			mov eax, [edi] 
			cmp eax,0 // if eax is 0 return to function let game handle it.
			jz return_normal
			
			
			mov eax, [eax] // if the pointer is good grab the data
			cmp eax, 0x00658CE0 // compare it against our known 'bad'
			jz avoid_dmplayer // avoid this player's data if the compare matches
			jmp return_normal // otherwise return to normal game operation

	
			/*
				.text:0050E2E7 mov     eax, [ebp + 0ECh]
				.text : 0050E2ED add     edi, 4 // we're nopping this
				.text : 0050E2F0 cmp     edi, eax
				.text : 0050E2F2 jnz     short loc_50E2A8
			*/

		return_normal:
			POPFD
			POPAD

			mov eax, [ebp + 0x0EC]
			push osd_health_fix_ret
			ret
	
		avoid_dmplayer:
			add edi,4
			jmp check_osd


	}
}


/* Currently this is not in-use */
DWORD nPlayerPTR = 0x00000000;
DWORD lPlayer = 0x00000000;
DWORD CameraLoop1_Ret = 0;
DWORD CameraLoop2_Ret = 0;

__declspec(naked) void CameraFuncLoop2() // make sure we only ever render the first player's stuff.
{ // see camera1 loop for comments on flow.
	__asm {
		pop CameraLoop2_Ret

		PUSHAD
		PUSHFD

		cmp nPlayerPTR, 0
		jz end

		mov edi, [ebp - 4]


		mov eax, 0x006B52E4
		mov eax, [eax]
		cmp eax, 0
		jz end

		add eax, 0xC0
		mov edx, [eax]
		cmp edx, 0
		jz end

		mov ebx, [edx]
		cmp ebx, 0
		jz end

		cmp ebx, edi
		jz end

		POPFD
		POPAD
		push 0x0050F91E
		ret

		end:
			mov lPlayer, ebx
			POPFD
			POPAD
			mov edi, [ebp - 4]
			cmp[edi + 0x1E], bl
			push CameraLoop2_Ret
			ret

	}

}

__declspec(naked) void CameraFuncLoop1() // make sure we only render the 1st player's stuff.
{

	__asm
	{
		pop CameraLoop1_Ret

		PUSHAD
		PUSHFD
		
		cmp nPlayerPTR,0
		jz end

		mov edi, [ebp - 4]


		mov eax, 0x006B52E4
		mov eax,[eax]
		cmp eax, 0
		jz end
	
		add eax, 0xC0
		mov edx, [eax]
		cmp edx,0
		jz end
		
		mov ebx,[edx] 
		cmp ebx,0
		jz end

		cmp ebx,edi // if the pointer of what we're trying to render matches the pointer of our first player continue.
		jz end

		POPFD
		POPAD
		//mov [edi+0x1E],1
		push 0x0050F87E // else push a different return value to the stack and force the loop onto the next entry.
		ret

	end:
		mov lPlayer, ebx // store local player for future use.
		POPFD
		POPAD
		mov edi,[ebp-4] // restore overwritten code.
		cmp [edi+0x1E],bl
		push CameraLoop1_Ret
		ret
	}

}

/* 

	Unknown related to camera but not sure what exactly it's handling... 
	I seemed to assume it would handle the HUD but the HUD text is still there.

	Will require additional investigation if it's required at all.

*/
typedef void(__stdcall *tcamera_hook3)(void* thisptr, BlendedCamera* pCamera);
tcamera_hook3 pcamera_hook3;

void __stdcall camera_hook3(void* thisptr, BlendedCamera* pCamera) // third camera fix, this one should take care of additional hud bullshit.
{
	T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
	BlendedCamera* local_player = 0;

		if (TurokEngine->pT4Game)
			if (TurokEngine->pT4Game->pEngineObjects)
				if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0])
					local_player = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0];

	if (local_player != pCamera)
		return;
		
	return pcamera_hook3(thisptr,pCamera);
}


/* This hook is to specifically get rid of the "You are dead message" */
typedef int(__stdcall *tdeath_message_hook)(void* thisptr);
tdeath_message_hook pdeath_message_hook;

int __stdcall death_message(void *thisptr)
{
	DMPlayer* localplayer = tengine.GetDMPlayer(0); // Simplify.

	if (localplayer != 0)
	{
		if (thisptr != localplayer)
			return 0;
	}

	return pdeath_message_hook(thisptr);
}


/* Input polling, this is looped per player or object in order to determine if input or actions are being applied to it. */
typedef void(__stdcall *tinput_query)(void *thisptr, DWORD pInputPointer);
tinput_query pinput_query;

void __stdcall input_query(void *thisptr, DWORD pInputPointer)
{	
	
	/* If the player is not the local player do not process their input. */
	DMPlayer* localplayer = tengine.GetDMPlayer(0);
	if (localplayer != 0)
	{
		if (localplayer != (DMPlayer*)pInputPointer)
		{
			return;
		}
	}
	
	t4net.ProcessMessage();

	pinput_query(thisptr, pInputPointer);

	if (t4net.server)
	{
		t4net.SendSnapShot();
	}
	else 
	{
		if (t4net.connected == true)
			t4net.SendPlayerSnapShot();
		else
			t4net.ConnectToServer();
	}

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		if (spawned == false)
		{
			tengine.SpawnPlayer();
			spawned = true;
		}
	}

	return;
}



/* The actual level load actor system, where the level itself loads each individual actor within it. */
typedef int(__stdcall *tlevel_load_actor)(void *thisptr, char* a2, int a3, int a4);
tlevel_load_actor plevel_load_actor;

int __stdcall level_load_actor(void* thisptr, char* a2, int a3, int a4)
{
	return plevel_load_actor(thisptr, a2, a3, a4);
}

/*  One of the initial calls after initiating a spawn, I believe this actually handles each objects constructor */
typedef int(__stdcall *tconstruct_actor)(void* thisptr, char* object_name, char* object_path);
tconstruct_actor pconstruct_actor;

int __stdcall construct_actor(void* thisptr, char* object_name, char* object_path)
{


	int ret = pconstruct_actor(thisptr, object_name, object_path);

	if (!strcmp(object_name, "DMPlayer"))
	{
		nPlayerPTR = (DWORD)ret;
	}


	/*
		So we know that a player is being spawned when the "Weapon" is called", and t4net.connected will stop us from running this multiple times.

		This is a horrible way to do this but it'll do for now, we also aren't sending any kind of ack ack from the server, so if the packet gets dropped we're a little screwed.
	*/

	if (!strcmp(object_name, "Weapon") && !strcmp(object_path,"y:\\Data\\Actors\\Weapons\\WarClub\\WarClub.atr") && t4net.connected == false && t4net.server == false) 
	{
		t4net.ConnectToServer(); 
	}

	
	return ret;
}



/* 
	When a second player is spawned the pause menu would crash due to a pointer being 0.
	
	This is in place as an attempt to fix that, but may no longer be needed depending on how this works. 

	The reason I believe it may no longer be needed is the player object being removed from several render loops.

*/
typedef char(__stdcall *tpause_menu)(void* thisptr, int a2);
tpause_menu ppause_menu;

char __stdcall pause_menu(void* thisptr, int a2)
{
	if (thisptr == 0)
		return 0;


	return ppause_menu(thisptr, a2);
}



/*	

	All of the below are related to fixes for crashes upon a player dying.

	Some of these are currently causing problems see death2 for instance.
	
	I should probably do additional research into this to determine if it's also related in any way to the current random crashes.

*/

typedef void(__stdcall *tplayer_death)(void* thisptr);
tplayer_death pplayer_death;

void __stdcall player_death(void* thisptr)
{
	if (thisptr == 0)
		return;

	return pplayer_death(thisptr);
}

typedef void(__stdcall *tplayer_death2)(void* thisptr, int a2);
tplayer_death2 pplayer_death2;

void __stdcall player_death2(void* thisptr, int a2)
{
	return; // this will disable the indicator for the death helm, but trying to return normally crashes so we'll accept it for now.
}

typedef char(__stdcall *tplayer_death3)(void* thisptr, int a2);
tplayer_death3 pplayer_death3;

char __stdcall player_death3(void* thisptr, int a2)
{
	if (thisptr == 0)
		return 0;

	return pplayer_death3(thisptr, a2);
}

typedef void(__stdcall *tplayer_death4)(void* thisptr, float a2);
tplayer_death4 pplayer_death4;

void __stdcall player_death4(void* thisptr, float a2)
{
	if (thisptr == 0)
		return;

	if (!*(DWORD*)((BYTE*)thisptr + 0x1B20))
		return;


	return pplayer_death4(thisptr, a2);
}


/* Self explanatory, was implemented as a way to fix a crash found while players were respawning... */
typedef int(__stdcall *tplayer_respawn_crashfix)(void* thisptr);
tplayer_respawn_crashfix pplayer_respawn_crashfix;

int __stdcall player_respawn_crashfix(void* thisptr)
{

	if (thisptr == 0)
		return 0;

	if (!*(DWORD*)((BYTE*)thisptr + 0x1B14))
		return 0;

	return pplayer_respawn_crashfix(thisptr);
}


/* 
	Literally a method used to spawn objects in the engine.
	Spawning players utilizes this, but typically it's only used for pickups or other things with a static location.

	In theory this could be used to sync specific power ups which are usually spawned with RNG (Speed Increase, Health Increase, Damage Increase, etc).

*/
typedef int(__stdcall *tspawn_object)(void* thisptr, int a2, char* object_name, char* object_path, Vector3* pos_struct, int a6);
tspawn_object pspawn_object;

int __stdcall spawn_object_engine(void* thisptr, int a2, char* object_name, char* object_path, Vector3* pos_struct, int a6)
{
	
	int ret = pspawn_object(thisptr, a2, object_name, object_path, pos_struct, a6);
	
	return ret;
}

/* 
	The game history functions /data/history/*.hst are all loaded here.

	Multiplayerjoin.hst is hooked to make sure the second  player never joins the game and as a result their player is not spawned, and there is no second screen.

	Options.hst is hooked to make sure AutoAim is disabled as it will cause unfair host advantage and major de-sync for clients believing they've done damage.

	I'm going to want to document this further to force map loading of specific maps and force the game into the "MP" mode.

	UPDATE: The new plan is not to force load specific maps through code but use the boot sequence to do it, the launcher will handle teling the game which maps to load,
	hooks will be created to load .t4mp versions of specific files.
*/


typedef int(__stdcall *tload_history)(void *thisptr, char* hist_file);
tload_history pload_history;

int __stdcall load_history(void* thisptr, char* hist_file)
{
	int ret = pload_history(thisptr, hist_file);

	if (!strcmp("$\\Data\\History\\MultiPlayerJoin.hst", hist_file))
	{
		DWORD player_area = *(DWORD*)(ret + 0x04);
		BYTE *player_2_joined = (BYTE*)(player_area + 0x68);
		*player_2_joined = 0;
	}

	if (!strcmp("$\\Data\\History\\Options.hst", hist_file))
	{
		DWORD data_area = *(DWORD*)(ret + 0x04);
		*(BYTE*)(data_area) = 0; // turn auto aim off.
	}

	return ret;
}


/* Used in a ton of places in order to get a valid DM Player pointer based on index. */
DMPlayer* TurokEngine::GetDMPlayer(int index)
{
	T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
	if (TurokEngine->pT4Game)
		if (TurokEngine->pT4Game->pEngineObjects)
			if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[index])
				if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[index]->pActor)
				{
					if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[index]->pActor->pDMPlayer)
						return TurokEngine->pT4Game->pEngineObjects->pCameraArray[index]->pActor->pDMPlayer;
				}
				else
				{
					return (DMPlayer*)TurokEngine->pT4Game->pEngineObjects->pCameraArray[index]->pPlayer;
				}


	return 0;
}


/* Self Explanatory, the initial press of a fire button (tab or left mouse down) previous to release or hold */
typedef void(__stdcall *tFireWeapon)(DMPlayer *pThis, int a1, int a2);
tFireWeapon pFireWeapon;

void __stdcall FireWeapon(DMPlayer* pDMPlayer, int a1, int a2)
{
	TurokEngine tengine;
	if (pDMPlayer == tengine.GetDMPlayer(0) && t4net.fire_set == false )//&& pDMPlayer->pHealth->Current > 0.0f)
	{
		t4net.fire_set = true;

	//	if (!t4net.server)
	//		return;
	
	}

	return pFireWeapon(pDMPlayer, a2, a2);
}


/* Again self explanatory, mapping of release fire calls. HeldTime is total time Held down calculated from HeldFire. */
typedef int(__stdcall *tReleaseFire)(DMPlayer* pThis, float HeldTime);
tReleaseFire pReleaseFire;

int __stdcall ReleaseFire(DMPlayer* pDMPlayer, float HeldTime)
{
	TurokEngine tengine;

	if (pDMPlayer == tengine.GetDMPlayer(0) && t4net.fire_release == false )//&& pDMPlayer->pHealth->Current > 0.0f)
	{
		t4net.fire_release_time = HeldTime;
		t4net.fire_release = true;
		
	//	if(!t4net.server)
	//		return 0;
	}

	return pReleaseFire(pDMPlayer, HeldTime);
}


/* Self Explanatory, hook of Holding fire calls... a2 is unknown*/
typedef int(__stdcall *tHoldFire)(DMPlayer* pDMPlayer, float HeldTime, int a2);
tHoldFire pHoldFire;

int __stdcall HoldFire(DMPlayer* pDMPlayer, float HeldTime, int a2)
{
	TurokEngine tengine;
	if (pDMPlayer == tengine.GetDMPlayer(0))
	{
		t4net.fire_hold_time = HeldTime;
		t4net.fire_hold = true;
	}

	return pHoldFire(pDMPlayer, HeldTime, a2);
}



/*
	These are engine functions used for switching weapons and checking if a weapon is available before attempting to switch to it.
	
	Due to the fact these are not hooked, I'm curious if the 3rd parameter is responsible for weapon modifiers...

	Weapon modifiers can be found by simply breaking on input query and following the first call though.
*/
typedef int(__thiscall *tWeaponCheck)(void* Pthis, int WeaponID, int Unk);
tWeaponCheck pWeaponCheck = (tWeaponCheck)(0x004E3720);

typedef int(__thiscall *tWeaponSwitch)(void* Pthis, int WeaponID, int Unk);
tWeaponSwitch pWeaponSwitch = (tWeaponSwitch)(0x004E3AF0);

void SwitchWeapon(void* WeaponPointer, int WeaponID)
{

	if (pWeaponCheck(WeaponPointer, WeaponID, 0))
	{
		pWeaponSwitch(WeaponPointer, WeaponID, 0);
	}

}


/* 
	This is the function responsible for damaging players.
	Any attempt at detouring this normally has not worked well.


*/
DWORD DamagePlayer_Ret = 0x00;
DWORD DamagedPlayer = 0x00;
__declspec(naked) void DamagePlayer() 
{
	__asm {
		pop DamagePlayer_Ret

		PUSHAD
		PUSHFD
	
	}

	/* 
		If we're not the server we update the pointer of the damage to be 0 so that the client applies no damage.
		This is a problem, because the damage function is also used to determine if an client should trigger events.

		Need some way to check the pointer which is being damaged and to determine if it's a player or not.
	*/
	if (!t4net.server)
	{
		__asm 
		{
			POPFD
			POPAD
			or dword ptr[ecx+0x28],2
			mov eax, [esp + 4]
			mov [eax], 0x00000000
			mov eax, 0x0051E570
			jmp eax
			push DamagePlayer_Ret
			ret
		}
	}

	__asm
	{
		POPFD
		POPAD

		or dword ptr[ecx+0x28],2
		mov eax, 0x0051E570
		jmp eax
		push DamagePlayer_Ret
		ret
	}

}



/*
	This hooks into the function that's used to kill players in the game.

	It may be better to do a vtable detour rather than a codecave for this one, as it's possible this is causing crashes.

	The real problem is getting the internal function to pass parameters properly to the real function.
*/

DWORD KillPlayer_Ret;
DWORD KillPlayer_Ret2;
DMPlayer* KilledPlayer = 0x00;
int death_type = 0;

__declspec(naked) void KillPlayer()
{
	__asm {
		pop KillPlayer_Ret
		PUSHAD
		PUSHFD
		mov KilledPlayer, ecx
		mov eax, [esp+0x2C]
		mov death_type, eax
		
	}

	if (t4net.server)
	{
		TurokEngine tengine;
		if (tengine.GetDMPlayer(0) == KilledPlayer)
		{
			t4net.death_type = death_type;
		}
		else
		{
			for (NetworkPlayer* player : t4net.netplayers)
			{
				if (player->PlayerObject == KilledPlayer)
					player->death_type = death_type;
			}
		}
	}

		__asm
		{
			POPFD
			POPAD
			push 0x0FFFFFFFF
			push 0x0062254B
			push KillPlayer_Ret
			ret
		}
}




void TurokEngine::UnCrouch(DMPlayer* thisptr)
{
	__asm
	{
		PUSHAD
		PUSHFD
		push 0
		mov ecx, thisptr
		mov eax, 0x4CFB90
		call eax
		POPFD
		POPAD
	}

}

/* Because hooking the death function has proved itself difficult, 
   In order to prevent the client from killing people I've hooked a function used just before to determine if their health has reached 0.
   
   On a client this will always tell them their health is not 0 and should not be responsible for killing them.
   */
typedef BOOL(__stdcall *tIsDead)(DMPlayer* pDMPlayer);
tIsDead pIsDead;

BOOL __stdcall IsDead(DMPlayer* pDMPlayer)
{
	
	if (t4net.server)
		return pIsDead(pDMPlayer);
	else
		return FALSE;

}


typedef char*(__stdcall *tload_actor_instance)(void* pThis, char* a2, int a3);
tload_actor_instance pload_actor_instance;

char* __stdcall load_actor_instance(void* pThis, char* ati_path, int a3)
{

	/*
	* The first instance file loaded is Begin.ati, 
	*  We replace this with our modified multiplayer join; this way we can force load MP into the map specified by the history file.
	*/
	if (strstr(ati_path, "Begin.ati"))
	{
		strcpy(ati_path, "$\\T4MP\\multiplayerjoin.ati");
	}

	return pload_actor_instance(pThis, ati_path, a3);
}

typedef int(__stdcall *tPickupCrash)(void* pScreenPtr, int a2);
tPickupCrash pPickupCrash;

/* Fixes jump boots pickup, disables it from attempting to add HUD for players other than the local one. */
int __stdcall PickupCrash(void* pScreenPtr, int a2)
{
	if (!pScreenPtr)
		return a2;

	return pPickupCrash(pScreenPtr, a2);
}


/* The rest of these are not necessarily related to pickup, just OSD in general and are to fix crashes or potential crashes */
typedef int(__stdcall *tPickupCrash2)(void* pScreenPtr, int a2);
tPickupCrash2 pPickupCrash2;

int __stdcall PickupCrash2(void* pScreen, int a2)
{
	if (!pScreen)
		return a2;

	return pPickupCrash2(pScreen, a2);
}

typedef int(__stdcall *tPickupCrash3)(void* pScreenPtr, int a2);
tPickupCrash3 pPickupCrash3;

int __stdcall PickupCrash3(void* pScreen, int a2)
{
	if (!pScreen)
		return a2;

	return pPickupCrash3(pScreen, a2);
}


typedef int(__stdcall *tPickupCrash4)(void* pScreenPtr, int a2);
tPickupCrash3 pPickupCrash4;

int __stdcall PickupCrash4(void* pScreen, int a2)
{
	if (!pScreen)
		return a2;

	return pPickupCrash4(pScreen, a2);
}


typedef int(__stdcall *tPickupCrash5)(void* pScreenPtr, int a2);
tPickupCrash5 pPickupCrash5;

int __stdcall PickupCrash5(void* pScreen, int a2)
{
	if (!pScreen)
		return a2;

	return pPickupCrash5(pScreen, a2);
}

typedef int(__stdcall *tPickupCrash6)(void* pScreenPtr, int a2);
tPickupCrash6 pPickupCrash6;

int __stdcall PickupCrash6(void* pScreen, int a2)
{
	if (!pScreen)
		return a2;

	return pPickupCrash6(pScreen, a2);
}


typedef int(__stdcall *tPickupCrash7)(void* pScreenPtr, int a2);
tPickupCrash7 pPickupCrash7;

int __stdcall PickupCrash7(void* pScreen, int a2)
{
	if (!pScreen)
		return a2;

	return pPickupCrash7(pScreen, a2);
}

typedef int(__stdcall *tPickupCrash8)(void* pScreenPtr, int a2);
tPickupCrash8 pPickupCrash8;

int __stdcall PickupCrash8(void* pScreen, int a2)
{
	if (!pScreen)
		return a2;

	return pPickupCrash8(pScreen, a2);
}

typedef void(__stdcall *tPickupText)(void* Unk, void* PlayerPTR);
tPickupText pPickupText;

void __stdcall PickupText(void *Unk, void* PlayerPTR)
{

	return pPickupText(Unk, PlayerPTR);
}


DWORD WeapOrigBytes = 0;

/* Internal function actually responsible for spawning additional players into the game. */
DMPlayer* TurokEngine::SpawnPlayer()
{

	T4Engine * TurokEngine = (T4Engine*)0x6B52E4;

	char *spawn_path = new char[255];
	ZeroMemory(spawn_path, 255);

	sprintf_s(spawn_path, strlen("$/Data/Actors/multiplayer\\Players\\TalSetPlayer\\TalSetPlayer.atr") + 1, "%s", "$/Data/Actors/multiplayer\\Players\\TalSetPlayer\\TalSetPlayer.atr");
	char *spawn_name = new char[20];
	ZeroMemory(spawn_name, 20);

	sprintf_s(spawn_name, strlen("DMPlayer") + 1, "%s", "DMPlayer");

	/* A position must be supplied to the function we're using to create the player so we'll use a random one. */
	Vector3 npos_struct;
	npos_struct.x = 12.0f;
	npos_struct.y = 10.0f;
	npos_struct.z = 5.0f;

	/* 
		We perform various patches when spawning the player, and restore the code after the fact.
		Each one of these patches handles something different, some may be sure the player isn't added to a rendering loop for first person data.

		Others account for potential crashes in relation to OSD/HUD.
	*/

	DWORD dwOld;
	VirtualProtect((BYTE*)0x004DAD49, 1, PAGE_EXECUTE_READWRITE, &dwOld);
	VirtualProtect((BYTE*)0x0050CED2, 4, PAGE_EXECUTE_READWRITE, &dwOld);
	VirtualProtect((BYTE*)0x00510AF9, 4, PAGE_EXECUTE_READWRITE, &dwOld);


	BYTE OrigByte = *(BYTE*)0x004DAD49;
	DWORD OrigBytes = *(DWORD*)0x0050CED2; // Camera/screen effect array increment pointer
	DWORD WeapOrigBytes = *(DWORD*)0x00510AF9; // Camera Loop 1, this should fix without a cave.

	*(BYTE*)0x004DAD49 = 0xEB; // disable OSD weapon related

	/* 
		Nop the increment for the camera array pointer. 
		This should stop the game from doing things like displaying water screen effects for everyone.
	*/
	memset((PVOID)0x0050CED2, 0x90, 4); 
	
	/* 
	   In this same area there's a camera that can be stopped from initializing and it would probably remove the need for the other OSD fix, however...
	   This also results in there being issues with what appears to be first person animations trying to get called for the weapon
	 
		.text:004D4E61 jz     short loc_4D4E74 // EB(jmp) on spawn new player

	 */

	memset((PVOID)0x00510AF9, 0x90, 4); // Causes FPS Weapon bug - 0x004D4E27
	
	
	DMPlayer *nPlayer = (DMPlayer*)pspawn_object(TurokEngine->pT4Game, 0, spawn_name, spawn_path, &npos_struct, 0);

	*(BYTE*)0x004DAD49 = OrigByte;
	
	memcpy((PVOID)0x0050CED2, &OrigBytes, 4); // Restore the bytes for the camera array addition.
	memcpy((PVOID)0x00510AF9, &WeapOrigBytes, 4); // Restore original Bytes.

	return nPlayer;
}


/* Apply all of our hooks */
void TurokEngine::SetModHooks()
{
	DWORD dwBack;

	/*
		There's an OSD loop where text gets rendered for all cameras these two codecaves take care of that loop,
		It was possible to determine a specific object type that the additionally spawned players were using and stop the game from rendering data for them.
	*/
	Codecave(0x0050E2E7, osd_health_fix, 4);
	Codecave(0x0050E293, osd_health_fix2, 1);

	pload_history = (tload_history)DetourClassFunc((BYTE*)0x529650, (BYTE*)load_history, 16);

	VirtualProtect(pload_history, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pspawn_object = (tspawn_object)DetourClassFunc((BYTE*)0x5120E0, (BYTE*)spawn_object_engine, 12);

	VirtualProtect(pspawn_object, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pconstruct_actor = (tconstruct_actor)DetourClassFunc((BYTE*)0x50DEE0, (BYTE*)construct_actor, 10);

	VirtualProtect(pconstruct_actor, 4, PAGE_EXECUTE_READWRITE, &dwBack);
	
	pinput_query = (tinput_query)DetourClassFunc((BYTE*)0x4FAA20, (BYTE*)input_query, 10);

	VirtualProtect(pinput_query, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	ppause_menu = (tpause_menu)DetourClassFunc((BYTE*)0x51C640, (BYTE*)pause_menu, 12);
	
	VirtualProtect(ppause_menu, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pplayer_death = (tplayer_death)DetourClassFunc((BYTE*)0x004EEA50, (BYTE*)player_death, 9);

	VirtualProtect(pplayer_death, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pplayer_death2 = (tplayer_death2)DetourClassFunc((BYTE*)0x4EE850, (BYTE*)player_death2, 14);

	VirtualProtect(player_death2, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	/* Possibly no longer needed, requires additional testing */
	//pcamera_hook3 = (tcamera_hook3)DetourClassFunc((BYTE*)0x0050E310, (BYTE*)camera_hook3, 13);

	//VirtualProtect(pcamera_hook3, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pdeath_message_hook = (tdeath_message_hook)DetourClassFunc((BYTE*)0x4DCFC0, (BYTE*)death_message, 13);

	VirtualProtect(pdeath_message_hook, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pplayer_death3 = (tplayer_death3)DetourClassFunc((BYTE*)0x51E3B0, (BYTE*)player_death3, 9);

	VirtualProtect(pplayer_death3, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pplayer_death4 = (tplayer_death4)DetourClassFunc((BYTE*)0x4D9130, (BYTE*)player_death4, 13);

	VirtualProtect(pplayer_death4, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pplayer_respawn_crashfix = (tplayer_respawn_crashfix)DetourClassFunc((BYTE*)0x4D91D0, (BYTE*)player_respawn_crashfix, 12);

	VirtualProtect(pplayer_respawn_crashfix, 4, PAGE_EXECUTE_READWRITE, &dwBack);


	pFireWeapon = (tFireWeapon)DetourClassFunc((BYTE*)0x004DBC70, (BYTE*)FireWeapon, 9);
	
	VirtualProtect(pFireWeapon, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pReleaseFire = (tReleaseFire)DetourClassFunc((BYTE*)0x4D6E40, (BYTE*)ReleaseFire, 15);

	VirtualProtect(pReleaseFire, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pHoldFire = (tHoldFire)DetourClassFunc((BYTE*)0x4D6DF0, (BYTE*)HoldFire, 11);
	
	VirtualProtect(pHoldFire, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pIsDead = (tIsDead)DetourClassFunc((BYTE*)0x00486110, (BYTE*)IsDead, 10);
	
	VirtualProtect(pIsDead, 4, PAGE_EXECUTE_READWRITE, &dwBack);
	
	pPickupCrash = (tPickupCrash)DetourClassFunc((BYTE*)0x004EE7C0, (BYTE*)PickupCrash, 12);

	VirtualProtect(pPickupCrash, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pPickupCrash2 = (tPickupCrash2)DetourClassFunc((BYTE*)0x4EE820, (BYTE*)PickupCrash2, 14);

	VirtualProtect(pPickupCrash2, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pPickupCrash3 = (tPickupCrash3)DetourClassFunc((BYTE*)0x4EE9C0, (BYTE*)PickupCrash3, 10);

	VirtualProtect(pPickupCrash3, 4, PAGE_EXECUTE_READWRITE, &dwBack);
	
	pPickupCrash4 = (tPickupCrash4)DetourClassFunc((BYTE*)0x4EE970, (BYTE*)PickupCrash4, 10);

	VirtualProtect(pPickupCrash4, 4, PAGE_EXECUTE_READWRITE, &dwBack);
	
	pPickupCrash5 = (tPickupCrash5)DetourClassFunc((BYTE*)0x4EE920, (BYTE*)PickupCrash5, 10);

	VirtualProtect(pPickupCrash5, 4, PAGE_EXECUTE_READWRITE, &dwBack);
	
	pPickupCrash6 = (tPickupCrash6)DetourClassFunc((BYTE*)0x4EE8D0, (BYTE*)PickupCrash6, 10);

	VirtualProtect(pPickupCrash6, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pPickupCrash7 = (tPickupCrash7)DetourClassFunc((BYTE*)0x4EEA40, (BYTE*)PickupCrash7, 10);

	VirtualProtect(pPickupCrash7, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pPickupCrash8 = (tPickupCrash8)DetourClassFunc((BYTE*)0x4EEA10, (BYTE*)PickupCrash8, 10);

	VirtualProtect(pPickupCrash8, 4, PAGE_EXECUTE_READWRITE, &dwBack);
	

	/* Because I was able to remove the player from the array of cameras/render loop this should no longer be needed. */
	//Codecave(0x0050F850, CameraFuncLoop1, 1);
	//Codecave(0x0050F8F0, CameraFuncLoop2, 1);


	Codecave(0x004EE7F0, screen_effect_osd, 1);
	Codecave(0x004E08B0, DamagePlayer, 4);
	Codecave(0x004DE1B0, KillPlayer, 2);

	/* Hook the level load sequence so we can force the game into multiplayer automatically for the launcher */
	pload_actor_instance = (tload_actor_instance)DetourClassFunc((BYTE*)0x00512AF0, (BYTE*)load_actor_instance, 8);
	VirtualProtect(pload_actor_instance, 4, PAGE_EXECUTE_READWRITE, &dwBack);


	t4net.Initalize();
	
}