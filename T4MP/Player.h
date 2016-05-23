#pragma once
#include "Weapon.h"

struct Position
{
	float x;
	float y;
	float z;
};

struct ViewAngle
{
	float x;
	float y;
};

class TurokPlayer
{
public:
	void set_index(int index);

	void set_position(Position* pos);
	void set_view(ViewAngle *view);
	void set_weapon(TurokWeapon* Weapon);
	void set_health(float health);
	void set_animation(float animation);

	Position *get_position();
	ViewAngle *get_view();
	TurokWeapon* get_weapon();
	float get_health();
	float get_animation();
	

protected:

private:
	int index;
};