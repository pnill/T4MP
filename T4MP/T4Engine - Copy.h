//Generated using ReClass 2013 Mod by CypherPresents

struct Vec3 {
	float x;
	float y;
	float z;
};

class T4Engine;
class T4Game;
class EngineObject;
class BlendedCamera;
class Actor;
class N1959C6DD;
class DMPlayer;
class Health;
class LevelPath;
class UnkWepRelated_1;
class UnkWeapRelated_2;
class TextPtrFill;
class N19AE12B7;
class N19AEAA95;
class PtrFillUnk;
class WeaponWheel;
class WeapRelate_unk4;
class WeaponRelate_unk5;
class WeaponRelate_unk6;
class N1AC074CE;
class PlayerMovement;

class T4Engine
{
public:
	T4Game* pT4Game; //0x0000 
char _0x0004[60];

};//Size=0x0040

class T4Game
{
public:
char _0x0000[32];
	LevelPath* N1957559D; //0x0020 
char _0x0024[156];
	EngineObject* pEngineObjects; //0x00C0 
char _0x00C4[4];

};//Size=0x00C8

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

char _0x0004[52];
	float rCamera_X; //0x0038 
	float rCamera_Y; //0x003C 
	float rCamera_Z; //0x0040 
char _0x0044[56];
	float UnkFloat1; //0x007C 
	float UnkFloat2; //0x0080 
	float UnkFloat3; //0x0084 
	PtrFillUnk* N195BFFCC; //0x0088 
char _0x008C[32];
	float rCamera2_X; //0x00AC 
	float rCamera2_Y; //0x00B0 
	float rCamera2_Z; //0x00B4 
char _0x00B8[12];
	float N195BFFBD; //0x00C4 
	float N195BFFBC; //0x00C8 
char _0x00CC[36];
	float N195BFFB2; //0x00F0 
	float N195BFFB1; //0x00F4 
char _0x00F8[192];
	float TickCount; //0x01B8 
char _0x01BC[128];
	float rPOS3_X; //0x023C 
	float rPOS3_Y; //0x0240 
	float rPOS3_Z; //0x0244 
char _0x0248[4];
	float rUnkFloat; //0x024C 
char _0x0250[4];
	float rUnkFloat2; //0x0254 
char _0x0258[4];
	float rUnkFloat3; //0x025C 
	float rUnkFloat4; //0x0260 
	float rUnkFloat5; //0x0264 
char _0x0268[4];
	float rUnkFloat6; //0x026C 
	float rUnkFloat7; //0x0270 
	float rUnkFloat8; //0x0274 
char _0x0278[16];
	float rUnkFloat9; //0x0288 
char _0x028C[104];
	float N195BFF31; //0x02F4 
char _0x02F8[4];
	float N195BFF2F; //0x02FC 
	float N195BFF2E; //0x0300 
	float N195BFF2D; //0x0304 
char _0x0308[32];
	float N195BFF24; //0x0328 
char _0x032C[216];
	float N195C17FA; //0x0404 
	float N195C17F9; //0x0408 
	float N195C17F8; //0x040C 
	float N195C17F7; //0x0410 
	float N195C17F6; //0x0414 
	float N195C17F5; //0x0418 
	float N195C17F4; //0x041C 
	float N195C17F3; //0x0420 
char _0x0424[28];
	float N195C1B37; //0x0440 
	float N195C1B36; //0x0444 
	float N195C1B35; //0x0448 
char _0x044C[24];
	float N195C1B2E; //0x0464 
	float N195C1B2D; //0x0468 
	float N195C1B2C; //0x046C 
char _0x0470[4];
	float N195C1B2A; //0x0474 
	float N195C1B29; //0x0478 
	float N195C1B28; //0x047C 
	float N195C2411; //0x0480 
	float N195C2410; //0x0484 
	float N195C240F; //0x0488 
	float N195C240E; //0x048C 
	float N195C240D; //0x0490 
	float N195C240C; //0x0494 
	float N195C240B; //0x0498 
	float N195C240A; //0x049C 
	float N195C2409; //0x04A0 
	float N195C2408; //0x04A4 
	float N197E9877; //0x04A8 
	float N195C2406; //0x04AC 
	float N195C2405; //0x04B0 
