#define _WINSOCKAPI_ 
#include "Engine.h"
#include "Hook.h"
#include "t4net.h"
#include <windows.h>
#include <stdio.h>

T4Network t4net;


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

typedef int(__stdcall *tdeath_message_hook)(void* thisptr);
tdeath_message_hook pdeath_message_hook;

int __stdcall death_message(void *thisptr)
{
	T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
	Player* localplayer = 0;

	if (TurokEngine->pT4Game)
		if (TurokEngine->pT4Game->pEngineObjects)
			if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0])
				if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pPlayer)
					localplayer = (Player*)TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pPlayer; // use pPlayer instead of DMPlayer as it exists even when dead.

	if (localplayer != 0)
	{
		if (thisptr != localplayer)
			return 0;
	}

	return pdeath_message_hook(thisptr);
}

typedef void(__stdcall *tinput_query)(void *thisptr, DWORD pInputPointer);
tinput_query pinput_query;

void __stdcall input_query(void *thisptr, DWORD pInputPointer)
{
	if (lPlayer != 0) // lPlayer populates in the camera function, once the camera is running we know the player is fully spawned and we can start to deal with input.
	{
		T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
		Player* localplayer = 0;

		//There's probably a better way to take care of this...
		if (TurokEngine->pT4Game)
			if (TurokEngine->pT4Game->pEngineObjects)
				if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0])
					if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pPlayer)
						localplayer = (Player*)TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pPlayer; // use pPlayer instead of DMPlayer as it exists even when dead.

		if (localplayer != 0)
		{
			if (localplayer != (Player*)pInputPointer)
			{
				return;
			}
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

	return;
}


typedef int(__stdcall *tlevel_load_actor)(void *thisptr, char* a2, int a3, int a4);
tlevel_load_actor plevel_load_actor;

int __stdcall level_load_actor(void* thisptr, char* a2, int a3, int a4)
{
	return plevel_load_actor(thisptr, a2, a3, a4);
}

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


typedef char(__stdcall *tpause_menu)(void* thisptr, int a2);
tpause_menu ppause_menu;

char __stdcall pause_menu(void* thisptr, int a2)
{
	if (thisptr == 0)
		return 1;
	return ppause_menu(thisptr, a2);
}

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
	if (thisptr == 0)
		return;
	return pplayer_death2(thisptr, a2);
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

typedef int(__stdcall *tspawn_object)(void* thisptr, int a2, char* object_name, char* object_path, Vector3* pos_struct, int a6);
tspawn_object pspawn_object;

int __stdcall spawn_object_engine(void* thisptr, int a2, char* object_name, char* object_path, Vector3* pos_struct, int a6)
{
	
	int ret = pspawn_object(thisptr, a2, object_name, object_path, pos_struct, a6);
	
	return ret;
}

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

	return ret;
}
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

typedef void(__stdcall *tFireWeapon)(DMPlayer *pThis, int a1, int a2);
tFireWeapon pFireWeapon;

void __stdcall FireWeapon(DMPlayer* pDMPlayer, int a1, int a2)
{
	TurokEngine tengine;
	if (pDMPlayer == tengine.GetDMPlayer(0) && t4net.fire_set == false && pDMPlayer->pHealth->Current > 0.0f)
	{
		t4net.fire_set = true;
		
		if(!t4net.server)
			return;
	}

	return pFireWeapon(pDMPlayer, a2, a2);
}

typedef int(__stdcall *tReleaseFire)(DMPlayer* pThis, float HeldTime);
tReleaseFire pReleaseFire;

int __stdcall ReleaseFire(DMPlayer* pDMPlayer, float HeldTime)
{
	TurokEngine tengine;


	if (pDMPlayer == tengine.GetDMPlayer(0) && t4net.fire_release == false && pDMPlayer->pHealth->Current > 0.0f)
	{
		t4net.fire_release_time = HeldTime;
		t4net.fire_release = true;
		
		if(!t4net.server)
			return 0;
	}

	return pReleaseFire(pDMPlayer, HeldTime);
}

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

typedef void(__thiscall *tApplyDamage)(void* pThis, float* Damage_Amount, int Unk);
//tApplyDamage pApplyDamage = (tApplyDamage)(0x0051E570);
tApplyDamage pApplyDamage = (tApplyDamage)(0x004D7A50);

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


//Detouring this has proven to be a bitch so it's code-caved instead.
DWORD DamagePlayer_Ret = 0x00;
DWORD DamagedPlayer = 0x00;
__declspec(naked) void DamagePlayer() 
{
	__asm {
		pop DamagePlayer_Ret

		PUSHAD
		PUSHFD
	
	}

	if (!t4net.server)
	{
		__asm 
		{
			POPFD
			POPAD
			or dword ptr[ecx+0x28],2
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


//In the future this will include the model and such, we also need to be sure players are spawning at specific positions, or transfer positions from server snapshots.
//It's probably best to hook the spawnpoint routine so we can sync spawning.

DMPlayer* TurokEngine::SpawnPlayer()
{

	T4Engine * TurokEngine = (T4Engine*)0x6B52E4;

	char *spawn_path = new char[255];
	ZeroMemory(spawn_path, 255);

	sprintf_s(spawn_path, strlen("$/Data/Actors/multiplayer\\players\\workerplayer\\workerplayer.atr") + 1, "%s", "$/Data/Actors/multiplayer\\players\\workerplayer\\workerplayer.atr");

	char *spawn_name = new char[20];
	ZeroMemory(spawn_name, 20);

	sprintf_s(spawn_name, strlen("DMPlayer") + 1, "%s", "DMPlayer");

	Vector3 npos_struct;
	npos_struct.x = 12.0f;
	npos_struct.y = 10.0f;
	npos_struct.z = 5.0f;

	DWORD dwOld;
	VirtualProtect((BYTE*)0x004DAD49, 1, PAGE_EXECUTE_READWRITE, &dwOld);

	BYTE OrigByte = *(BYTE*)0x004DAD49;
	*(BYTE*)0x004DAD49 = 0xEB;

	DMPlayer *nPlayer = (DMPlayer*)pspawn_object(TurokEngine->pT4Game, 0, spawn_name, spawn_path, &npos_struct, 0);

	*(BYTE*)0x004DAD49 = OrigByte;

	return nPlayer;
}


void TurokEngine::SetModHooks()
{
	DWORD dwBack;

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

	pplayer_death2 = (tplayer_death2)DetourClassFunc((BYTE*)0x4EE850, (BYTE*)player_death2, 8);

	VirtualProtect(player_death2, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	pcamera_hook3 = (tcamera_hook3)DetourClassFunc((BYTE*)0x0050E310, (BYTE*)camera_hook3, 13);

	VirtualProtect(pcamera_hook3, 4, PAGE_EXECUTE_READWRITE, &dwBack);

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

	

	Codecave(0x0050F850, CameraFuncLoop1, 1);
	Codecave(0x0050F8F0, CameraFuncLoop2, 1);
	Codecave(0x004EE7F0, screen_effect_osd, 1);
	Codecave(0x004E08B0, DamagePlayer, 4);
	Codecave(0x004DE1B0, KillPlayer, 2);

	t4net.Initalize();
	
}