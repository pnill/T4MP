#pragma once
#include <dinput.h>
#include "IDInDev8.h"

interface hkIDirectInput8 : public IDirectInput8
{
public:
	hkIDirectInputDevice8 hkDInputDevice8;
	HRESULT APIENTRY QueryInterface(REFIID iid, void ** ppvObject);
	ULONG APIENTRY AddRef(void);
	ULONG APIENTRY Release(void);
	HRESULT APIENTRY ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags, LPVOID pvRefData);
	HRESULT APIENTRY CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lpDirectInputDevice, LPUNKNOWN pUnkOuter);
	HRESULT APIENTRY EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);
	HRESULT APIENTRY EnumDevicesBySemantics(LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags);
	HRESULT APIENTRY FindDevice(REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance);
	HRESULT APIENTRY GetDeviceStatus(REFGUID rguidInstance);
	HRESULT APIENTRY Initialize(HINSTANCE hinst, DWORD dwVersion);
	HRESULT APIENTRY RunControlPanel(HWND hwndOwner, DWORD dwFlags);
};

