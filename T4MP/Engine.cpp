#include "stdafx.h"
#include "Engine.h"
#include "Hook.h"

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

	return pprint_text(obj, text, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
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
}