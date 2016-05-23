#include "stdafx.h"
#include <iostream>
#include "Engine.h"

TurokEngine Engine;

void DebugAction()
{
	int actionID;

	char* object_path = new char[255];
	memset(object_path, 0x00, 255);

	fprintf(stdout, "Enter an actionID: \n");
	scanf_s("%d", &actionID);

	switch (actionID)
	{
		case 1:
			printf("sent 1");
		break;

		case 2:
			Engine.print_text("Test printing text");
		break;
	
	}

}

DWORD WINAPI Intialize(LPVOID lpParam)
{
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
	
	LoadLibrary("D3dHook.dll");
	int Data_of_Init_Thread = 1;
    HANDLE Hanlde_of_Init_Thread = 0;

	Hanlde_of_Init_Thread = CreateThread(NULL, 0, Intialize, &Data_of_Init_Thread, 0, NULL);

}