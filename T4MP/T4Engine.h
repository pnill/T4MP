// Generated using ReClass 2016
#pragma once

class T4Engine;
class T4Game;
class EngineObject;
class BlendedCamera;
class Object;
class BlendedCamera;
class Actor;
class DMPlayer;
class Health;
class WeaponWheel;
class N00000F90;
class Player;

struct Vector3 {
	float x;
	float y;
	float z;
};

class T4Engine
{
public:
	T4Game* pT4Game; //0x0000 
	char pad_0x0004[0x3C]; //0x0004

}; //Size=0x0040

class T4Game
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //

	char pad_0x0004[0x1C]; //0x0004
	char* LevelPath; //0x0020 
	char pad_0x0024[0x9C]; //0x0024
	EngineObject* pEngineObjects; //0x00C0 

}; //Size=0x00C4

class EngineObject
{
public:
	BlendedCamera* pCameraArray[2]; //0x0000 
	char _0x0004[24];

};//Size=0x001C


class BlendedCamera
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //

	char pad_0x0004[0x58]; //0x0004
	char* ObjectName; //0x005C 
	char pad_0x0060[0x58C]; //0x0060
	Player* pPlayer; //0x05EC 
	char pad_0x05F0[0x74]; //0x05F0
	Actor* pActor; //0x0664 
	char pad_0x0668[0x1C]; //0x0668

}; //Size=0x0684

class Actor
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //

	char pad_0x0004[0x298]; //0x0004
	DMPlayer* pDMPlayer; //0x029C 

}; //Size=0x02A0

