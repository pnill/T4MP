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

	pinput_query(thisptr, pInputPointer);

	t4net.ProcessMessage();

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
	/*char text_out[2000];
	memset(text_out, 0x00, 2000);
	sprintf(text_out, "thisptr: %p, a2: %s, a3: %08X, a4: %08X", thisptr, a2, a3, a4);

	FILE* fh = fopen("level_load.txt", "a+");
	fwrite(text_out, strlen(text_out), 1, fh);
	fclose(fh);
	*/
	return plevel_load_actor(thisptr, a2, a3, a4);
}

typedef int(__stdcall *tconstruct_actor)(void* thisptr, char* object_name, char* object_path);
tconstruct_actor pconstruct_actor;

//int i = 0;
int __stdcall construct_actor(void* thisptr, char* object_name, char* object_path)
{
	/*
	FILE* fh = fopen("construct_actor.txt", "a+");

	char text_out[2000];
	memset(text_out, 0x00, 2000);
	sprintf(text_out, "this: %p, object_name: %s, object_path: %s\r\n", thisptr, object_name, object_path);
	fwrite(text_out, strlen(text_out), 1, fh);
	fclose(fh);*/

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






void FireWeapon()
{

	Player* player1 = 0;


		T4Engine * TurokEngine = (T4Engine*)0x6B52E4;

		if (TurokEngine->pT4Game)
			if (TurokEngine->pT4Game->pEngineObjects)
				if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[1])
					if (TurokEngine->pT4Game->pEngineObjects->pCameraArray[1]->pPlayer)
						player1 = TurokEngine->pT4Game->pEngineObjects->pCameraArray[1]->pPlayer;

	if (player1 != 0)
	{
		BYTE OrigByte = *(BYTE*)0x004DAD49;
		*(BYTE*)0x004DAD49 = 0xEB;

		player1->respawn(0, 0);

		*(BYTE*)0x004DAD49 = OrigByte;
	}

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

	/*
	  .text:004D916D mov     ecx, [esi+1B20h]
	  .text:004D9173 test    byte ptr [ecx+30h], 40h
	*/

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

	/*if(!strcmp(object_path,"y:\\Data\\Actors\\EnemyWeapons\\SpikedMine\\SpikedMine.atr"))
	{
			char *spawn_path = new char[255];
			ZeroMemory(spawn_path, 255);
			//memset(spawn_path, 0x00, 255);

			sprintf_s(spawn_path, strlen("$/Data/Actors/multiplayer\\players\\workerplayer\\workerplayer.atr")+1, "%s", "$/Data/Actors/multiplayer\\players\\workerplayer\\workerplayer.atr");
			
			char *spawn_name = new char[20];
			ZeroMemory(spawn_name, 20);
			//memset(spawn_name, 0x00, 20);

			sprintf_s(spawn_name, strlen("DMPlayer")+1, "%s", "DMPlayer");

			Vector3 npos_struct = *pos_struct;
			npos_struct.x += 5.0f;
			npos_struct.y += 5.0f;
			npos_struct.z += 5.0f;

			DWORD dwOld;
			VirtualProtect((BYTE*)0x004DAD49, 1, PAGE_EXECUTE_READWRITE, &dwOld);

			BYTE OrigByte = *(BYTE*)0x004DAD49;
			*(BYTE*)0x004DAD49 = 0xEB;

			DWORD nPlayerPTR = (DWORD)pspawn_object(thisptr, 0, spawn_name, spawn_path, &npos_struct, 0);

			*(BYTE*)0x004DAD49 = OrigByte;
	}*/

	
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

void TurokEngine::print_text(char* text)
{
	HMODULE T4Base = GetModuleHandle(L"Turok4.exe");
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

	Codecave(0x0050F850, CameraFuncLoop1, 1);
	Codecave(0x0050F8F0, CameraFuncLoop2, 1);
	Codecave(0x004EE7F0, screen_effect_osd, 1);

    t4net.Initalize();
	
}