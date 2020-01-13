#pragma once
#include "T4Engine.h"

class TurokEngine {
public:
	void SetModHooks();
	DMPlayer *SpawnPlayer();
	DMPlayer* GetDMPlayer(int index);
	void UnCrouch(DMPlayer* thisptr);
};

void SwitchWeapon(void* WeaponPointer, int WeaponID);
int WeaponModify(DMPlayer* pDMPlayer);

//int tModifyWeapon(DMPlayer* pDMPlayer, int a1, int a2);