class DMPlayer
{
public:
	virtual void Function0(); //
	virtual void nullsub_6(); //
	virtual void Function2(); //
	virtual void input_query(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void Function22(); //
	virtual void Function23(); //
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27(); //
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual void Function45(); //
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual void Function60(); //
	virtual void Function61(); //
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //
	virtual void Function75(); //
	virtual void Function76(); //
	virtual void Function77(); //
	virtual void Function78(); //
	virtual void Function79(); //
	virtual void Function80(); //
	virtual void Function81(); //
	virtual void Function82(); //
	virtual void Function83(); //
	virtual void Function84(); //
	virtual void Function85(); //
	virtual void Function86(); //
	virtual void Function87(); //
	virtual void Function88(); //
	virtual void Function89(); //
	virtual void Function90(); //
	virtual void Function91(); //
	virtual void Function92(); //
	virtual void Function93(); //
	virtual void Function94(); //
	virtual void Function95(); //
	virtual void Function96(); //
	virtual void Function97(); //
	virtual void Function98(); //
	virtual void Function99(); //
	virtual void Function100(); //
	virtual void Function101(); //
	virtual void Function102(); //
	virtual void Function103(); //
	virtual void Function104(); //
	virtual void Function105(); //
	virtual void Function106(); //
	virtual void Function107(); //
	virtual void Function108(); //
	virtual void Function109(); //
	virtual void Function110(); //
	virtual void Function111(); //
	virtual void Function112(); //
	virtual void Function113(); //
	virtual void Function114(); //
	virtual void Function115(); //
	virtual void Function116(); //
	virtual void Function117(); //
	virtual void Function118(); //
	virtual void Function119(); //
	virtual void Function120(); //
	virtual void Function121(); //
	virtual void Function122(); //
	virtual void Function123(); //
	virtual void Function124(); //
	virtual void Function125(); //
	virtual void Function126(); //
	virtual void Function127(); //
	virtual void Function128(); //
	virtual void Function129(); //
	virtual void Function130(); //
	virtual void Function131(); //
	virtual int jump(int a2, float a3); //
	virtual int crouch(int a2, float a3); //
	virtual void fire_weapon(int a1, int a2); 
	virtual void fire_held(float time_held, int a2); 
	virtual void fire_release(float time_held); 
	virtual void Function137(); //
	virtual void Function138(); //
	virtual void Function139(); //
	virtual void Function140(); //
	virtual void Function141(); //
	virtual void Function142(); //
	virtual void Function143(); //
	virtual void Function144(); //
	virtual void Function145(); //
	virtual void Function146(); //
	virtual void Function147(); //
	virtual void Function148(); //
	virtual void Function149(); //
	virtual void Function150(); //
	virtual void Function151(); //
	virtual void Function152(); //
	virtual void Function153(); //
	virtual void Function154(); //
	virtual void Function155(); //
	virtual void Function156(); //
	virtual void Function157(); //
	virtual void Function158(); //
	virtual void Function159(); //
	virtual void Function160(); //
	virtual void Function161(); //
	virtual void Function162(); //
	virtual void Function163(); //
	virtual void Function164(); //
	virtual void Function165(); //
	virtual void Function166(); //
	virtual void Function167(); //
	virtual void Function168(); //
	virtual void Function169(); //
	virtual void Function170(); //
	virtual void Function171(); //
	virtual void Function172(); //
	virtual void Function173(); //
	virtual void Function174(); //
	virtual void Function175(); //
	virtual void Function176(); //
	virtual void Function177(); //
	virtual void Function178(); //
	virtual void Function179(); //
	virtual void Function180(); //
	virtual void Function181(); //
	virtual void Function182(); //
	virtual void Function183(); //
	virtual void Function184(); //
	virtual void Function185(); //
	virtual void Function186(); //
	virtual void Function187(); //
	virtual void Function188(); //
	virtual void Function189(); //
	virtual void Function190(); //
	virtual void Function191(); //
	virtual void Function192(); //
	virtual void Function193(); //
	virtual void Function194(); //
	virtual void Function195(); //
	virtual void Function196(); //
	virtual void Function197(); //
	virtual void Function198(); //
	virtual void Function199(); //
	virtual void Function200(); //
	virtual void Function201(); //
	virtual void Function202(); //
	virtual void Function203(); //
	virtual void Function204(); //
	virtual void Function205(); //
	virtual void Function206(); //
	virtual void Function207(); //
	virtual void Function208(); //
	virtual void Function209(); //
	virtual void Function210(); //
	virtual void Function211(); //
	virtual void Function212(); //
	virtual void Function213(); //
	virtual void Function214(); //
	virtual void Function215(); //
	virtual void Function216(); //
	virtual void Function217(); //
	virtual void Function218(); //
	virtual void Function219(); //
	virtual void Function220(); //
	virtual void Function221(); //
	virtual void Function222(); //
	virtual void Function223(); //
	virtual void Function224(); //
	virtual void Function225(); //
	virtual void Function226(); //
	virtual void Function227(); //
	virtual void Function228(); //
	virtual void Function229(); //
	virtual void Function230(); //
	virtual void Function231(); //
	virtual void Function232(); //
	virtual void Function233(); //
	virtual void Function234(); //
	virtual void Function235(); //
	virtual void Function236(); //
	virtual void Function237(); //
	virtual void Function238(); //
	virtual void Function239(); //
	virtual void Function240(); //
	virtual void Function241(); //
	virtual void Function242(); //
	virtual void Function243(); //
	virtual void Function244(); //
	virtual void Function245(); //
	virtual void Function246(); //
	virtual void Function247(); //
	virtual void Function248(); //
	virtual void Function249(); //
	virtual void Function250(); //
	virtual void Function251(); //
	virtual void Function252(); //
	virtual void Function253(); //
	virtual void Function254(); //
	virtual void Function255(); //
	virtual void Function256(); //
	virtual void Function257(); //
	virtual void Function258(); //
	virtual void Function259(); //
	virtual void Function260(); //
	virtual void Function261(); //
	virtual void Function262(); //
	virtual void Function263(); //
	virtual void Function264(); //
	virtual void Function265(); //
	virtual void Function266(); //
	virtual void Function267(); //
	virtual void Function268(); //
	virtual void Function269(); //
	virtual void Function270(); //
	virtual void Function271(); //
	virtual void Function272(); //
	virtual void Function273(); //
	virtual void Function274(); //
	virtual void Function275(); //
	virtual void KillPlayer(int Unk1, int DeathType, void* DamagePtr); //
	virtual void Function277(); //

	char pad_0x0004[0x18]; //0x0004
	__int8 N0000040D; //0x001C 
	__int8 N00000535; //0x001D 
	__int8 bEnabled; //0x001E 
	__int8 N00000536; //0x001F 
	__int8 bThirdPerson; //0x0020 
	__int8 bEnabled2; //0x0021 
	__int8 N0000053F; //0x0022 
	__int8 N0000053D; //0x0023 
	__int8 N0000040F; //0x0024 
	__int8 N00000543; //0x0025 
	__int8 N00000546; //0x0026 
	__int8 N00000544; //0x0027 
	char pad_0x0028[0x10]; //0x0028
	Vector3 POS; //0x0038 
	char pad_0x0044[0x18]; //0x0044
	char* PlayerName; //0x005C 
	char pad_0x0060[0x94]; //0x0060
	float ViewX; //0x00F4 
	char pad_0x00F8[0xF0]; //0x00F8
	Health* pHealth; //0x01E8 
	char pad_0x01EC[0x1B8]; //0x01EC
	float PlayerAction; //0x03A4 
	char pad_0x03A8[0x2C]; //0x03A8
	float CameraHeight; //0x03D4 
	char pad_0x03D8[0x24]; //0x03D8
	float ViewY; //0x03FC 
	char pad_0x0400[0x41C]; //0x0400
	__int32 UnCrouchAction; //0x081C 
	char pad_0x0820[0x10E0]; //0x0820
	float Walk_left; //0x1900 
	float Walk_right; //0x1904 
	float Walk_forward; //0x1908 
	float Walk_backward; //0x190C 
	char pad_0x1910[0x38]; //0x1910
	char N00000BA4[8]; //0x1BC5980 
	char pad_0x1950[0x9C]; //0x1950
	__int32 pWeapon; //0x19EC 
	WeaponWheel* pWeaponWheel; //0x19F0 
	char pad_0x19F4[0x24]; //0x19F4
	__int32 Weapon_switch; //0x1A18 
	float Weapon_switch_time; //0x1A1C 
	char pad_0x1A20[0x28]; //0x1A20
	__int32 Weapon_slot; //0x1A48 
	char pad_0x1A4C[0x150]; //0x1A4C
	char* N00000D64; //0x1B9C 
	char* N00000D65; //0x1BA0 
	char pad_0x1BA4[0x48C]; //0x1BA4
	char* N00000E8D; //0x2030 
	char* N00000E8E; //0x2034 
	char* N00000E8F; //0x2038 
	char* N00000E90; //0x203C 
	char* N00000E91; //0x2040 
	char* N00000E92; //0x2044 
	char* N00000E93; //0x2048 
	char* N00000E94; //0x204C 
	char* N00000E95; //0x2050 
	char* N00000E96; //0x2054 
	char* N00000E97; //0x2058 
	char* N00000E98; //0x205C 
	char* N00000E99; //0x2060 
	char* N00000E9A; //0x2064 
	char pad_0x2068[0x80]; //0x2068
	N00000F90* N00000EBB; //0x20E8 
	char pad_0x20EC[0x2B4]; //0x20EC
	char* N00000F69; //0x23A0 
	char* N00000F6A; //0x23A4 
	char pad_0x23A8[0x50]; //0x23A8

}; //Size=0x23F8

class Health
{
public:
	float Current; //0x0000 
	float Max; //0x0004 

}; //Size=0x0008

class WeaponWheel
{
public:
	__int32 bHas_WarClub; //0x0000 
	__int32 UnkValue; //0x0004 
	__int32 UnkValue2; //0x0008 
	__int32 UnkValue3; //0x000C 
	__int32 WarClubID; //0x0010 
	__int32 WarClubVal1; //0x0014 
	__int32 WarClubVal2; //0x0018 
	char pad_0x001C[0x4]; //0x001C
	__int32 bHas_WarClub2; //0x0020 
	__int32 bHas_Bow1; //0x0024 
	__int32 BowID; //0x0028 
	__int32 Bow_Normal_Ammo; //0x002C 
	__int32 Bow_Explosive_Ammo; //0x0030 
	__int32 Bow_Poison_Ammo; //0x0034 
	__int32 bBow_Has_Normal; //0x0038 
	__int32 bBow_Has_Explosive; //0x003C 
	__int32 bBow_Has_Poison; //0x0040 
	char pad_0x0044[0x4]; //0x0044
	__int32 bHas_Bow2; //0x0048 
	__int32 bHas_TekBow; //0x004C 
	__int32 TekBowID; //0x0050 
	__int32 Tekbow_Normal_Ammo; //0x0054 
	__int32 TekBow_Explosive_Ammo; //0x0058 
	__int32 TekBow_Poison_Ammo; //0x005C 
	__int32 bTekbow_Has_Normal; //0x0060 
	__int32 bTekBow_Has_Explosive; //0x0064 
	__int32 bTekBow_Has_Poison; //0x0068 
	char pad_0x006C[0x4]; //0x006C
	__int32 bHas_Tekbow2; //0x0070 
	__int32 bHas_SpikeGrenade; //0x0074 
	__int32 SpikeGrenadeID; //0x0078 
	__int32 SpikeGrenade_Ammo; //0x007C 
	__int32 SpikeGrenade_Ammo2; //0x0080 
	__int32 SpikeGrenade_Ammo3; //0x0084 
	__int32 bSpikeGrenade_Has_Ammo; //0x0088 
	__int32 bSpikeGrenade_Has_Ammo2; //0x008C 
	__int32 bSpikeGrenade_Has_Ammo3; //0x0090 
	char pad_0x0094[0x4]; //0x0094
	__int32 bHas_SpikeGrenade2; //0x0098 
	__int32 bHas_Pistol; //0x009C 
	__int32 PistolID; //0x00A0 
	__int32 Pistol_Ammo; //0x00A4 
	__int32 Pistol_Ammo2; //0x00A8 
	__int32 Pistol_Ammo3; //0x00AC 
	__int32 bPistol_Has_Ammo; //0x00B0 
	__int32 bPistol_Has_Ammo2; //0x00B4 
	__int32 bPistol_Has_Ammo3; //0x00B8 
	char pad_0x00BC[0x4]; //0x00BC
	__int32 bHas_Pistol2; //0x00C0 
	__int32 bHas_ShotGun; //0x00C4 
	__int32 ShotGunID; //0x00C8 
	__int32 ShotGun_Ammo; //0x00CC 
	__int32 ShotGun_Ammo1; //0x00D0 
	__int32 ShotGun_Ammo2; //0x00D4 
	__int32 bShotGun_Has_Ammo1; //0x00D8 
	__int32 bShotGun_Has_Ammo2; //0x00DC 
	__int32 bShotGun_Has_Ammo3; //0x00E0 
	char pad_0x00E4[0x4]; //0x00E4
	__int32 bHas_ShotGun2; //0x00E8 
	__int32 bHas_Fleechete; //0x00EC 
	__int32 FleecheteID; //0x00F0 
	__int32 Fleechete_Ammo; //0x00F4 
	__int32 MiniGun_Ammo; //0x00F8 
	__int32 Fleechete_Ammo2; //0x00FC 
	__int32 bFleechete_Has_Ammo; //0x0100 
	__int32 bMiniGun_Has_Ammo; //0x0104 
	__int32 bFleechete_Has_Ammo2; //0x0108 
	char pad_0x010C[0x4]; //0x010C
	__int32 bHas_Fleechete2; //0x0110 
	__int32 bHas_RocketLauncher; //0x0114 
	__int32 RocketLauncherID; //0x0118 
	__int32 RocketLauncher_Ammo; //0x011C 
	__int32 RocketLauncher_Ammo2; //0x0120 
	__int32 RocketLauncher_Ammo3; //0x0124 
	__int32 bRocketLauncher_Has_Ammo; //0x0128 
	__int32 bRocketLauncher_Has_Ammo1; //0x012C 
	__int32 bRocketLauncher_Has_Ammo2; //0x0130 
	char pad_0x0134[0x4]; //0x0134
	__int32 bHas_RocketLauncher2; //0x0138 
	__int32 bHas_PlasmaCannon; //0x013C 
	__int32 PlasmaCannonID; //0x0140 
	__int32 PlasmaCannon_Ammo; //0x0144 
	__int32 PlasmaCannon_Ammo2; //0x0148 
	__int32 PlasmaCannon_Ammo3; //0x014C 
	__int32 bPlasmaCannon_Has_Ammo; //0x0150 
	__int32 bPlasmaCannon_Has_Ammo2; //0x0154 
	__int32 bPlasmaCannon_Has_Ammo3; //0x0158 
	char pad_0x015C[0x4]; //0x015C
	__int32 bHas_PlasmaCannon2; //0x0160 
	__int32 bHas_FlameThrower; //0x0164 
	__int32 FlameThrowerID; //0x0168 
	__int32 FlameThrower_Ammo; //0x016C 
	__int32 FlameThrower_Ammo2; //0x0170 
	__int32 FlameThrower_Ammo3; //0x0174 
	__int32 bFlameThrower_Has_Ammo; //0x0178 
	__int32 bFlameThrower_Has_Ammo2; //0x017C 
	__int32 bFlameThrower_Has_Ammo3; //0x0180 
	char pad_0x0184[0x4]; //0x0184
	__int32 bHas_FlameThrower2; //0x0188 
	__int32 bHas_SpiderMine; //0x018C 
	__int32 SpiderMineID; //0x0190 
	__int32 SpiderMine_Ammo; //0x0194 
	__int32 SpiderMine_Ammo2; //0x0198 
	__int32 SpiderMine_Ammo3; //0x019C 
	__int32 bSpiderMine_Has_Ammo; //0x01A0 
	__int32 bSpiderMine_Has_Ammo2; //0x01A4 
	__int32 bSpiderMine_Has_Ammo3; //0x01A8 
	char pad_0x01AC[0x4]; //0x01AC
	__int32 bHas_SpiderMine2; //0x01B0 
	__int32 bHas_GravityGun; //0x01B4 
	__int32 GravityGunID; //0x01B8 
	__int32 GravityGun_Ammo; //0x01BC 
	__int32 GravityGun_Ammo2; //0x01C0 
	__int32 GravityGun_Ammo3; //0x01C4 
	__int32 bGravityGun_Has_Ammo; //0x01C8 
	__int32 bGravityGun_Has_Ammo2; //0x01CC 
	__int32 bGravityGun_Has_Ammo3; //0x01D0 
	char pad_0x01D4[0x4]; //0x01D4
	__int32 bHas_GravityGun2; //0x01D8 
	__int32 bHas_DarkMatterCube; //0x01DC 
	__int32 DarkMatterCubeID; //0x01E0 
	__int32 DarkMatterCube_Ammo; //0x01E4 
	__int32 DarkMatterCube_Ammo2; //0x01E8 
	__int32 DarkMatterCube_Ammo3; //0x01EC 
	__int32 bDarkMatterCube_Has_Ammo; //0x01F0 
	__int32 bDarkMatterCube_Has_Ammo2; //0x01F4 
	__int32 bDarkMatterCube_Has_Ammo3; //0x01F8 
	char pad_0x01FC[0x4]; //0x01FC
	__int32 bHas_DarkMatterCube2; //0x0200 
	__int32 bHas_CrossBow; //0x0204 
	__int32 CrossBowID; //0x0208 
	__int32 CrossBow_Normal_Ammo; //0x020C 
	__int32 CrossBow_Explosive_Ammo; //0x0210 
	__int32 CrossBow_Poison_Ammo; //0x0214 
	__int32 bCrossBow_Has_Normal; //0x0218 
	__int32 bCrossBow_Has_Explosive; //0x021C 
	__int32 bCrossBow_Has_Poison; //0x0220 
	char pad_0x0224[0x4]; //0x0224
	__int32 bHas_CrossBow2; //0x0228 

}; //Size=0x022C

class N00000F90
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //

}; //Size=0x0004

