#include <windows.h>
#include <iostream>
#include <string>
#include "Engine.h"
#include "d3d9.h"
#include "D3D9/T4Console.h"
#include "Hook.h"

TurokEngine Engine;
ConsoleCommands* commands = new ConsoleCommands();

void DebugAction()
{
	
	
	//For testing specific actions.
	if (GetAsyncKeyState(VK_RSHIFT))
	{
	//	ChangeDeath();
	}

}

typedef BOOL(__stdcall *tPeekMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
tPeekMessageA pPeekMessageA;

BOOL WINAPI PeekMessageAHook(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
	BOOL result;
	result = pPeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);

	if (result && wRemoveMsg & PM_REMOVE)
	{
		switch (lpMsg->message)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			result = commands->handleInput(lpMsg->wParam);
			if (result == TRUE)
			{
				DWORD dwBack;
				VirtualProtect((BYTE*)0x004D0466, 1, PAGE_EXECUTE_READWRITE, &dwBack);

				if(commands->console != false)
					*(BYTE*)(0x004D0466) = 0xEB; // Disable game input
			}

		}
	}


	return result;
}


DWORD WINAPI Intialize(LPVOID lpParam)
{
	/*
	   Establishing our own D3D hook for some fixes and debugging console,
	   will potentially be used for more in the future. 
	*/

	char sysd3d[320];
	GetSystemDirectory(sysd3d, 320);
	strcat(sysd3d, "\\d3d9.dll");

	HMODULE hMod = LoadLibrary(sysd3d);
	oDirect3DCreate9 = (tDirect3DCreate9)DetourFunc(
		(BYTE*)GetProcAddress(hMod, "Direct3DCreate9"),
		(BYTE*)hkDirect3DCreate9,
		5);

	/* Hook to get input for debug console, 
	   Doesn't currently restrict input from game needs to be looked into.   
	*/
	HMODULE hMod2 = LoadLibrary("user32.dll");

	pPeekMessageA = (tPeekMessageA)DetourFunc((BYTE*)GetProcAddress(hMod2,"PeekMessageA"), (BYTE*)PeekMessageAHook, 5);
	DWORD dwBack;
	VirtualProtect(pPeekMessageA, 4, PAGE_EXECUTE_READWRITE, &dwBack);

	/*
	Using an 3rd party hook which forces windowed mode and adds some input improvements to the game.
	Configured using hook.ini which the server browser/launcher will modify in the future.
	*/
	HINSTANCE hook_handle = LoadLibraryA("D3dHook.dll");


	if (GetModuleHandle("T4MP.exe"))
	{
		AllocConsole();
		FILE *cout;
		freopen_s(&cout, "CONOUT$", "w", stdout);

		Engine.SetModHooks(); // Setup engine hooks.
		
		// Some debug code...
		//while (true)
		//{
		//	DebugAction();
		//}
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