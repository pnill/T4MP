#include "stdafx.h"
#include "Engine.h"
#include "Hook.h"
#include <windows.h>
#include <stdio.h>
#include "T4Engine.h"

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
		push screen_effect_ret
		ret
			

		ret_null:
			POPFD
			POPAD
			push 0x004EE815
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

	if (TurokEngine) // check each property make sure it's valid before trying to access it.
	{
		if (TurokEngine->pT4Game)
			if (TurokEngine->pT4Game->pEngineObjects)
				if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0])
					local_player = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0];
	}

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

	if (TurokEngine) // check each property make sure it's valid before trying to access it.
	{
		if (TurokEngine->pT4Game)
			if (TurokEngine->pT4Game->pEngineObjects)
				if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0])
					if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pPlayer)
						localplayer = (Player*)TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pPlayer; // use pPlayer instead of DMPlayer as it exists even when dead.
	}

	if (localplayer != 0)
	{
		if (thisptr != localplayer)
			return 0;
	}

	return pdeath_message_hook(thisptr);
}

typedef void(__stdcall *tinput_query)(void *thisptr,DWORD pInputPointer);
tinput_query pinput_query;

void __stdcall input_query(void *thisptr, DWORD pInputPointer)
{	
	if (lPlayer != 0) // lPlayer populates in the camera function, once the camera is running we know the player is fully spawned and we can start to deal with input.
	{
		T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
		Player* localplayer = 0;

		//There's probably a better way to take care of this...
		if (TurokEngine) // check each property make sure it's valid before trying to access it.
		{
			if (TurokEngine->pT4Game)
				if (TurokEngine->pT4Game->pEngineObjects)
					if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0])
						if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pPlayer)
							localplayer = (Player*)TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pPlayer; // use pPlayer instead of DMPlayer as it exists even when dead.
		}
	
		if (localplayer != 0)
		{
			if (localplayer != (Player*)pInputPointer)
			{
				return;
			}
		}
	}

	return pinput_query(thisptr, pInputPointer);
}

typedef int(__stdcall *tactor_spawn_1)(void* thisptr);
tactor_spawn_1 pactor_spawn_1;

int __stdcall actor_spawn_1(void* thisptr)
{
	if ((DWORD)thisptr != lPlayer && lPlayer != 0)
		return 0;

	return pactor_spawn_1(thisptr);
}

typedef int(__stdcall *tconstruct_player_weapon)(void *thisptr);
tconstruct_player_weapon pconstruct_player_weapon;

int __stdcall construct_player_weapon(void* thisptr)
{

	printf("construct_player_weapon: %08X\r\n", thisptr);
	if (thisptr == (void*)nPlayerPTR)
	{
		printf("Matched new player, aborting weapon construction.\r\n");
		return 0;
	}
	return pconstruct_player_weapon(thisptr);
}

typedef int(__stdcall *tlevel_load_actor)(void *thisptr, char* a2, int a3, int a4);
tlevel_load_actor plevel_load_actor;

int __stdcall level_load_actor(void* thisptr, char* a2, int a3, int a4)
{
	char text_out[2000];
	memset(text_out, 0x00, 2000);
	sprintf(text_out, "thisptr: %p, a2: %s, a3: %08X, a4: %08X", thisptr, a2, a3, a4);

	FILE* fh = fopen("level_load.txt", "a+");
	fwrite(text_out, strlen(text_out), 1, fh);
	fclose(fh);

	return plevel_load_actor(thisptr, a2, a3, a4);
}

typedef int (__stdcall *tconstruct_actor)(void* thisptr, char* object_name, char* object_path);
tconstruct_actor pconstruct_actor;

int i = 0;
int __stdcall construct_actor(void* thisptr, char* object_name,char* object_path)
{
	FILE* fh = fopen("construct_actor.txt", "a+");

	char text_out[2000];
	memset(text_out, 0x00, 2000);
	sprintf(text_out, "this: %p, object_name: %s, object_path: %s\r\n", thisptr, object_name, object_path);
	fwrite(text_out, strlen(text_out), 1, fh);
	fclose(fh);

	int ret = pconstruct_actor(thisptr, object_name, object_path);
	if (!strcmp(object_name, "DMPlayer"))
	{
		if (i = 1)
		{
			nPlayerPTR = (DWORD)ret;
			printf("nPlayerPTR: %08X - construct_actor\r\n", nPlayerPTR);
		}
		i++;
	}
	//printf("construct_actor: %08X\r\n",ret);

	return ret;
}



