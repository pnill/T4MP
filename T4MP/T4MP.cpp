// SR4-MP.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Hook.h"
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

bool sync_players = false;

struct float_arr
{
	float x = 0;
	float y = 0;
	float z = 0;
};

void trace(const char* message, ...)
{
	
	va_list	arg;
	va_start(arg, message);
	printf("[T4MP]: ");
	vfprintf(stdout, message, arg);
	printf("\n");
	va_end(arg);

}

float_arr* get_player_pos(int index)
{
	int base = *(int*)(0x6B52E4);
	int base_2 = 0;
	int base_3 = 0;
	int base_4 = 0;
	int player = 0;

	float_arr* player_pos = 0;

	if(base)
		base_2 = *(int*)(base + 0x0C0);
	if(base_2)
		base_3 = *(int*)(base_2+(index*4));
	if(base_3)
		base_4 = *(int*)(base_3 + 0x664);
	if(base_4)
		player = *(int*)(base_4 + 0x29C);
	if (player)
		player_pos = (float_arr*)(player + 0x38);

	if (player_pos == 0)
	{
		player_pos = new float_arr;
	}

	return player_pos;
}

int get_player_1_walk()
{
	int base = *(int*)(0x6B52E4);
	int base_2 = 0;
	int base_3 = 0;
	int base_4 = 0;
	int player = 0;

	int walk = 0;

	if (base)
		base_2 = *(int*)(base + 0x0C0);
	if (base_2)
		base_3 = *(int*)(base_2);
	if (base_3)
		base_4 = *(int*)(base_3 + 0x664);
	if (base_4)
		player = *(int*)(base_4 + 0x29C);
	if (player)
		walk = *(int*)(player + 0x104);


	return walk;
}

void set_player_2_walk(int walk)
{
	int base = *(int*)(0x6B52E4);
	int base_2 = 0;
	int base_3 = 0;
	int base_4 = 0;
	int player = 0;


	if (base)
		base_2 = *(int*)(base + 0x0C0);
	if (base_2)
		base_3 = *(int*)(base_2 + 0x04);
	if (base_3)
		base_4 = *(int*)(base_3 + 0x664);
	if (base_4)
		player = *(int*)(base_4 + 0x29C);
	if (player)
		*(int*)(player + 0x104) = walk;
}

struct view {
	float x = 0;
	float y = 0;
};

float* get_player_view(int index)
{
	int base = *(int*)(0x6B52E4);
	int base_2 = 0;
	int base_3 = 0;
	int base_4 = 0;
	int player = 0;

	float* player_view = 0;

	if (base)
		base_2 = *(int*)(base + 0x0C0);
	if (base_2)
		base_3 = *(int*)(base_2 + (index * 4));
	if (base_3)
		base_4 = *(int*)(base_3 + 0x664);
	if (base_4)
		player = *(int*)(base_4 + 0x29C);
	if (player)
		player_view = (float*)(player + 0xF4);

	if (player_view == 0)
	{
		float x = 1;
		player_view = &x;
	}

	return player_view;
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
		*player_2_joined = 1;
	}

	return ret;
}

