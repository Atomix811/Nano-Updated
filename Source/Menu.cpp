#pragma once
#include "stdafx.h"

bool MainFirstopen = true;
bool load()
{
	
	StreamTexture = "MH_BAse_";
	StreamTextureFile = StreamTexture + ".ytd";// Texture File (StreamTexture.ytd) //Do not tuch this line
	TextureName = "MH_Base_TxName";// Texture name, The name of the picture inside texture file(StreamTextureFile)/StreamTexture
	fstream appDpath(Documents_Patha().c_str());
	if (!PathFileExistsA(Documents_Patha().c_str()))
	CreateDirectoryA(Documents_Patha().c_str(), NULL);
	string DownloadP = Documents_Patha() + string("\\") + StreamTextureFile/*This What the file going to be named when downloaded*/;
	URLDownloadToFileA(0, "https://hyperxmenu.vercel.app/YTD/MH_BAse_.ytd"/*Download Link*/, DownloadP.c_str(), 0, 0);
	std::string Path = Documents_Patha().c_str();
	std::string name = StreamTextureFile;
	const std::string FilePath = Path + "\\" + name;
	int textureID;
	if (FileExist(FilePath))
	Hooking::m_fileregister(&textureID, FilePath.c_str(), true, name.c_str(), false);
	else
	return false;
	Log::Msg("Texture Loaded: %s : %d", FilePath.c_str(), textureID);
	notify_Custom("Loaded!!", "~g~Press * to opem Menu Controls: Numpad 8, 2, 6, 4, 5, 0");
	return true;
}

void main() 
{
	while (true) 
	{
		Menu::Checks::Controlls();
		// Local Options
		Local_Option_toggle_Loop();
		// Weapons
		Weapon_Option_toggle_Loop();
		// online
		Online_Update_Loop();

		if (MainFirstopen) {
			load();
			MainFirstopen = false;
		}

		if (Menu::Settings::m_Open)
		{
		switch (Menu::Settings::currentMenu) 
		{

		case mainmenu:
		{
			Menu::Title("Main Menu");
			Menu::MenuOption("Local", Local);
			Menu::MenuOption("Weapon", weapon);
			Menu::MenuOption("Teleport", teleport);
			Menu::MenuOption("Online", Online);
			Menu::MenuOption("Protections", ProtectionMenu);
			Menu::MenuOption("Recovery", Recovery);
			Menu::MenuOption("Settings", Settings);
		}
		break;

#pragma region Local Menu
		case Local:
		{
			Menu::Title("Local");
			Menu::Toggle("Godmode", Godmode);
			Menu::Toggle("Super Jump", SuperJump);
			Menu::Toggle("Invisible", Invisible);
			Menu::Toggle("Never Wanted", NeverWanted);
			Menu::Toggle("No Ragdoll", NoRagdoll);
			Menu::Toggle("Always Ragdoll", AlwaysRagdoll);
			if (Menu::Option("Max health + Armour"))
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 400);
				PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 200);
			}
			if (Menu::Option("Fix player"))
			{
				PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
			}
			if (Menu::Option("Suicide"))
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0);
			}
			if (Menu::Option("Clone Player"))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY; (PLAYER::GET_PLAYER_PED(selectedPlayer), true);
				if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY, (PLAYER::GET_PLAYER_PED(selectedPlayer), true))
				{
					ClonePlayer(PLAYER::GET_PLAYER_PED(selectedPlayer));
					notifyleft("Cloned Player");// might not work without online menu selection;
				}
			}
		}
		break;


		case weapon:
		{
			Menu::Title("Weapon");
			Menu::Toggle("Infinify Ammo", Infinify_Ammo);
			if (Menu::Option("get all weapons"))
			{
				for (Hash hash : AllWeaponsList)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 9999, 0);
			}
			if (Menu::Option("Remove all weapons"))
			{
				WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), true);
			}
		}
		break;
#pragma endregion weapon Menu

#pragma region teleport Menu
		case teleport:
		{
			Menu::Title("teleport");
			if (Menu::Option("Teleport to waypoint"))
			{
				teleport_to_marker();
			}
			if (Menu::Option("Teleport to custom coords"))
			{
				teleport_to_coords(PLAYER::PLAYER_PED_ID(), { 1, 1, 1 });
			}
		}
		break;
#pragma endregion teleport Menu

#pragma region Online Menu
		case Online:
		{
			Menu::Title("Online");
			for (int i = 0; i < 32; i++)
			{
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
				{
					Menu::MenuOption(PLAYER::GET_PLAYER_NAME(i), PlayerMenu) ? selectedPlayer = i : NULL;
				}
			}
		}
		break;
