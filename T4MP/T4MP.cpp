#include "stdafx.h"
#include <iostream>
#include <string>
#include "Engine.h"
#include "Player.h"
TurokEngine Engine;
TurokPlayer player1;


void DebugAction()
{
	int actionID;

	char* object_path = new char[255];
	memset(object_path, 0x00, 255);

	//fprintf(stdout, "Enter an actionID: \n");
	//scanf_s("%d", &actionID);

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		printf("Firing Weapon\r\n");
		FireWeapon();
	}

	/*switch (actionID)
	{
		case 1:
			printf("sent 1");
		break;

		case 2:
			Engine.spawn_object("y:\\data\\actors\\enemies\\Humans\\soldier\\solider.atr",(int)player1.get_position());
		break;

		case 3:
			Engine.print_text("Test printing text");
		break;

		

	/*	case 4:
			char* script_arr = new char[0x100];
			char* script_path = new char[255];
			memset(script_arr, 0x00, 0x100);
			memset(script_path, 0x00, 255);

			sprintf(script_path, "y:\\data\\actors\\enemies\\Humans\\soldier\\soldier.atr");

			*(DWORD*)script_arr[0] = 0x65F230;
			*(DWORD*)script_arr[4] = 0x6B92D8;
			*(DWORD*)script_arr[8] = (DWORD)script_path;
			*(DWORD*)script_arr[0x38] = 0;
			*(DWORD*)script_arr[0x0C] = 1;

		break;*/
	/*
		case 5:
			DWORD flOldProtect;
			VirtualProtect((LPVOID)0x5DECF3, 2, 4, &flOldProtect);

			*(BYTE*)0x5DECF3 = 0xEB; // Patch SendMessageA Jump

			VirtualProtect((LPVOID)0x5DECF3, 2, flOldProtect, 0);

			HMODULE tlib = LoadLibrary("tlib.dll");
			typedef void(__stdcall *ExecScript)(char* script);
			ExecScript escript = (ExecScript)GetProcAddress(tlib, "ExecScript");
			char* script_data = new char[0x6100];
			memset(script_data, 0x00, 0x6100);

			FILE* fh = fopen("C:\\TUROK\\data\\levels\\u_jcowlishaw\\screens\\Zoo\\zoo.ati", "r");
			fread(script_data, 0x51A2, 1, fh);
			// *(DWORD*)script_data[0] = 0x01617469;
		//	*(DWORD*)(script_data+4) = 0x4200CC05;
			fclose(fh);
			escript(script_data);

			VirtualProtect((LPVOID)0x5DECF3, 2, 4, &flOldProtect);

			*(BYTE*)0x5DECF3 = 0x0F; // Patch SnedMessage jnz

			VirtualProtect((LPVOID)0x5DECF3, 2, flOldProtect, 0);
			//char* script = new char[255];
			//memset(script, 0x00, 255);
			//sprintf(script, "y:\\data\\actors\\enemies\\Humans\\soldier\\soldier.atr");
			//escript(script);
		break;*/

		/*case 6:
			FireWeapon();
		break;

	}*/
	
	delete[] object_path;
}

DWORD WINAPI Intialize(LPVOID lpParam)
{
	HINSTANCE hook_handle = LoadLibraryA("D3dHook.dll");
	if (GetModuleHandle("Turok4.exe"))
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);

		Engine.SetModHooks(); // Setup engine hooks.
		
		while (true)
		{
			DebugAction();
		}
	}
	return 0;
}


void PreIntialize()
{
	Sleep(2000);
	
	/*DWORD flOldProtect;
	VirtualProtect((LPVOID)0x5DECF3, 2, 4, &flOldProtect);

	*(BYTE*)0x5DECF3 = 0xEB; // Patch SendMessageA Jump

	VirtualProtect((LPVOID)0x5DECF3, 2, flOldProtect, 0);
*/
	int Data_of_Init_Thread = 1;
    HANDLE Hanlde_of_Init_Thread = 0;

	Hanlde_of_Init_Thread = CreateThread(NULL, 0, Intialize, &Data_of_Init_Thread, 0, NULL);

}