int __cdecl call_print_text(int obj, int text, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, unsigned int a12)
{
	typedef int(__cdecl *print_text)(int obj, int text, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, unsigned int a12);
	print_text pprint_text = (print_text)((char*)0x4EA850);

	return pprint_text(obj,text,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
}


int(__thiscall *construct_actor_object)(void* thisPtr, char* object_name, char* object_path) = (int(__thiscall*)(void*, char*, char*))0x50DEE0;
int(__thiscall *set_actor_position)(void *actorPtr, float_arr *pos) = (int(__thiscall*)(void*,float_arr*))0x51A4D0;
int(__thiscall *spawn_actor)(void *thisPtr, void* actorPtr, int a3) = (int(__thiscall*)(void*,void*,int))0x511410;
int(__thiscall *spawn_actor_parent)(void *thisPtr, void* actorPtr, int a3) = (int(__thiscall*)(void*, void*, int))0x511560;

/*
	spawning_ai
	v5 = main_obj_ptr
	a2 = AI path

	actor_ptr = construct_actor(v5, a2, a2);

	(*(*v4 + 0x40))(v4);
	v10 = (*(*v4 + 0xC))(v4);

	unk shit happening here...

	/*
	.text:00511E78                 mov     eax, [edi] mov eax,[actorptr]
	.text:00511E7A                 push    esi	// unk value
	.text:00511E7B                 mov     ecx, edi // mov ecx,actorptr
	.text:00511E7D                 call    dword ptr [eax+0B0h] // sub_4B87A0(int actorptr, int unkptr) - seems to be sounds.

	v12 = (*(*actor_ptr + 0xB0))(actor_ptr);


	v28 = *(actor_ptr + 0x1E4);
	v29 = *(v5 + 0x188); // main_obj_pointer
	if ( !v28 || (v30 = *(*(v28 + 176) - 8), v45 = 1, !v30) )
	v45 = 0;
*/


int(__thiscall *create_camera_screen)(void* thisptr) = (int(__thiscall*)(void*))0x4FED00;
int(__thiscall *player_spawn_end_routine)(void* thisptr, int a2) = (int(__thiscall*)(void*, int))0x510AA0;
int(__thiscall *player_construct_1)(void* thisptr, int a2) = (int(__thiscall*)(void*, int))0x4D65C0;
int(__thiscall *player_construct_2)(void* thisptr, int a2) = (int(__thiscall*)(void*, int))0x4C7A10;
int(__thiscall *player_construct_3)(void* thisptr, int a2) = (int(__thiscall*)(void*, int))0x4D6D50;
int(__thiscall *player_construct_4)(void* thisptr, void* a2) = (int(__thiscall*)(void*, void*))0x4D8740;
int(__thiscall *player_construct_5)(void* thisptr, int a2) = (int(__thiscall*)(void*, int))0x4F2710;
char*(__stdcall *add_player)(int playernum) = (char*(__stdcall*)(int))0x4F5240;
int(__thiscall *init_particle)(void* thisptr, char* particle_path, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11) = (int(__thiscall *)(void*,char*,int,int,int,int,int,int,int,int,int))0x51E810;

void spawn_player(int thisptr, char* player_path)
{
	trace("spawn_player( thisptr: %08X, player_path: %s )", thisptr, player_path);

	trace("construct_actor_object(thisptr: %08X, player_path: %s)",thisptr,player_path);

	int actorPtr = construct_actor_object((void*)thisptr, "TAL'SET", player_path);

	trace("construct_actor_object: %08X - finished", actorPtr);

	if (actorPtr)
	{
	
		strcpy((char*)(actorPtr + 0x1948), "TAL'SET (2)");
		trace("copied string to actorPtr+0x1948");
		
		int v4 = *(int*)((char*)GetModuleHandle("Turok4.exe") + 0x2B5930);
		trace("v4 = %08X", v4);
		
		int v5 = *(int*)((char*)v4 + 0x6C);
		trace("v5 = %08X", v5);
		
		int v6 = *(int*)((char*)v4 + 0x70);
		trace("v6 = %08X", v6);

		int v8 = *(int*)((char*)v5);
		trace("v8 = %08X", v8);

		int v11 = *(int*)((char*)v8+0x54);
		trace("v11 = %08X", v11);


		/*
			.text:004FA40A                 mov     eax, [ebx+54h] // mov eax(v11), [v8+0x54]
			.text:004FA40D                 mov     edx, [esi] // mov edx,[actorPtr]
			.text:004FA40F                 push    eax	// push v11
			.text:004FA410                 mov     ecx, esi //mov ecx(this), actorPtr
			.text:004FA412                 call    dword ptr [edx+3A0h] // sub_4D65C0(void* actorPtr, int v11)
		*/
		//trace("player_construct_1( actorPtr: %08X, v11: %08X )");
		//player_construct_1((void*)actorPtr, v11);
		//trace("player_construct_1( actorPtr: %08X, v11: %08X ) - finished");

		int v16 = *(int*)(v8 + 4);
		
		trace("v16 = %08X", v16);

		//trace("player_construct_2(actorPtr: %08X, &v16: %08X, v16: %08X)", actorPtr, &v16, v16);
		//player_construct_2((void*)actorPtr, (int)&v16);
		//trace("player_construct_2(actorPtr: %08X, &v16: %08X, v16: %08X) - finished",actorPtr,&v16,v16);

		/*
			.text:004FA43A                 mov     eax, [esi] // mov eax,[actorPtr]
			.text:004FA43C                 push    1		// 1
			.text:004FA43E                 mov     ecx, esi // mov ecx,ActorPtr
			.text:004FA440                 call    dword ptr [eax+134h] // sub_4D6D50(void* actorPtr, int 1)
		*/

    	//trace("player_construct_3(actorPtr: %08X, a1: 1)", actorPtr);
		//player_construct_3((void*)actorPtr, 1);
		//trace("player_construct_3(actorPtr: %08X, a1: 1) - finished",actorPtr);


		int v10 = create_camera_screen((void*)(v4 + 4));
		trace("v10 = %08X", v10);
		trace("actorPtr: %08X", actorPtr);

		*(int*)(v10 + 0x5EC) = actorPtr;
		*(int*)(actorPtr + 0x3CC) = v10;

		trace("main_obj_ptr: %08X",thisptr);
		trace("v10: %08X",v10);

	
		//trace("player_spawn_end_routine( thisptr: %08X, v10: %08X )", thisptr, v10);
		//player_spawn_end_routine((void*)thisptr, v10); // crash at sub_54B280  ecx = 0;
		//trace("player_spawn_end_routine( thisptr: %08X, v10: %08X ) - finished", thisptr, v10);

		//trace("spawn_actor_parent(thisptr: %08X,v10: %08X)", thisptr, v10);
		//spawn_actor_parent((void*)thisptr, (void*)v10, 0);
		//trace("spawn_actor_parent(thisptr: %08X,v10: %08X) - finished", thisptr, v10);

		/*
			.text:004FA46E                 mov     ecx, [esp+14h]
			.text:004FA472                 mov     edx, [ecx]
			.text:004FA474                 push    esi
			.text:004FA475                 call    dword ptr [edx+44h]

			!SKIPPED! esp+14h can't be calculated, and it's the thisptr.
			It could be the actorptr, or something related to it considering edx = actor_ptr, maybe the parent?
			Stepping through it revelead a small function that seemed to be skipped.
		*/

		/*
			.text:004FA478                 mov     eax, [esi] // mov eax,[actorPtr]
			.text:004FA47A                 push    ebp	// thisptr / main object pointer
			.text:004FA47B                 mov     ecx, esi // mov ecx,actorPtr
			.text:004FA47D                 call    dword ptr [eax+3B4h] // sub_4D8740(void *actorptr, int mainObjectPointer)
		*/
		
	
		//spawn_actor_parent((void*)thisptr, (void*)actorPtr, 0);

		//Lets attempt avoiding some race conditions with some hacky bullshit...
		//The game attempts to access 0x1BD0 and fails at some point..
		//We can only assume the same will eventually happen on 0x1Bd4 as well.

		
	
		//trace("player_construct_4( actorPtr: %08X, objptr: %08X)", actorPtr, thisptr);
		//	player_construct_4((void*)actorPtr, (void*)thisptr);
		//trace("player_construct_4( actorPtr: %08X, objptr: %08X) - finished", actorPtr, thisptr);
		
		/*
				.text:004FA483                 mov     edx, [ebx] // mov edx,[ebx(v8)]
				.text:004FA485                 push    1		 // 1
				.text:004FA487                 mov     ecx, ebx // mov ecx, v8
				.text:004FA489                 call    dword ptr [edx] // sub_4F2710( void* v8, 1 )
		*/

		//trace("player_construct_5( v8: %08X, 1)", v8);
		//player_construct_5((void*)v8, 1);
		//trace("player_construct_5( v8: %08X, 1) - finished", v8);

	}
}

void spawn_object(int thisptr,char* object_name,char* object_path,float_arr* float_array)
{
	int actorPtr = construct_actor_object((void*)thisptr, object_name, object_path);
	if (actorPtr)
	{
		set_actor_position((void*)actorPtr, float_array);
		spawn_actor_parent((void*)thisptr, (void*)actorPtr, 0);
	}
}


bool player_test = false;
void DebugAction()
{
	int actionID;

	char* object_path = new char[255];
	memset(object_path, 0x00, 255);

	fprintf(stdout, "Enter an actionID: \n");
	scanf_s("%d", &actionID);
	HMODULE T4Base = GetModuleHandle("Turok4.exe");
	
	int object_ptr = *(int*)((char*)T4Base + 0x2B52E4);
	char* text = "Hello World! - Turok Forums!";

	switch (actionID)
	{

		case 1:
			
			FILE* f;
			fopen_s(&f,"spawn_object.txt", "r");
			while (fgets(object_path, 255, f))
			{
				printf("Spawning Object: %s\r\n", object_path);
			}
			fclose(f);

			printf("T4Base: %08X\r\n", T4Base);

			//float_arr obj_xyz;
			//obj_xyz.x = 0;
			//obj_xyz.y = 3;
			//obj_xyz.z = 0;

			//spawn_object(object_ptr, object_path, object_path, &obj_xyz); 

			printf("object_ptr: %08X\r\n", object_ptr);
		break;

		case 2:
			call_print_text(object_ptr, (int)text, 0x41700000, 0x3F800000, 4, 0x3EFFDDDE, 0x3EB25B6B, 0, 2, 1, 1, 2);
		break;

		case 3:
			call_print_text(object_ptr, (int)text, 0x41700000, 0x40000000, 4, 0x3F800000, 0x3EB25B6B, 0, 2, 1, 1, 2);
		break;

		case 4:
			call_print_text(object_ptr, (int)text, 0x41700000, 0x40400000, 4, 0x3EFFDDDE, 0x3F800000, 0, 2, 1, 1, 2);
		break;

		case 5:
			call_print_text(object_ptr, (int)text, 0x41700000, 0x3F000000, 4, 0x3F000000, 0x3EB25B6B, 0, 4, 1, 1, 2);
		break;

		case 6:
			call_print_text(object_ptr, (int)text, 0x41700000, 0x3F000000, 4, 0x3F000000, 0x3EB25B6B, 0, 2, 5, 1, 2);
		break;


		case 7:
			call_print_text(object_ptr, (int)text, 0x41700000, 0x3F000000, 4, 0x3F000000, 0x3EB25B6B, 0, 2, 1, 5, 2);
		break;

		case 8:
			call_print_text(object_ptr, (int)text, 0x41700000, 0x3F000000, 4, 0x3F000000, 0x3EB25B6B, 0, 2, 1, 1, 4);
		break;

		case 9:
			Sleep(10000);
			spawn_player(object_ptr, "$\\Data\\Actors\\Multiplayer\\Players\\TalsetPlayer\\TalsetPlayer.atr");
		break;

		case 10:
			add_player(2);
			add_player(2);
			add_player(2);
		break;

		case 11:
			sync_players = true;
		break;

		case 13:
			player_test = true;
		break;

		case 12:
			float_arr *pos = get_player_pos(0);
			float_arr *pos_2 = get_player_pos(1);
			trace("player 1 x: %f", pos->x);
			trace("player 2 x: %f", pos_2->x);
		break;

	
	}

}


void SetupHooks()
{
	trace("Setting up function hooks....");
	DWORD dwBack;

	pload_history = (tload_history)DetourClassFunc((BYTE*)0x529650, (BYTE*)load_history, 16);

	VirtualProtect(pload_history, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	trace("Set load_history() hook.");

	trace("All hooks intialized");
}

DWORD WINAPI IntializeNetworking(LPVOID lpParam)
{
	bool is_server;
	FILE* f;
	fopen_s(&f, "t4mp.conf", "r");
	fscanf(f, "%1d", &is_server);
	trace("is_server: %i", is_server);
	fclose(f);

	SOCKET s;
	struct sockaddr_in server, si_other, client;
	int client_len, recv_len;
	WSADATA wsa;

	trace("Intializing Winsock....");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	trace("Winsock Intialized");

	trace("Creating UDP socket");
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	trace("Socket created");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(9000);

	trace("binding socket to port: 9000 UDP");
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	trace("Socket bound listening on port 9000 UDP");


	si_other.sin_family = AF_INET;
	si_other.sin_addr.s_addr = inet_addr("70.187.162.246");
	si_other.sin_port = htons(9000);

	bool is_connected = false;
	
	while (1)
	{
		char RecvBuf[2000];
		memset(RecvBuf, 0x00, 2000);

		if (is_server == 0 && is_connected == false)
		{

			/* Talk to server and get it talking to us....*/
			char *ping = new char[1];
			*ping = { 0x54 };

			trace("Sending ping packet...");
			sendto(s, ping, 1, 0, (SOCKADDR*)&si_other, sizeof(si_other));		
			

			memset(RecvBuf, 0x00, 2000);
			client_len = sizeof(client);

			DWORD dwTime = 20;
			setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&dwTime, sizeof(dwTime));

			recvfrom(s, RecvBuf, 1, 0, (SOCKADDR*)&client, &client_len);

			if (RecvBuf[0] == 0x45)
			{
				is_connected = true;
				trace("We received a packet from the other side time to continue...");
			}
			delete[] ping;

		}

		if (is_server == 1 && is_connected == false)
		{
			memset(RecvBuf, 0x00, 2000);
			client_len = sizeof(client);

			DWORD dwTime = 20;
			setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&dwTime, sizeof(dwTime));

			recvfrom(s, RecvBuf, 1, 0, (SOCKADDR*)&client, &client_len);

			char* pong = new char[1];
			*pong = { 0x45 };

			if (RecvBuf[0] == 0x54)
			{
				trace("Received ping packet... sending our pong.");
				sendto(s, pong, 1, 0, (SOCKADDR*)&client, sizeof(client));

				is_connected = true;
			}
			delete[] pong;
			
		}

		if (player_test)
		{
			*(int*)(0x6b5970) = *(int*)(0x6b5950);
			float* player_view_y = get_player_view(0);
			float* player_view_x = (player_view_y + 4);

	
			//float* player1_view_x = get_player_view(0, 0xF4);
			//float* player1_view_y = get_player_view(0, 0xF8);

			//float* player2_view_x = get_player_view(1, 0xF4);
			//float* player2_view_y = get_player_view(1, 0xF8);

			

			//*player2_view_x = *player1_view_x;
			//*player2_view_y = *player1_view_y;

			//get_player_view(1)->x = get_player_view(0)->x;
			//get_player_view(1)->y = get_player_view(0)->y;
		}
			if (sync_players && is_connected == true)
			{
				int player_1_action = *(int*)(0x6B5950);

				char* sendbuf = new char[2000];
				int sendsize = 0;
				bool x = false;
				bool y = false;
				bool z = false;

				if (get_player_pos(0))
				{
						sendbuf[0] = { 0x01 };
					
						*(float*)&sendbuf[1] = get_player_pos(0)->x;
						*(float*)&sendbuf[5] = get_player_pos(0)->y;
						*(float*)&sendbuf[9] = get_player_pos(0)->z;

						*(int*)&sendbuf[13] = player_1_action;
						*(int*)&sendbuf[17] = get_player_1_walk();

						sendto(s, sendbuf, 22, 0, (SOCKADDR*)&client, sizeof(client));
				}

				if (get_player_pos(1))
				{
					memset(RecvBuf, 0x00, 2000);
					client_len = sizeof(client);

					DWORD dwTime = 20;
					setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&dwTime, sizeof(dwTime));

					recvfrom(s, RecvBuf, 22, 0, (SOCKADDR*)&client, &client_len);

					if (RecvBuf[0] == 0x01)
					{
						float_arr * player2_pos = get_player_pos(1);
						if (player2_pos)
						{
					
							get_player_pos(1)->x = *(float*)&RecvBuf[1];
							get_player_pos(1)->y = *(float*)&RecvBuf[5];
							get_player_pos(1)->z = *(float*)&RecvBuf[9];
						}
						*(int*)(0x6B5970) = *(int*)&RecvBuf[13];
						set_player_2_walk(*(int*)&RecvBuf[17]);

					}
				}

				delete[] sendbuf;
			
			} // sync players
		} // while(1)
}


DWORD WINAPI Intialize(LPVOID lpParam)
{
	if (GetModuleHandle("Turok4.exe"))
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);

		trace("Turok 4 Multiplayer Modification Intializing....");

		SetupHooks();

		int Data_of_Init_Thread = 1;
		HANDLE Hanlde_of_Init_Thread = 0;
		Hanlde_of_Init_Thread = CreateThread(NULL, 0, IntializeNetworking, &Data_of_Init_Thread, 0, NULL);

		while (true)
		{
			DebugAction();
		}
	}
	return 0;
}


void PreIntialize()
{
	

	int Data_of_Init_Thread = 1;
    HANDLE Hanlde_of_Init_Thread = 0;

	// We have to work entirely in a new thread otherwise we'll encounter some blocking, and other IO related complications.
	// We don't want to block game code waiting for input and shit.
	Hanlde_of_Init_Thread = CreateThread(NULL, 0, Intialize, &Data_of_Init_Thread, 0, NULL);

		
}