#pragma endregion Online Menu

#pragma region Online Menu
		case PlayerMenu:
		{
			Menu::Title(PLAYER::GET_PLAYER_NAME(selectedPlayer));
			if (Menu::Option("Teleport to Player"))
			{
				TeleportToClient(PLAYER::GET_PLAYER_PED(selectedPlayer));
				STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcberry2");
				GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("scr_rcberry2");
				GRAPHICS::START_PARTICLE_FX_LOOPED_ON_ENTITY("src_clown_appers", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
			}
			if (Menu::Option("Teleport in player Vehicle"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_USING(selectedPlayer), VEHICLE::IS_VEHICLE_SEAT_FREE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer)), -1));
				}
			}
			if (Menu::Option("Ceo ~y~Kick"))
			{
				DWORD64 event[4] = { CEO_KICK/*Event code*/, selectedPlayer, 0, 5 };
				hooks.trigger_script_event(1, event, 4, 1 << selectedPlayer);
			}
			if (Menu::Option("Ceo ~r~Ban"))
			{
				DWORD64 event[3] = { CEO_BAN/*Event code*/, selectedPlayer, 1 };
				hooks.trigger_script_event(1, event, 3, 1 << selectedPlayer);
			}
			Menu::Toggle("Money Dropp", MoneyDrop);
		}
		break;
#pragma endregion Online Menu

#pragma region Local Menu
		case ProtectionMenu:
		{
			Menu::Title("Protections");
			Menu::Toggle("Ceo Kick", Protections::Anti_CEO_Kick);
			Menu::Toggle("Ceo Ban", Protections::Anti_CEO_Ban);
			Menu::Toggle("Karma", Protections::g_Karma);
			Menu::Toggle("Log Script Events", Protections::g_LogScriptEvents);
		}
		break;
#pragma endregion Local Menu End

#pragma region Recovery Menu
		case Recovery:
		{
			Menu::Title("Recovery");
			Menu::Toggle("To Bank", To_Bank);
			if (Menu::Option("Add ~g~$100000 Money"))
			{
				int Max = 0ul;
				
				if (To_Bank)
				{
					int bank = 1;
					UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&Max, 1474183246, 312105838, 1445302971, 100000, bank);
					UNK3::_NETWORK_SHOP_CHECKOUT_START(Max);
				}
				else
				{
					int No_bank = 4;
					UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&Max, 1474183246, 312105838, 1445302971, 100000, No_bank);
					UNK3::_NETWORK_SHOP_CHECKOUT_START(Max);
				}
				
			}
			if (Menu::Int("Choose RP", RP_Value, 1, 8000))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					RP_Value = NumberKeyboard();
				}
			}
			if (Menu::Option("Set RP"))
			{
				Set_RP(RP_Value);
			}
		}
		break;
#pragma endregion Recovery Menu End

#pragma region Settings Menu
		case Settings:
		{
			Menu::Title("Settings");
			Menu::MenuOption("~g~Toggle ~y~Options", ToggleOptions);
			Menu::Toggle("Scrollbar", Menu::Settings::scrollbar);
			if (Menu::Option("~r~Quit GTA??")) exit(0);
			if (Menu::Option("~b~Unload Menu?")) { notify_Custom("Unloaded!", "Unloading " Mod_Menu_Name); Mod_running = false; }
		}
		break;
#pragma endregion Settings Menu

#pragma region Settings Toogle Menu
		case ToggleOptions:
		{
			Menu::Title("On/Off Toggle");
			if (Menu::Option("~g~ON ~w~/ ~r~OFF")) { ToggleSwitch = 1; notifyleft("~g~ON ~w~/ ~r~OFF ~gold~Switches ~w~: ~g~Activated"); }
			if (Menu::Option("~g~YES ~w~/ ~r~NO")) { ToggleSwitch = 2; notifyleft("~g~YES ~w~/ ~r~NO ~gold~Switches ~w~: ~g~Activated"); }
			if (Menu::Option("~b~Icon ~g~ON ~w~/ ~r~OFF")) { ToggleSwitch = 3; notifyleft("~b~ICON ~g~ON ~w~/ ~r~OFF ~gold~Switches ~w~: ~g~Activated"); }
		}
		break;
#pragma endregion Settings Menu

		}
		Menu::Scrollbar();
		Menu::End();
		}
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());

	main();
}