#pragma once
#include "T4Engine.h"

class TurokEngine {
public:
	bool jump_set = false;
	bool fire_set = false;
	bool fire_hold = false;
	bool fire_release = false;
	bool crouch = false;

	float fire_hold_time = 0.0f;
	float fire_release_time = 0.0f;

	void print_text(char* text);
	void SetModHooks();
	DMPlayer *SpawnPlayer();
	DMPlayer* GetDMPlayer(int index);
	void UnCrouch(DMPlayer* thisptr);
};

void FireWeapon();

