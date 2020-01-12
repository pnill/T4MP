#define INITGUID
#include "IDIn8.h"
#include "IDInDev8.h"
#include "DirectInputHook.h"
extern IDirectInput8 *g_pDInInt8;
extern hkIDirectInput8 *phkDInput8;
extern LPVOID * Value;

void __cdecl add_log(const char * fmt, ...);

extern HHOOK currentHook;
LRESULT CALLBACK HookProc(int nCode, WPARAM wp, LPARAM lp);

HRESULT APIENTRY hkIDirectInput8::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{

	hkIDirectInputDevice8 *phkDInputDevice8 = new hkIDirectInputDevice8;
	
	
	if (rguid == GUID_SysMouse)
	{
		add_log("hooked mouse");
	}
	if (rguid == GUID_SysKeyboard)
	{
		add_log("hooked Keyboard");
	}
	if (rguid == GUID_Joystick)
	{
		add_log("hooked Joystick");
	}

	if (rguid == GUID_SysKeyboardEm)
	{
		add_log("hooked SysKeyBoardEm");
	}

	add_log("GUID 0x%X",rguid);

	HRESULT Result = g_pDInInt8->CreateDevice(rguid, (LPDIRECTINPUTDEVICE8*)&phkDInputDevice8->g_pDInDev8, pUnkOuter);
	add_log( "Hooked IDirectInputDevice8: 0x%x -> 0x%x", Value, phkDInputDevice8 );
	*lplpDirectInputDevice = (LPDIRECTINPUTDEVICE8)phkDInputDevice8;

	UnhookWindowsHookEx(currentHook);
	currentHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, 0, 0);

	return Result;


}

HRESULT APIENTRY hkIDirectInput8::QueryInterface(REFIID iid, void ** ppvObject)
{


	HRESULT hRes = g_pDInInt8->QueryInterface(iid, ppvObject); 


	return hRes;

}

ULONG APIENTRY hkIDirectInput8::AddRef(void)
{
	return g_pDInInt8->AddRef();
}

ULONG APIENTRY hkIDirectInput8::Release(void)
{
	return g_pDInInt8->Release();
}

HRESULT APIENTRY hkIDirectInput8::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return g_pDInInt8->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}

HRESULT APIENTRY hkIDirectInput8::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return g_pDInInt8->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT APIENTRY hkIDirectInput8::EnumDevicesBySemantics(LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return g_pDInInt8->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
}

HRESULT APIENTRY hkIDirectInput8::FindDevice(REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance)
{
	return g_pDInInt8->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT APIENTRY hkIDirectInput8::GetDeviceStatus(REFGUID rguidInstance)
{
	return g_pDInInt8->GetDeviceStatus(rguidInstance);
}

HRESULT APIENTRY hkIDirectInput8::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return g_pDInInt8->Initialize(hinst, dwVersion);
}

HRESULT APIENTRY hkIDirectInput8::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return g_pDInInt8->RunControlPanel(hwndOwner, dwFlags);
}
