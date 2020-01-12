
#include "DirectInputHook.h"
#include "IDInDev8.h"


HRESULT APIENTRY hkIDirectInputDevice8::GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{

	HRESULT Result = g_pDInDev8->GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);
	switch (rgdod->dwOfs)
	{
	case DIK_F1:
		if (rgdod->dwData !=0 )
		{
			Beep(1500,100);
			Beep(1250,50);
		}

		rgdod->dwData =0;
		break;
	}
	return Result;
}

ULONG APIENTRY hkIDirectInputDevice8::Release(void)
{
	return g_pDInDev8->Release();
}

HRESULT APIENTRY hkIDirectInputDevice8::QueryInterface(REFIID iid, void ** ppvObject)
{
	return g_pDInDev8->QueryInterface(iid, ppvObject);
}

ULONG APIENTRY hkIDirectInputDevice8::AddRef(void)
{
	return g_pDInDev8->AddRef();
}

HRESULT APIENTRY hkIDirectInputDevice8::Acquire()
{
	return g_pDInDev8->Acquire();
}

HRESULT APIENTRY hkIDirectInputDevice8::BuildActionMap(LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags)
{
	return g_pDInDev8->BuildActionMap(lpdiaf, lpszUserName, dwFlags);
}

HRESULT APIENTRY hkIDirectInputDevice8::CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT *ppdeff, LPUNKNOWN punkOuter)
{
	return g_pDInDev8->CreateEffect(rguid, lpeff, ppdeff, punkOuter);
}

HRESULT APIENTRY hkIDirectInputDevice8::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
{
	return g_pDInDev8->EnumCreatedEffectObjects(lpCallback, pvRef, fl);
}

HRESULT APIENTRY hkIDirectInputDevice8::EnumEffects(LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType)
{
	return g_pDInDev8->EnumEffects(lpCallback, pvRef, dwEffType);
}

HRESULT APIENTRY hkIDirectInputDevice8::EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
{
	return g_pDInDev8->EnumEffectsInFile(lpszFileName, pec, pvRef, dwFlags);
}

HRESULT APIENTRY hkIDirectInputDevice8::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return g_pDInDev8->EnumObjects(lpCallback, pvRef, dwFlags);
}

HRESULT APIENTRY hkIDirectInputDevice8::Escape(LPDIEFFESCAPE pesc)
{
	return g_pDInDev8->Escape(pesc);
}

HRESULT APIENTRY hkIDirectInputDevice8::GetCapabilities(LPDIDEVCAPS lpDIDevCaps)
{
	HRESULT hRes = g_pDInDev8->GetCapabilities(lpDIDevCaps);
	return hRes;
}

HRESULT APIENTRY hkIDirectInputDevice8::GetDeviceInfo(LPDIDEVICEINSTANCE pdidi)
{
	return g_pDInDev8->GetDeviceInfo(pdidi);
}

HRESULT APIENTRY hkIDirectInputDevice8::GetDeviceState(DWORD cbData, LPVOID lpvData)
{
	return g_pDInDev8->GetDeviceState(cbData, lpvData);
}

HRESULT APIENTRY hkIDirectInputDevice8::GetEffectInfo(LPDIEFFECTINFO pdei, REFGUID rguid)
{
	return g_pDInDev8->GetEffectInfo(pdei, rguid);
}

HRESULT APIENTRY hkIDirectInputDevice8::GetForceFeedbackState(LPDWORD pdwOut)
{
	return g_pDInDev8->GetForceFeedbackState(pdwOut);
}

HRESULT APIENTRY hkIDirectInputDevice8::GetImageInfo(LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader)
{
	return g_pDInDev8->GetImageInfo(lpdiDevImageInfoHeader);
}

HRESULT APIENTRY hkIDirectInputDevice8::GetObjectInfo(LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow)
{
	return g_pDInDev8->GetObjectInfo(pdidoi, dwObj, dwHow);
}

HRESULT APIENTRY hkIDirectInputDevice8::GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph)
{
	return g_pDInDev8->GetProperty(rguidProp, pdiph);
}

HRESULT APIENTRY hkIDirectInputDevice8::Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
	return g_pDInDev8->Initialize(hinst, dwVersion, rguid);
}

HRESULT APIENTRY hkIDirectInputDevice8::Poll()
{
	return g_pDInDev8->Poll();
}

HRESULT APIENTRY hkIDirectInputDevice8::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return g_pDInDev8->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT APIENTRY hkIDirectInputDevice8::SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl)
{
	return g_pDInDev8->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
}

HRESULT APIENTRY hkIDirectInputDevice8::SendForceFeedbackCommand(DWORD dwFlags)
{
	return g_pDInDev8->SendForceFeedbackCommand(dwFlags);
}

HRESULT APIENTRY hkIDirectInputDevice8::SetActionMap(LPDIACTIONFORMAT lpdiActionFormat, LPCTSTR lptszUserName, DWORD dwFlags)
{
	return g_pDInDev8->SetActionMap(lpdiActionFormat, lptszUserName, dwFlags);
}

HRESULT APIENTRY hkIDirectInputDevice8::SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
{
	return g_pDInDev8->SetCooperativeLevel(hwnd, dwFlags);
}

HRESULT APIENTRY hkIDirectInputDevice8::SetDataFormat(LPCDIDATAFORMAT lpdf)
{
	return g_pDInDev8->SetDataFormat(lpdf);
}

HRESULT APIENTRY hkIDirectInputDevice8::SetEventNotification(HANDLE hEvent)
{
	return g_pDInDev8->SetEventNotification(hEvent);
}

HRESULT APIENTRY hkIDirectInputDevice8::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
{
	return g_pDInDev8->SetProperty(rguidProp, pdiph);
}

HRESULT APIENTRY hkIDirectInputDevice8::Unacquire()
{
	return g_pDInDev8->Unacquire();
}

HRESULT APIENTRY hkIDirectInputDevice8::WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
{
	return g_pDInDev8->WriteEffectToFile(lpszFileName, dwEntries, rgDiFileEft, dwFlags);
}
