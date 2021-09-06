/*

	  _____      _                _                          _____                               
	 |  __ \    | |              | |                        / ____|                              
	 | |__) |_ _| | ___ _ __ ___ | |__   __ _ _ __   __ _  | |  __  __ _ _ __ ___   ___ _ __ ___ 
	 |  ___/ _` | |/ _ \ '_ ` _ \| '_ \ / _` | '_ \ / _` | | | |_ |/ _` | '_ ` _ \ / _ \ '__/ __|
	 | |  | (_| | |  __/ | | | | | |_) | (_| | | | | (_| | | |__| | (_| | | | | | |  __/ |  \__ \
	 |_|   \__,_|_|\___|_| |_| |_|_.__/ \__,_|_| |_|\__, |  \_____|\__,_|_| |_| |_|\___|_|  |___/
	                                                 __/ |                                       
	                                                |___/                                        
	    									
								Global Scripter : 	- Abiel Al-Farel Syah
												  	- Junai (Server head community)
								
								De Facto Scripter: 	- Junai (Server head community)
								
								Server Management:	- Skyler19 (Server head community)			
								
								===== > V1 Changelog < =====
								
								> Added Login & Register
								> Added UCP System
								
								============================
    
*/

/* Includes */
#include <a_samp>
#include <a_mysql>

#include <YSI_Coding\y_va>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

#include <YSI_Server\y_colors>								

#include <streamer>

#include <foreach>
#include <samp_bcrypt>
#include <izcmd>
#include <sscanf2>

#include "Modules/Server/define"

new MySQL:g_SQL;
new g_RaceCheck[MAX_PLAYERS char];
new PlayerChar[MAX_PLAYERS][MAX_CHARS][MAX_PLAYER_NAME + 1];
new tempUCP[64];

/* Enums */

enum
{
	DIALOG_REGISTER,
	DIALOG_LOGIN,
	DIALOG_MAKECHAR,
	DIALOG_ORIGIN,
	DIALOG_AGE,
	DIALOG_GENDER,
	DIALOG_CHARLIST,
	DIALOG_STATS,
	DIALOG_ITEMS,
	// BUSSINES
	BUSSINES_BUYMENU,
	BUSSINES_EDITMENU
};

enum e_player_data
{
	pID,
	pUCP[22],
	pName[MAX_PLAYER_NAME],
	Float:pPos[3],
	pWorld,
	pInterior,
	pSkin,
	pAge,
	pOrigin[32],
	pGender,
	bool:pSpawned,
	pChar,
	Float:pHealth,
	pHunger,
	pThirst,
	pAdmin,
	pAdminDuty,
	pFreeze,
	pFreezeTimer,
	pMoney,
	pBankMoney,
	// Item
	pBandage,
	pCiggar,
	pSnack,
	pSprunk,
	pPhone,
	pPhoneCredit,
	pMP3,
	// In
	pInHouse,
	pInBussines,
	// Minutes
	pHours,
	pMinutes,
	pSeconds,
	//Level
	pLevel,
	pLevelUp
};

new PlayerData[MAX_PLAYERS][e_player_data];
new PlayerText:Hunger[MAX_PLAYERS];
new PlayerText:Thirst[MAX_PLAYERS];
new PlayerText:Blackline[MAX_PLAYERS];
new PlayerText:ThirstAlert[MAX_PLAYERS];
new PlayerText:HungerAlert[MAX_PLAYERS];
new PlayerText:SkinModel[MAX_PLAYERS];
new PlayerText:BlacklineModel[MAX_PLAYERS];

#include "Modules/Server/native"
#include "Modules/Server/function"
#include "Modules/Server/task"
#include "Modules/Server/color"
#include "Modules/Vehicle/Vehicle"
#include "Modules/House/House"
#include "Modules/Bussines/Bussines"

#include "Modules/Admin/command_admin"
#include "Modules/Player/player_command"
main()
{
	print("UCP Roleplay Gamemode loaded!");
}

