#include "stdafx.h"

// weaponss 

bool Infinify_Ammo = false;
void infinify_Ammo(bool toggle)
{
	if (Infinify_Ammo)
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), true);
	}
	else
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), false);
	}
}



//Everything in here will be contiuously looped, when it is true here is an example
//You want to do the bool by the void, easy enough right: test_bool ? test(true) : NULL; or testVoid(testBool);
//If this is true we continuously loop the void, if its false then just do nothing
// this Option can reduce crashes
void Weapon_Option_toggle_Loop()
{
	infinify_Ammo(Infinify_Ammo);
}


// Weapon List
std::vector<Hash> AllWeaponsList{
	//Melee
	0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D,
	0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08,

	//Handguns
	0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0xD205520E, 0x83839C4,
	0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0x97EA20B8, 0xAF3696A1, 0xAF3696A1, 0x917F6C8C,
	//Submachine Guns
	0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155,
	//Shotguns
	0x1D073A89, 0x1D073A89, 0x1D073A89, 0x1D073A89, 0x1D073A89, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D,
	//Assault Rifles
	0xBFEFFF6D, 0x83BF0278, 0x83BF0278, 0xC0A3098D, 0x7F229F94, 0x624FE830,
	//Light Machine Guns
	0x9D07F764, 0x7FD62962, 0x61012683,
	//Sniper Rifles
	0x05FC3C11, 0x0C472FE2, 0xC734385A,
	//Heavy Weapons
	0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67,
	//Throwables
	0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0x2C3731D9, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3,
	//Miscellaneous
	0x34A67B97, 0xFBAB5776, 0x060EC506, 0xBA536372
};