char _0x04B4[432];
	Actor* pActor; //0x0664 

};//Size=0x0668

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

char _0x0004[52];
	float rDPOS_X; //0x0038 
	float rDPOS_Y; //0x003C 
	float rDPOS_Z; //0x0040 
char _0x0044[104];
	float rDPOS2_X; //0x00AC 
	float rDPOS2_Y; //0x00B0 
	float rDPOS2_Z; //0x00B4 
char _0x00B8[424];
	__int32 FrameCount; //0x0260 
char _0x0264[56];
	DMPlayer* pDMPlayer; //0x029C 

};//Size=0x02A0

class N1959C6DD
{
public:
char _0x0000[4];

};//Size=0x0004

class DMPlayer
{
public:
	virtual void Function0(); //
	virtual void nullsub_6(); //
	virtual void Function2(); //
	virtual int input_query(); //
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
	virtual int Crouch_two(); //
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
	virtual void fire_weapon(int a1, int a2); // only used on warclub so far - called by flame thrower on first click.
	virtual void fire_held(float a1, int a2); // only used on warclub so far
	virtual void fire_weapon2(float a1); // only used on warclub so far
	virtual void Function137(); //
	virtual void Function138(); //
	virtual void Function139(); //
	virtual void weapon_mode_change_right_click(); //
	virtual void Function141(); //
	virtual void Function142(); //
	virtual void Function143(); //
	virtual void Function144(); //
	virtual void movement_key_release(); //
	virtual void Function146(); //
	virtual void Function147(); //
	virtual void Function148(); //
	virtual void weapon_switch_right(); //
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
	virtual void walk_right_relate(); //
	virtual void Function166(); //
	virtual void Function167(); //
	virtual void movement_related_3(); //
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
	virtual void crouch_related_3(); //
	virtual void crouch_related_2(float a1); //
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
	virtual void movement_related_2(); //
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