public OnGameModeInit()
{
	Database_Connect();
	mysql_tquery(g_SQL, "SELECT * FROM `house`", "House_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `bussines`", "Bussines_Load");
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerConnect(playerid)
{
	g_RaceCheck{playerid} ++;
	SetPlayerPos(playerid, 155.3337, -1776.4384, 14.8978+5.0);
	SetPlayerCameraPos(playerid, 155.3337, -1776.4384, 14.8978);
	SetPlayerCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128);
	InterpolateCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128, 156.2713, -1776.0797, 14.7078, 5000, CAMERA_MOVE);
	SetTimerEx("PlayerCheck", 1000, false, "ii", playerid, g_RaceCheck{playerid});
	ShowServerTextdraw(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	SaveData(playerid);
	return 1;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOG_REGISTER)
	{
	    if(!response)
	        return Kick(playerid);

		new str[256];
	    format(str, sizeof(str), "Welcome to Palembang Gamers roleplay\n\nYour UCP: %s\nERROR: Password length cannot below 7 or above 32!\nPlease insert your Password below to register:", GetName(playerid));

        if(strlen(inputtext) < 7)
			return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "UCP - Register", str, "Register", "Exit");

        if(strlen(inputtext) > 32)
			return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "UCP - Register", str, "Register", "Exit");

        bcrypt_hash(playerid, "HashPlayerPassword", inputtext, BCRYPT_COST);
	}
	if(dialogid == DIALOG_LOGIN)
	{
	    if(!response)
	        return Kick(playerid);
	        
        if(strlen(inputtext) < 1)
        {
			new str[256];
            format(str, sizeof(str), "Welcome Back to Palembang Gamers roleplay\n\nYour UCP: %s\nPlease insert your Password below to logged in:", GetName(playerid));
            ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "UCP - Login", str, "Login", "Exit");
            return 1;
		}
		new pwQuery[256], hash[BCRYPT_HASH_LENGTH];
		mysql_format(g_SQL, pwQuery, sizeof(pwQuery), "SELECT Password FROM PlayerUCP WHERE UCP = '%e' LIMIT 1", GetName(playerid));
		mysql_query(g_SQL, pwQuery);
		
        cache_get_value_name(0, "Password", hash, sizeof(hash));
        
        bcrypt_verify(playerid, "OnPlayerPasswordChecked", inputtext, hash);

	}
    if(dialogid == DIALOG_CHARLIST)
    {
		if(response)
		{
			if (PlayerChar[playerid][listitem][0] == EOS)
				return ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Create Character", "Insert your new Character Name\n\nExample: Finn_Xanderz, Javier_Cooper etc.", "Create", "Exit");

			PlayerData[playerid][pChar] = listitem;
			SetPlayerName(playerid, PlayerChar[playerid][listitem]);

			new cQuery[256];
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT * FROM `characters` WHERE `Name` = '%s' LIMIT 1;", PlayerChar[playerid][PlayerData[playerid][pChar]]);
			mysql_tquery(g_SQL, cQuery, "LoadCharacterData", "d", playerid);
			
		}
	}
	if(dialogid == DIALOG_MAKECHAR)
	{
	    if(response)
	    {
		    if(strlen(inputtext) < 1 || strlen(inputtext) > 24)
				return ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Create Character", "Insert your new Character Name\n\nExample: Finn_Xanderz, Javier_Cooper etc.", "Create", "Back");

			if(!IsRoleplayName(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Create Character", "Insert your new Character Name\n\nExample: Finn_Xanderz, Javier_Cooper etc.", "Create", "Back");

			new characterQuery[178];
			mysql_format(g_SQL, characterQuery, sizeof(characterQuery), "SELECT * FROM `characters` WHERE `Name` = '%s'", inputtext);
			mysql_tquery(g_SQL, characterQuery, "InsertPlayerName", "ds", playerid, inputtext);

		    format(PlayerData[playerid][pUCP], 22, GetName(playerid));
		}
	}
	if(dialogid == DIALOG_AGE)
	{
		if(response)
		{
			if(strval(inputtext) >= 70)
			    return ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "ERROR: Cannot more than 70 years old!", "Continue", "Cancel");

			if(strval(inputtext) < 13)
			    return ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "ERROR: Cannot below 13 Years Old!", "Continue", "Cancel");

			PlayerData[playerid][pAge] = strval(inputtext);
			ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Character Origin", "Please input your Character Origin:", "Continue", "Quit");
		}
		else
		{
		    ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "Please Insert your Character Age", "Continue", "Cancel");
		}
	}
	if(dialogid == DIALOG_ORIGIN)
	{
	    if(!response)
	        return ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Character Origin", "Please input your Character Origin:", "Continue", "Quit");

		if(strlen(inputtext) < 1)
		    return ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, "Character Origin", "Please input your Character Origin:", "Continue", "Quit");

        format(PlayerData[playerid][pOrigin], 32, inputtext);
        ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Character Gender", "Male\nFemale", "Continue", "Cancel");
	}
	if(dialogid == DIALOG_GENDER)
	{
	    if(!response)
	        return ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Character Gender", "Male\nFemale", "Continue", "Cancel");

		if(listitem == 0)
		{
			PlayerData[playerid][pGender] = 1;
			PlayerData[playerid][pSkin] = 240;
			PlayerData[playerid][pHealth] = 100.0;
			PlayerData[playerid][pHunger] = 100;
			PlayerData[playerid][pThirst] = 100;
			SetupPlayerData(playerid);
		}
		if(listitem == 1)
		{
			PlayerData[playerid][pGender] = 1;
			PlayerData[playerid][pSkin] = 172;
			PlayerData[playerid][pHealth] = 100.0;
			PlayerData[playerid][pHunger] = 100;
			PlayerData[playerid][pThirst] = 100;
			SetupPlayerData(playerid);
		}
	}
	return 1;
}

public OnPlayerSpawn(playerid)
{
	if(!PlayerData[playerid][pSpawned])
	{
	    PlayerData[playerid][pSpawned] = true;
	    SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
	    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
	    SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
	}
	return 1;
}


public OnPlayerText(playerid, text[])
{
	text[0] = toupper(text[0]);
	SendNearbyMessage(playerid, 20.0, -1, "%s says: %s", GetName(playerid), text);
    return 0;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
    if(success == 0)
    {
       return SendClientMessage(playerid, X11_GRAY, "[ERROR] Command tidak di temukan silahkan /help untuk mencari command");
    }
    return 1;
}