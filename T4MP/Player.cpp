#include "stdafx.h"
#include "Player.h"
int base = *(int*)(0x6B52E4);


void TurokPlayer::set_index(int index)
{
	this->index = index;
}

void TurokPlayer::set_view(ViewAngle* view)
{

}

void TurokPlayer::set_position(Position* pos)
{
	int base_2 = 0;
	int base_3 = 0;
	int base_4 = 0;
	int player = 0;

	if (base)
		base_2 = *(int*)(base + 0x0C0);
	if (base_2)
		base_3 = *(int*)(base_2 + (this->index * 4));
	if (base_3)
		base_4 = *(int*)(base_3 + 0x664);
	if (base_4)
		player = *(int*)(base_4 + 0x29C);
	if (player)
		*(Position*)(player + 0x38) = *pos;
}

void TurokPlayer::set_weapon(TurokWeapon* weapon)
{

}

void TurokPlayer::set_animation(float animation)
{

}

void TurokPlayer::set_health(float health)
{

}

ViewAngle* TurokPlayer::get_view()
{
	ViewAngle* view = NULL;
	return view;
}

Position* TurokPlayer::get_position()
{
	Position* pos = NULL;

	int base_2 = 0;
	int base_3 = 0;
	int base_4 = 0;
	int player = 0;

	if (base)
		base_2 = *(int*)(base + 0x0C0);
	if (base_2)
		base_3 = *(int*)(base_2 + (this->index * 4));
	if (base_3)
		base_4 = *(int*)(base_3 + 0x664);
	if (base_4)
		player = *(int*)(base_4 + 0x29C);
	if(player)
		pos = (Position*)(player + 0x38);

	return pos;
}

float TurokPlayer::get_health()
{
	return 100.0f;
}

TurokWeapon* TurokPlayer::get_weapon()
{
	TurokWeapon* weapon = NULL;
	return weapon;
}

float TurokPlayer::get_animation()
{
	return 0.1f;
}