	UnkWepRelated_1* pUnkWep1; //0x0004 
char _0x0008[8];
	UnkWeapRelated_2* N19810F60; //0x0010 
char _0x0014[8];
	__int8 N19810F5D; //0x001C 
	__int8 N19C0884A; //0x001D 
	__int8 bEnabled; //0x001E 
	__int8 N19C0884B; //0x001F 
	__int8 bThirdPerson; //0x0020 
	__int8 bControlEnabled2; //0x0021 
	__int8 N19C133C8; //0x0022 
	__int8 N19C12C82; //0x0023 
	__int32 N19810F5B; //0x0024 
	__int32 N19810F5A; //0x0028 
char _0x002C[8];
	__int8 N19810F57; //0x0034 
	__int8 N19C5A774; //0x0035 
	__int8 N19C5B15A; //0x0036 
char _0x0037[1];
	Vec3 pos; //0x0038 
	float N19811DBE; //0x0044 
char _0x0048[12];
	DWORD N19615039; //0x0054 
char _0x0058[4];
	char * PlayerName; //0x005C 
char _0x0060[28];
	float N19616060; //0x007C 
	float POS; //0x0080 
	float N19852C8D; //0x0084 
char _0x0088[8];
	float N19616E6F; //0x0090 
	float N19616FA8; //0x0094 
	float N1961718E; //0x0098 
char _0x009C[4];
	float N196174FB; //0x00A0 
char _0x00A4[4];
	float N19617877; //0x00A8 
	float N19617991; //0x00AC 
	float N196181D0; //0x00B0 
	float N19618319; //0x00B4 
char _0x00B8[16];
	float rViewX; //0x00C8 
char _0x00CC[40];
	float wViewX; //0x00F4 
char _0x00F8[56];
	float N1960AF4D; //0x0130 
char _0x0134[4];
	float N1960AF4F; //0x0138 
char _0x013C[20];
	float N198149E5; //0x0150 
char _0x0154[4];
	float N19814EF8; //0x0158 
char _0x015C[4];
	float N19815449; //0x0160 
	float N1989C57B; //0x0164 
	float N198156DB; //0x0168 
	float N19815805; //0x016C 
	float N198992EB; //0x0170 
	float N19816013; //0x0174 
	float N198979DF; //0x0178 
char _0x017C[8];
	float N1981600F; //0x0184 
char _0x0188[8];
	float N1981600C; //0x0190 
char _0x0194[4];
	float N1981600A; //0x0198 
char _0x019C[4];
	float N19816008; //0x01A0 
	float N19816007; //0x01A4 
	float N19816006; //0x01A8 
char _0x01AC[12];
	float GameTick; //0x01B8 
char _0x01BC[44];
	Health* pHealth; //0x01E8 
char _0x01EC[12];
	DWORD N198AB513; //0x01F8 
char _0x01FC[8];
	DWORD UnkCollision; //0x0204 
	DWORD N198ABA14; //0x0208 
char _0x020C[12];
	DWORD N198ABA10; //0x0218 
char _0x021C[20];
	DWORD N198ABA0A; //0x0230 
char _0x0234[48];
	float N198AC400; //0x0264 
	float N198AC3FF; //0x0268 
	float N198AC3FE; //0x026C 
char _0x0270[24];
	DWORD N198ACEE5; //0x0288 
char _0x028C[96];
	float N198AD748; //0x02EC 
	float N198AD747; //0x02F0 
	float N198AD746; //0x02F4 
	float N198AD745; //0x02F8 
	float N198AD744; //0x02FC 
	float N198AE28F; //0x0300 
	float N198AE28E; //0x0304 
	float N198AE28D; //0x0308 
	float N198AE28C; //0x030C 
	float N198AE28B; //0x0310 
	float N198AE28A; //0x0314 
char _0x0318[80];
	__int8 N198AEAD2; //0x0368 
	__int8 N19E6A77A; //0x0369 
	__int8 N19E6B1AF; //0x036A 
	__int8 N19E6A77B; //0x036B 
char _0x036C[40];
	float N198AF557; //0x0394 
char _0x0398[12];
	float PlayerActionRelated; //0x03A4 
char _0x03A8[24];
	DWORD N198AFF6E; //0x03C0 
	DWORD N198AFF6D; //0x03C4 
	DWORD N198AFF6C; //0x03C8 
char _0x03CC[4];
	float rCameraHeight; //0x03D0 
	float wCameraHeight; //0x03D4 
	float N198AFF68; //0x03D8 
char _0x03DC[4];
	float N198AFF66; //0x03E0 
char _0x03E4[12];
	float N198AFF62; //0x03F0 
char _0x03F4[8];
	float ViewY; //0x03FC 
char _0x0400[8];
	float N19AA9417; //0x0408 
	float N19AA9416; //0x040C 
	float N19AA9415; //0x0410 
	float N19AA9414; //0x0414 
	DWORD WeaponCheck1; //0x0418 
char _0x041C[20];
	float N19AA940D; //0x0430 
	float N19AA940C; //0x0434 
	float N19AA940B; //0x0438 
	float N19AA940A; //0x043C 
	float N19AA9409; //0x0440 
	float N19AA9408; //0x0444 
char _0x0448[20];
	__int32 N19AA9402; //0x045C 
	float N19AA9401; //0x0460 
	float N19AA9400; //0x0464 
	float N19AA93FF; //0x0468 
	float N19AA93FE; //0x046C 
	float N19AA93FD; //0x0470 
	float N19AA93FC; //0x0474 
	float N19AA93FB; //0x0478 
	float N19AA93FA; //0x047C 
	float N19AA93F9; //0x0480 
	DWORD N19AA93F8; //0x0484 
	DWORD N19AA93F7; //0x0488 
	DWORD N19AA93F6; //0x048C 
	DWORD N19AA93F5; //0x0490 
	DWORD N19AA93F4; //0x0494 
	DWORD N19AA93F3; //0x0498 
	DWORD N19AA93F2; //0x049C 
	DWORD N19AA93F1; //0x04A0 
	DWORD N19AA93F0; //0x04A4 
	DWORD N19AA93EF; //0x04A8 
	DWORD N19AA93EE; //0x04AC 
	float N19AA93ED; //0x04B0 
char _0x04B4[876];
	float N19AAA2BD; //0x0820 
	float N19AAA2BC; //0x0824 
char _0x0828[40];
	float N19AAA2B1; //0x0850 
	float N19AAA2B0; //0x0854 
	float N19AAA2AF; //0x0858 
	float N19AAA2AE; //0x085C 
	float N19AAA2AD; //0x0860 
	float N19AAA2AC; //0x0864 
	float N19AAA2AB; //0x0868 
	float N19AAA2AA; //0x086C 
	float N19AAA2A9; //0x0870 
	float N19AAA2A8; //0x0874 
	float N19AAA2A7; //0x0878 
	float N19AAA2A6; //0x087C 
	float N19AAA2A5; //0x0880 
	float N19AAA2A4; //0x0884 
	float N19AAA2A3; //0x0888 
	float N19AAA2A2; //0x088C 
	float N19AAA2A1; //0x0890 
	float N19AAA2A0; //0x0894 
char _0x0898[4];
	float N19AAA29E; //0x089C 
	float N19AAA29D; //0x08A0 
	float N19AAA29C; //0x08A4 
	float N19AAA29B; //0x08A8 
	float N19AAA29A; //0x08AC 
	float N19AAA299; //0x08B0 
	float N19AAA298; //0x08B4 
	float N19AAA297; //0x08B8 
	float N19AAA296; //0x08BC 
	float N19AAA295; //0x08C0 
	float N19AAA294; //0x08C4 
	float N19AAA293; //0x08C8 
	float N19AAA292; //0x08CC 
	float N19AAA291; //0x08D0 
	float N19AAA290; //0x08D4 
char _0x08D8[4];
	DWORD WepRelated1; //0x08DC 
char _0x08E0[8];
	DWORD N19AAA28B; //0x08E8 
char _0x08EC[40];
	float N19AAA280; //0x0914 
	float N19AAA27F; //0x0918 
char _0x091C[4];
	float N19AAA27D; //0x0920 
	float N19AAA27C; //0x0924 
char _0x0928[4];
	float N19AAA27A; //0x092C 
char _0x0930[4];
	float N19AAA278; //0x0934 
char _0x0938[12];
	float N19AAA274; //0x0944 
	float N19AAA273; //0x0948 
	float N19AAA272; //0x094C 
char _0x0950[4];
	float N19AAA270; //0x0954 
char _0x0958[8];
	__int32 N19AAA26D; //0x0960 
char _0x0964[24];
	float N19AAA266; //0x097C 
char _0x0980[16];
	float N19AAA261; //0x0990 
	float N19AAA260; //0x0994 
	float N19AAA25F; //0x0998 
char _0x099C[108];
	float N19AAA243; //0x0A08 
	float N19AAA242; //0x0A0C 
	float N19AAA241; //0x0A10 
	float N19AAA240; //0x0A14 
	float N19AAA23F; //0x0A18 
	float N19AAA23E; //0x0A1C 
	float N19AAA23D; //0x0A20 
	float N19AAA23C; //0x0A24 
	float N19AAA23B; //0x0A28 
	float N19AAA23A; //0x0A2C 
	float N19AAA239; //0x0A30 
	float N19AAA238; //0x0A34 
	float N19AAA237; //0x0A38 
	float N19AAA236; //0x0A3C 
	float N19AAA235; //0x0A40 
	float N19AAA234; //0x0A44 
	float N19AAA233; //0x0A48 
	float N19AAA232; //0x0A4C 
	float N19AAA231; //0x0A50 
	float N19AAA230; //0x0A54 
	float N19AAA22F; //0x0A58 
	float N19AAA22E; //0x0A5C 
	float N19AAA22D; //0x0A60 
	float N19AAA22C; //0x0A64 
char _0x0A68[24];
	float PlayerMovement_1; //0x0A80 
char _0x0A84[144];
	float N19AAA200; //0x0B14 
	float N19AAA1FF; //0x0B18 
char _0x0B1C[1440];
	DWORD N19AAC0F8; //0x10BC 
char _0x10C0[1660];
	float N19AAD26F; //0x173C 
	float N19AAD26E; //0x1740 
	float N19AAD26D; //0x1744 
	float N19AAD26C; //0x1748 
	float N19AAD26B; //0x174C 
	float N19AAD26A; //0x1750 
	float N19AAD269; //0x1754 
	float N19AAD268; //0x1758 
	float N19AAD267; //0x175C 
char _0x1760[32];
	float N19AAD25E; //0x1780 
	float N19AAD25D; //0x1784 
	float N19AAD25C; //0x1788 
	float N19AAD25B; //0x178C 
	float N19AAD25A; //0x1790 
	float N19AAD259; //0x1794 
	float N19AAD258; //0x1798 
	float N19AAD257; //0x179C 
	float N19AAD256; //0x17A0 
	float N19AAD255; //0x17A4 
	float N19AAD254; //0x17A8 
char _0x17AC[48];
	float N19AAD247; //0x17DC 
char _0x17E0[4];
	float N19AAD245; //0x17E4 
char _0x17E8[52];
	float N19AAE5FA; //0x181C 
char _0x1820[4];
	float N19AAE5F8; //0x1824 
char _0x1828[16];
	float N19AAE5F3; //0x1838 
char _0x183C[32];
	__int32 N19AAE5EA; //0x185C 
char _0x1860[48];
	float N19AAE5DD; //0x1890 
	float N19AAE5DC; //0x1894 
	float N19AAE5DB; //0x1898 
	float N19AAE5DA; //0x189C 
	float N19AAE5D9; //0x18A0 
	float N19AAE5D8; //0x18A4 
	float N19AAE5D7; //0x18A8 
	float N19AAE5D6; //0x18AC 
	float N19AAE5D5; //0x18B0 
	float N19AAE5D4; //0x18B4 
	float N19AAE5D3; //0x18B8 
	float N19AAE5D2; //0x18BC 
	float N19AAE5D1; //0x18C0 
	float N19AAE5D0; //0x18C4 
	float N19AAE5CF; //0x18C8 
	float N19AAE5CE; //0x18CC 
	float N19AAE5CD; //0x18D0 
	float N19AAE5CC; //0x18D4 
	float N19AAE5CB; //0x18D8 
	float N19AAE5CA; //0x18DC 
	float N19AAE5C9; //0x18E0 
	float N19AAE5C8; //0x18E4 
	float N19AAE5C7; //0x18E8 
	float N19AAE5C6; //0x18EC 
	float N19AAE5C5; //0x18F0 
	float N19AAE5C4; //0x18F4 
	float N19AAE5C3; //0x18F8 
	float N19AAE5C2; //0x18FC 
	float WalkLeft; //0x1900 
	float WalkRight; //0x1904 
	float WalkForward; //0x1908 
	float WalkBackward; //0x190C 
	float N19AAE5BD; //0x1910 
	float N19AAE5BC; //0x1914 
	float N19AAE5BB; //0x1918 
	float N19AAE5BA; //0x191C 
	float N19AAE5B9; //0x1920 
	float N19AAE5B8; //0x1924 
	float N19AAE5B7; //0x1928 
	float N19AAE5B6; //0x192C 
	float N19AAE5B5; //0x1930 
	float N19AAE5B4; //0x1934 
	__int32 N19AAE5B3; //0x1938 
	float N19AAE5B2; //0x193C 
	float N19AAE5B1; //0x1940 
	float N19AAE5B0; //0x1944 
	char N19AAE5AF[10]; //0x1948 
char _0x1952[26];
	float N19AAE5A6; //0x196C 
char _0x1970[16];
	float N19AAE5A1; //0x1980 
char _0x1984[16];
	float N19AAE59C; //0x1994 
char _0x1998[16];
	float N19AAE597; //0x19A8 
char _0x19AC[64];
	WeaponRelate_unk6* pWeaponRelatedUnk; //0x19EC 
	WeaponWheel* pWeaponWheel; //0x19F0 
char _0x19F4[8];
	__int32 N19AAE582; //0x19FC 
char _0x1A00[24];
	__int32 WeaponSwitch; //0x1A18 
	float TimeTillSwitch; //0x1A1C 
char _0x1A20[40];
	DWORD unkWeaponSlot; //0x1A48 
char _0x1A4C[4];
	float N19AAE56D; //0x1A50 
	float N19AAE56C; //0x1A54 
char _0x1A58[104];
	float N19AAE551; //0x1AC0 
char _0x1AC4[56];
	DWORD N19AAE542; //0x1AFC 
	DWORD N19AAE541; //0x1B00 
char _0x1B04[92];
	PtrFillUnk* N19AAE529; //0x1B60 
char _0x1B64[4];
	float N19AAE527; //0x1B68 
char _0x1B6C[4];
	DWORD N19AAE525; //0x1B70 
char _0x1B74[32];
	DWORD N19AAE51C; //0x1B94 
char _0x1B98[4];
	TextPtrFill* DeadActor; //0x1B9C 
	TextPtrFill* OnScreen; //0x1BA0 
	float N19AAE518; //0x1BA4 
char _0x1BA8[8];
	PtrFillUnk* N19AAE515; //0x1BB0 
char _0x1BB4[4];
	float N19AAE513; //0x1BB8 
char _0x1BBC[4];
	__int32 N19AAE511; //0x1BC0 
char _0x1BC4[12];
	PtrFillUnk* N19AAE50D; //0x1BD0 
	PtrFillUnk* N19AAE50C; //0x1BD4 
	PtrFillUnk* N19AAE50B; //0x1BD8 
	PtrFillUnk* N19AAE50A; //0x1BDC 
	PtrFillUnk* N19AAE509; //0x1BE0 
char _0x1BE4[1036];
	PtrFillUnk* N19AB0891; //0x1FF0 
char _0x1FF4[4];
	float N19AB088F; //0x1FF8 
char _0x1FFC[16];
	PtrFillUnk* N19AB19CC; //0x200C 
char _0x2010[4];
	float N19AB19CA; //0x2014 
char _0x2018[24];
	TextPtrFill* N19AB19C3; //0x2030 
	TextPtrFill* N19AEE443; //0x2034 
	TextPtrFill* N19AEE444; //0x2038 
	TextPtrFill* N19AEE445; //0x203C 
	TextPtrFill* N19AEE446; //0x2040 
	TextPtrFill* N19AEE447; //0x2044 
	TextPtrFill* N19AEE448; //0x2048 
	TextPtrFill* N19AEE449; //0x204C 
	TextPtrFill* N19AEE44A; //0x2050 
	TextPtrFill* N19AEE44B; //0x2054 
	TextPtrFill* N19AEE44C; //0x2058 
	TextPtrFill* N19AEE44D; //0x205C 
	TextPtrFill* N19AEE44E; //0x2060 
	TextPtrFill* N19AEE44F; //0x2064 
char _0x2068[28];
	float N19AB19AE; //0x2084 
char _0x2088[36];
	float N19AB19A4; //0x20AC 
char _0x20B0[20];
	float N19AB199E; //0x20C4 
char _0x20C8[12];
	float N19AB199A; //0x20D4 
char _0x20D8[16];
	PtrFillUnk* UnkPTR; //0x20E8 
char _0x20EC[580];
	float N19AB1903; //0x2330 
char _0x2334[4];
	DWORD N19AB1901; //0x2338 
char _0x233C[16];
	DWORD N19AB18FC; //0x234C 
char _0x2350[4];
	float N19AB18FA; //0x2354 
	PtrFillUnk* N19AB18F9; //0x2358 
	DWORD N19AB18F8; //0x235C 
	float N19AB18F7; //0x2360 
	__int32 N19AB18F6; //0x2364 
char _0x2368[56];
	TextPtrFill* ModelPath; //0x23A0 
	TextPtrFill* TexturePath; //0x23A4 
	DWORD WepRelated2; //0x23A8 
char _0x23AC[12];
	float N19AB18E1; //0x23B8 
char _0x23BC[4];
	DWORD N19AB18DF; //0x23C0 
char _0x23C4[48];

};//Size=0x23F4

