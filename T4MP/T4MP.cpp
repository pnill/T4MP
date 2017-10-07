#include <windows.h>
#include <iostream>
#include <string>
#include "Engine.h"

TurokEngine Engine;
void DebugAction()
{
	
	

	if (GetAsyncKeyState(VK_RSHIFT))
	{
	//	ChangeDeath();
	}

}

DWORD WINAPI Intialize(LPVOID lpParam)
{
	HINSTANCE hook_handle = LoadLibraryA("D3dHook.dll");
	if (GetModuleHandle(L"Turok4.exe"))
	{
		AllocConsole();
		FILE *cout;
		freopen_s(&cout, "CONOUT$", "w", stdout);

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
	Sleep(2000); // wait awhile for DirectX, otherwise the d3dhook won't work for windowed mode.
	
	int Data_of_Init_Thread = 1;
    HANDLE Hanlde_of_Init_Thread = 0;

	Hanlde_of_Init_Thread = CreateThread(NULL, 0, Intialize, &Data_of_Init_Thread, 0, NULL);

}