void UnCrouch(DMPlayer* thisptr)
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


void FireWeapon()
{

	Player* player1 = 0;


	T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
	if (TurokEngine)
		if (TurokEngine->pT4Game)
			if (TurokEngine->pT4Game->pEngineObjects)
				if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[1])
					if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[1]->pPlayer)
						player1 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[1]->pPlayer;

	if(player1 !=0)
		player1->respawn(0, 0);

	/*
//	lPlayer1->crouch(0, 1.0f);
	
	//Sleep(500);
	//UnCrouch(lPlayer1);

	lPlayer1->PlayerAction = 0;
	lPlayer1->fire_weapon(0, 0); 
	//lPlayer1->fire_held(0.0f, 0);
	//Sleep(100);
	lPlayer1->fire_release(0.1f);
	*/
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

	return pplayer_death4(thisptr,a2);
}

typedef int(__stdcall *tspawn_object)(void* thisptr, int a2, char* object_name, char* object_path, Vector3* pos_struct, int a6);
tspawn_object pspawn_object;

int count = 0;
int __stdcall spawn_object_engine(void* thisptr, int a2, char* object_name, char* object_path, Vector3* pos_struct, int a6)
{
	FILE* fh = fopen("Object_Dump.txt", "a+");
	
	char text_out[2000];
	memset(text_out, 0x00, 2000);

	sprintf(text_out, "this: %p a2: %i, object_name: %s, object_path: %s, x: %f, y: %f, z: %f, a6: %i\r\n", thisptr, a2, object_name, object_path, pos_struct->x, pos_struct->y, pos_struct->z, a6);
	
	fwrite(text_out, strlen(text_out), 1, fh);
	fclose(fh);

	int ret = pspawn_object(thisptr, a2, object_name, object_path, pos_struct, a6);

	if (!strcmp(object_path, "y:\\Data\\Actors\\EnemyWeapons\\AllyShotgun\\AllyShotgun.atr"))
	{
		T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
		DMPlayer* lPlayer1 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor->pDMPlayer;
		lPlayer1->PlayerAction = 0;

		lPlayer1->fire_weapon(0, 0); // 3A4 = 0
		lPlayer1->fire_held(3.0f, 0); //0xE9
		
		lPlayer1->fire_release(3.0f);
		
		//printf("Attempting to fire\r\n");

	}

	if (!strcmp(object_path, "y:\\Data\\Actors\\EnemyWeapons\\EnemyFlameThrower\\EnemyFlameThrower.atr"))
	{
		T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
		DMPlayer* lPlayer1 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor->pDMPlayer;
		lPlayer1->fire_weapon(0, 0); // 3A4 = 0
		lPlayer1->fire_held(0.2f, 0); //0xE9
		lPlayer1->fire_release(0.02979338f);

		printf("Firing flame thrower\r\n");
		//lPlayer1->fire_weapon2(1.0f);
	}

	if (!strcmp(object_path, "y:\\Data\\Actors\\EnemyWeapons\\AllySniperRifle\\AllySniperRifle.atr"))
	{
		T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
		DMPlayer* lPlayer1 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor->pDMPlayer;
		lPlayer1->fire_weapon(0, 0);
		lPlayer1->fire_held(0.2f, 0);
		lPlayer1->fire_release(1.0f);

	}
	/*
	if (!strcmp(object_path, "y:\\Data\\Actors\\EnemyWeapons\\Warclub\\Warclub.atr"))
	{
		count++;

		if (count > 4)
		{

		
			T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
			DMPlayer* lPlayer1 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor->pDMPlayer;
			lPlayer1->fire_weapon(0, 0);
			lPlayer1->fire_held(0.0f, 0);
			//lPlayer1->fire_weapon2(5.99901f);
		

		}
	}*/

	if(!strcmp(object_path,"y:\\Data\\Actors\\EnemyWeapons\\SpikedMine\\SpikedMine.atr"))
	{

		T4Engine * TurokEngine = (T4Engine*)0x6B52E4;
		DMPlayer* lPlayer1 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[0]->pActor->pDMPlayer;
		lPlayer1->pWeaponWheel->bFlameThrower = 1;
		lPlayer1->pWeaponWheel->bFlameThrowerAllowed = 1;
		lPlayer1->pWeaponWheel->FlameThrowerAmmo = 500;

		/*lPlayer1->fire_weapon(0,0);
		lPlayer1->fire_held(0.2, 0);
		lPlayer1->fire_weapon2(1.0f);
		*/
		count++;

		
		//if (count == 1)
	//	{
			char *spawn_path = new char[255];
			memset(spawn_path, 0x00, 255);
			sprintf(spawn_path, "$/Data/Actors/multiplayer\\players\\workerplayer\\workerplayer.atr");

			char *spawn_name = new char[20];
			memset(spawn_name, 0x00, 20);
			sprintf(spawn_name, "DMPlayer");

			Vector3 npos_struct = *pos_struct;
			npos_struct.x += 5.0f;
			npos_struct.y += 5.0f;
			npos_struct.z += 5.0f;

			DWORD dwOld;
			VirtualProtect((BYTE*)0x004DAD49, 1, PAGE_EXECUTE_READWRITE, &dwOld);

			BYTE OrigByte = *(BYTE*)0x004DAD49;
			*(BYTE*)0x004DAD49 = 0xEB;

			DWORD nPlayerPTR = (DWORD)pspawn_object(thisptr, 0, spawn_name, spawn_path, &npos_struct, 0);
			printf("nPlayerPTR: %08X - spawn_object\r\n", nPlayerPTR);

			*(BYTE*)0x004DAD49 = OrigByte;
		//}

			/*

		if (count == 2 )
		{
			DMPlayer* pPlayer2 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[1]->pActor->pDMPlayer;
			/*pPlayer2->pWeaponWheel->bRocket1 = 1;
			pPlayer2->pWeaponWheel->bRocket2 = 1;
			pPlayer2->pWeaponWheel->RocketAmmo1 = 20;
			pPlayer2->pWeaponWheel->RocketAmmo2 = 20;
			pPlayer2->pWeaponWheel->RocketAmmo3 = 20;
			pPlayer2->WeaponSwitch = -1;
			pPlayer2->TimeTillSwitch = 0.4f;
			*/
		/*	pPlayer2->jump(0, 1.0f);
		}

		if (count == 3)
		{
			DMPlayer* pPlayer2 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[1]->pActor->pDMPlayer;
			pPlayer2->fire_weapon(0, 0);
			pPlayer2->fire_held(0.2f, 0);

		}

		if (count == 5)
		{
			DMPlayer* pPlayer2 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[1]->pActor->pDMPlayer;
			pPlayer2->fire_weapon2(0.2f);

		}*/

	}

	
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


int __cdecl call_print_text(int obj, int text, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, unsigned int a12)
{
	typedef int(__cdecl *print_text)(int obj, int text, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, unsigned int a12);
	print_text pprint_text = (print_text)((char*)0x4EA850);

	return pprint_text(obj, text, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
}

int __cdecl call_spawn_object(int obj, int a2, char* object_name, char* object_path, int pos_struct, int a6)
{
	typedef int(__cdecl *spawn_object)(int obj, int a2, char* object_name, char* object_path, int pos_struct, int a6);
	spawn_object pspawn_object = (spawn_object)((char*)0x5120E0);

	return pspawn_object(obj, a2, object_name, object_path, pos_struct, a6);
}

//Broken for now, seems to not resolve correctly.
void TurokEngine::spawn_object(char* object_path,int position)
{
	int objptr = *(DWORD *)(*(DWORD *)(*(DWORD *)(*(DWORD *)(*(DWORD *)(*(DWORD *)(0x6B52E4 + 0xC0) + 4) + 0x664) + 0x29C) + 0x1A38) + 0x48);
	
	call_spawn_object(objptr, 1, "EnemyWeapon", object_path, position, 0);

}

void TurokEngine::print_text(char* text)
{
	HMODULE T4Base = GetModuleHandle("Turok4.exe");
	int object_ptr = *(int*)((char*)T4Base + 0x2B52E4);
	call_print_text(object_ptr, (int)text, 0x41700000, 0x3F800000, 4, 0x3EFFDDDE, 0x3EB25B6B, 0, 2, 1, 1, 2);
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

	pactor_spawn_1 = (tactor_spawn_1)DetourClassFunc((BYTE*)0x005C1DD0, (BYTE*)actor_spawn_1, 10);

	VirtualProtect(pactor_spawn_1, 4, PAGE_EXECUTE_READWRITE, &dwBack);
	
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

	Codecave(0x0050F850, CameraFuncLoop1, 1);
	Codecave(0x0050F8F0, CameraFuncLoop2, 1);
	Codecave(0x004EE7F0, screen_effect_osd, 1);
}