class Health
{
public:
	float Current; //0x0000 
	float Max; //0x0004 
char _0x0008[56];

};//Size=0x0040

class LevelPath
{
public:
	char N19967483[83]; //0x0000 

};//Size=0x0053

class UnkWepRelated_1
{
public:
char _0x0000[348];
	float N19A7F457; //0x015C 
	float N19A7F456; //0x0160 
	float N19A7FB99; //0x0164 
char _0x0168[20];
	float N19A7FB93; //0x017C 
char _0x0180[324];

};//Size=0x02C4

class UnkWeapRelated_2
{
public:
char _0x0000[708];

};//Size=0x02C4

class TextPtrFill
{
public:
	char N19ABA0C4[255]; //0x0000 

};//Size=0x00FF

class N19AE12B7
{
public:
char _0x0000[4];

};//Size=0x0004

class N19AEAA95
{
public:
char _0x0000[4];

};//Size=0x0004

class PtrFillUnk
{
public:
char _0x0000[252];

};//Size=0x00FC

class WeaponWheel
{
public:
	__int32 bAxe_1; //0x0000 
	__int32 N19B76D0D; //0x0004 
	__int32 N19B7700C; //0x0008 
	DWORD N19B771F1; //0x000C 
	__int32 AxeWeaponID; //0x0010 
	DWORD N19B77697; //0x0014 
	DWORD N19B777D0; //0x0018 
	WeapRelate_unk4* N19B77A13; //0x001C 
	__int32 bAxe; //0x0020 
	DWORD N19B77CD4; //0x0024 
	__int32 NormalBowWeaponID; //0x0028 
	__int32 NormalArrowAmmo1; //0x002C 
	__int32 ExplosiveArrowAmmo1; //0x0030 
	__int32 PosionArrowAmmo1; //0x0034 
	__int32 bBow; //0x0038 
	DWORD N19B78DF1; //0x003C 
	DWORD N19B78F1B; //0x0040 
char _0x0044[4];
	__int32 bBow2; //0x0048 
	DWORD N19B79335; //0x004C 
	__int32 SinglePlayerBowWeaponID; //0x0050 
	__int32 TekBowAmmo_Normal; //0x0054 
	__int32 TelBowAmmo_Explosive; //0x0058 
	__int32 TekBowAmmo_Poison; //0x005C 
	__int32 bTekBow1; //0x0060 
	DWORD N19B7AB67; //0x0064 
	DWORD N19B7AC81; //0x0068 
char _0x006C[4];
	__int32 bTekBow2; //0x0070 
	DWORD N19B7B108; //0x0074 
	__int32 GrenadeWeaponID; //0x0078 
	__int32 GrenadeAmmo1; //0x007C 
	__int32 GrenadeAmmo2; //0x0080 
	__int32 GrenadeAmmo3; //0x0084 
	__int32 bGrenade1; //0x0088 
	__int32 N19B7B880; //0x008C 
	__int32 N19B4C63F; //0x0090 
char _0x0094[4];
	__int32 bGrenade2; //0x0098 
	__int32 N19B4C642; //0x009C 
	__int32 PistolWeaponID; //0x00A0 
	__int32 PistolAmmo1; //0x00A4 
	__int32 PistolAmmo2; //0x00A8 
	__int32 PistolAmmo3; //0x00AC 
	__int32 bPistol1; //0x00B0 
	__int32 N19B4C648; //0x00B4 
	__int32 N19B4C649; //0x00B8 
char _0x00BC[4];
	__int32 bPistol; //0x00C0 
	__int32 N19B4C64C; //0x00C4 
	__int32 ShotGunWeaponID; //0x00C8 
	__int32 ShotGunAmmo1; //0x00CC 
	__int32 ShotGunAmmo2; //0x00D0 
	__int32 ShotGunAmmo3; //0x00D4 
	__int32 bShotgun; //0x00D8 
	__int32 N19B5F31C; //0x00DC 
	__int32 N19B5F475; //0x00E0 
char _0x00E4[4];
	__int32 bShotgun_2; //0x00E8 
	__int32 N19BE6B15; //0x00EC 
	__int32 FlechetteWeaponID; //0x00F0 
	__int32 FlechetteAmmo1; //0x00F4 
	__int32 FlechetteAmmo2; //0x00F8 
	__int32 FlechetteAmmo3; //0x00FC 
	__int32 bFlechette1; //0x0100 
	__int32 N19BE7388; //0x0104 
	__int32 N19BE74C1; //0x0108 
char _0x010C[4];
	__int32 bFlechette2; //0x0110 
	__int32 N19BE785E; //0x0114 
	__int32 RocketWeaponID; //0x0118 
	__int32 RocketAmmo1; //0x011C 
	__int32 RocketAmmo2; //0x0120 
	__int32 RocketAmmo3; //0x0124 
	__int32 bRocket1; //0x0128 
	__int32 N19BE7FD6; //0x012C 
	__int32 N19BE8100; //0x0130 
char _0x0134[4];
	__int32 bRocket2; //0x0138 
	__int32 N19BE850A; //0x013C 
	__int32 PlasmaWeaponID; //0x0140 
	__int32 PlasmaAmmo; //0x0144 
	__int32 PlasmaAmmo2; //0x0148 
	__int32 PlasmaAmmo3; //0x014C 
	__int32 bPlasmaCannon1; //0x0150 
	__int32 N19BE8C35; //0x0154 
	__int32 N19BE8D7E; //0x0158 
char _0x015C[4];
	__int32 bPlasmaCannon; //0x0160 
	__int32 UnkVal; //0x0164 
	__int32 FlameThrowerWeaponID; //0x0168 
	__int32 FlameThrowerAmmo; //0x016C 
	__int32 N19FD720B; //0x0170 
	__int32 N19FD73E1; //0x0174 
	__int32 bFlameThrower1; //0x0178 
	__int32 bFlameThrower2; //0x017C 
	__int32 N19FD775F; //0x0180 
char _0x0184[4];
	__int32 bFlameThrow3; //0x0188 
	__int32 N19FD7B0B; //0x018C 
	__int32 SpiderMineWeaponID; //0x0190 
	__int32 SpiderMineAmmo; //0x0194 
	__int32 SpiderMineAmmo2; //0x0198 
	__int32 SpiderMineAmmo3; //0x019C 
	__int32 bSpider; //0x01A0 
	__int32 N19FD82B2; //0x01A4 
	__int32 N19FD83CD; //0x01A8 
char _0x01AC[4];
	__int32 bSpider2; //0x01B0 
	__int32 N19FD870C; //0x01B4 
	__int32 GravityGunWeaponID; //0x01B8 
	__int32 GravityGunAmmo; //0x01BC 
	__int32 GravityGunAmmo2; //0x01C0 
	__int32 GravityGunAmmo3; //0x01C4 
	__int32 N1A06DD89; //0x01C8 
	__int32 N1A06DED2; //0x01CC 
	__int32 bGravityGun; //0x01D0 
char _0x01D4[4];
	__int32 bGravityGun2; //0x01D8 
	__int32 N1A06E445; //0x01DC 
	__int32 DarkMatterCubeWeaponID; //0x01E0 
	__int32 DarkMatterCubeAmmo1; //0x01E4 
	__int32 DarkMatterCubeAmmo2; //0x01E8 
	__int32 DarkMattterCubeAmmo3; //0x01EC 
	__int32 bDarkMatterCube1; //0x01F0 
	__int32 N1A0CCF28; //0x01F4 
	__int32 N1A0CE205; //0x01F8 
char _0x01FC[4];
	__int32 bDarkMatterCube2; //0x0200 
	__int32 N1A0CEA55; //0x0204 
	__int32 ArrowWeaponID; //0x0208 
	__int32 ArrowNormalAmmo; //0x020C 
	__int32 ArrowExplosiveAmmo; //0x0210 
	__int32 ArrowPoisonAmmo; //0x0214 
	__int32 bArrow1; //0x0218 
	__int32 N1A0CF41F; //0x021C 
	__int32 N1A0CF53A; //0x0220 
char _0x0224[4];
	__int32 bArrow; //0x0228 

};//Size=0x022C

class WeapRelate_unk4
{
public:
char _0x0000[64];

};//Size=0x0040

class WeaponRelate_unk5
{
public:
char _0x0000[64];

};//Size=0x0040

class WeaponRelate_unk6
{
public:
	PtrFillUnk* N19EC2397; //0x0000 
	PtrFillUnk* N19EC2398; //0x0004 
	PtrFillUnk* N19EC2399; //0x0008 
	PtrFillUnk* N19EC239A; //0x000C 
	PtrFillUnk* N19EC239B; //0x0010 
	PtrFillUnk* N19EC239C; //0x0014 
	PtrFillUnk* N19EC239D; //0x0018 
	PtrFillUnk* N19EC239E; //0x001C 
	PtrFillUnk* N19EC239F; //0x0020 
	PtrFillUnk* N19EC23A0; //0x0024 
char _0x0028[24];

};//Size=0x0040

class N1AC074CE
{
public:
char _0x0000[4];

};//Size=0x0004

class PlayerMovement
{
public:
char _0x0000[64];

};//Size=0x0040