class Player
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void Function22(); //
	virtual void Function23(); //
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27(); //
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual void Function45(); //
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual void Function60(); //
	virtual void Function61(); //
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //
	virtual void Function75(); //
	virtual void Function76(); //
	virtual void Function77(); //
	virtual void Function78(); //
	virtual void Function79(); //
	virtual void Function80(); //
	virtual void Function81(); //
	virtual void Function82(); //
	virtual void Function83(); //
	virtual void Function84(); //
	virtual void Function85(); //
	virtual void Function86(); //
	virtual void Function87(); //
	virtual void Function88(); //
	virtual void Function89(); //
	virtual void Function90(); //
	virtual void Function91(); //
	virtual void Function92(); //
	virtual void Function93(); //
	virtual void Function94(); //
	virtual void Function95(); //
	virtual void Function96(); //
	virtual void Function97(); //
	virtual void Function98(); //
	virtual void Function99(); //
	virtual void Function100(); //
	virtual void Function101(); //
	virtual void Function102(); //
	virtual void Function103(); //
	virtual void Function104(); //
	virtual void Function105(); //
	virtual void Function106(); //
	virtual void Function107(); //
	virtual void Function108(); //
	virtual void Function109(); //
	virtual void Function110(); //
	virtual void Function111(); //
	virtual void Function112(); //
	virtual void Function113(); //
	virtual void Function114(); //
	virtual void Function115(); //
	virtual void Function116(); //
	virtual void Function117(); //
	virtual void Function118(); //
	virtual void Function119(); //
	virtual void Function120(); //
	virtual void Function121(); //
	virtual void Function122(); //
	virtual void Function123(); //
	virtual void Function124(); //
	virtual void Function125(); //
	virtual void Function126(); //
	virtual void Function127(); //
	virtual void Function128(); //
	virtual void Function129(); //
	virtual void Function130(); //
	virtual void Function131(); //
	virtual void Function132(); //
	virtual void Function133(); //
	virtual void respawn(int a1, int a2); //
	virtual void Function135(); //
	virtual void Function136(); //
	virtual void Function137(); //
	virtual void Function138(); //
	virtual void Function139(); //
	virtual void Function140(); //
	virtual void Function141(); //
	virtual void Function142(); //
	virtual void Function143(); //
	virtual void Function144(); //
	virtual void Function145(); //
	virtual void Function146(); //
	virtual void Function147(); //
	virtual void Function148(); //
	virtual void Function149(); //
	virtual void Function150(); //
	virtual void Function151(); //
	virtual void Function152(); //
	virtual void Function153(); //
	virtual void Function154(); //
	virtual void Function155(); //
	virtual void Function156(); //
	virtual void Function157(); //
	virtual void Function158(); //
	virtual void Function159(); //
	virtual void Function160(); //
	virtual void Function161(); //
	virtual void Function162(); //
	virtual void Function163(); //
	virtual void Function164(); //
	virtual void Function165(); //
	virtual void Function166(); //
	virtual void Function167(); //
	virtual void Function168(); //
	virtual void Function169(); //
	virtual void Function170(); //
	virtual void Function171(); //
	virtual void Function172(); //
	virtual void Function173(); //
	virtual void Function174(); //
	virtual void Function175(); //
	virtual void Function176(); //
	virtual void Function177(); //
	virtual void Function178(); //
	virtual void Function179(); //
	virtual void Function180(); //
	virtual void Function181(); //
	virtual void Function182(); //
	virtual void Function183(); //
	virtual void Function184(); //
	virtual void Function185(); //
	virtual void Function186(); //
	virtual void Function187(); //
	virtual void Function188(); //
	virtual void Function189(); //
	virtual void Function190(); //
	virtual void Function191(); //
	virtual void Function192(); //
	virtual void Function193(); //
	virtual void Function194(); //
	virtual void Function195(); //
	virtual void Function196(); //
	virtual void Function197(); //
	virtual void Function198(); //
	virtual void Function199(); //
	virtual void Function200(); //
	virtual void Function201(); //
	virtual void Function202(); //
	virtual void Function203(); //
	virtual void Function204(); //
	virtual void Function205(); //
	virtual void Function206(); //
	virtual void Function207(); //
	virtual void Function208(); //
	virtual void Function209(); //
	virtual void Function210(); //
	virtual void Function211(); //
	virtual void Function212(); //
	virtual void Function213(); //
	virtual void Function214(); //
	virtual void Function215(); //
	virtual void Function216(); //
	virtual void Function217(); //
	virtual void Function218(); //
	virtual void Function219(); //
	virtual void Function220(); //
	virtual void Function221(); //
	virtual void Function222(); //
	virtual void Function223(); //
	virtual void Function224(); //
	virtual void Function225(); //
	virtual void Function226(); //
	virtual void Function227(); //
	virtual void Function228(); //
	virtual void Function229(); //
	virtual void Function230(); //
	virtual void Function231(); //
	virtual void Function232(); //
	virtual void Function233(); //
	virtual void Function234(); //
	virtual void Function235(); //
	virtual void Function236(); //
	virtual void Function237(); //
	virtual void Function238(); //
	virtual void Function239(); //
	virtual void Function240(); //
	virtual void Function241(); //
	virtual void Function242(); //
	virtual void Function243(); //
	virtual void Function244(); //
	virtual void Function245(); //
	virtual void Function246(); //
	virtual void Function247(); //
	virtual void Function248(); //
	virtual void Function249(); //
	virtual void Function250(); //
	virtual void Function251(); //
	virtual void Function252(); //
	virtual void Function253(); //
	virtual void Function254(); //
	virtual void Function255(); //
	virtual void Function256(); //
	virtual void Function257(); //
	virtual void Function258(); //
	virtual void Function259(); //
	virtual void Function260(); //
	virtual void Function261(); //
	virtual void Function262(); //
	virtual void Function263(); //
	virtual void Function264(); //
	virtual void Function265(); //
	virtual void Function266(); //
	virtual void Function267(); //
	virtual void Function268(); //
	virtual void Function269(); //
	virtual void Function270(); //
	virtual void Function271(); //
	virtual void Function272(); //
	virtual void Function273(); //
	virtual void Function274(); //
	virtual void Function275(); //
	virtual void Function276(); //
	virtual void Function277(); //

	char pad_0x0004[0x58]; //0x0004
	char* PlayerName; //0x005C 
	char pad_0x0060[0xF4]; //0x0060

}; //Size=0x0154

