FUNC::PlayerCheck(playerid, rcc)
{
	if(rcc != g_RaceCheck{playerid})
	    return Kick(playerid);
	    
	CheckAccount(playerid);
	return true;
}

FUNC::CheckPlayerUCP(playerid)
{
	new rows = cache_num_rows();
	new str[256];
	if (rows)
	{
	    cache_get_value_name(0, "UCP", tempUCP[playerid]);
	    format(str, sizeof(str), "Welcome Back to Roleplay Server!\n\nYour UCP: %s\nPlease insert your Password below to logged in:", GetName(playerid));
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "UCP - Login", str, "Login", "Exit");
	}
	else
	{
	    format(str, sizeof(str), "Welcome to Roleplay Server!\n\nYour UCP: %s\nPlease insert your Password below to register:", GetName(playerid));
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "UCP - Register", str, "Register", "Exit");
	}
	return 1;
}

FUNC::LoadCharacterData(playerid)
{
	cache_get_value_name_int(0, "pID", PlayerData[playerid][pID]);
	cache_get_value_name(0, "Name", PlayerData[playerid][pName]);
	cache_get_value_name_float(0, "PosX", PlayerData[playerid][pPos][0]);
	cache_get_value_name_float(0, "PosY", PlayerData[playerid][pPos][1]);
	cache_get_value_name_float(0, "PosZ", PlayerData[playerid][pPos][2]);
	cache_get_value_name_float(0, "Health", PlayerData[playerid][pHealth]);
	cache_get_value_name_int(0, "Interior", PlayerData[playerid][pInterior]);
	cache_get_value_name_int(0, "World", PlayerData[playerid][pWorld]);
	cache_get_value_name_int(0, "Age", PlayerData[playerid][pAge]);
	cache_get_value_name(0, "Origin", PlayerData[playerid][pOrigin]);
	cache_get_value_name_int(0, "Gender", PlayerData[playerid][pGender]);
	cache_get_value_name_int(0, "Skin", PlayerData[playerid][pSkin]);
	cache_get_value_name(0, "UCP", PlayerData[playerid][pUCP]);
	cache_get_value_name_int(0, "Admin", PlayerData[playerid][pAdmin]);
	cache_get_value_name_int(0, "Money", PlayerData[playerid][pMoney]);
	cache_get_value_name_int(0, "Hunger", PlayerData[playerid][pHunger]);
	cache_get_value_name_int(0, "Thirst", PlayerData[playerid][pThirst]);
	cache_get_value_name_int(0, "Bandage", PlayerData[playerid][pBandage]);
	cache_get_value_name_int(0, "Ciggar", PlayerData[playerid][pCiggar]);
	cache_get_value_name_int(0, "Snack", PlayerData[playerid][pSnack]);
	cache_get_value_name_int(0, "Sprunk", PlayerData[playerid][pSprunk]);
	cache_get_value_name_int(0, "Phone", PlayerData[playerid][pPhone]);
	cache_get_value_name_int(0, "PhoneCredits", PlayerData[playerid][pPhoneCredit]);
		
    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2], 0.0, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    SendServerMessage(playerid, "Successfully loaded your characters database!");
    return 1;
}

FUNC::HashPlayerPassword(playerid, hashid)
{
	new
		query[256],
		hash[BCRYPT_HASH_LENGTH];

    bcrypt_get_hash(hash, sizeof(hash));

	GetPlayerName(playerid, tempUCP[playerid], MAX_PLAYER_NAME + 1);

	format(query,sizeof(query),"INSERT INTO `PlayerUCP` (`UCP`, `Password`) VALUES ('%s', '%s')", tempUCP[playerid], hash);
	mysql_tquery(g_SQL, query);

    SendServerMessage(playerid, "Your UCP is successfully registered!");
    CheckAccount(playerid);
	return 1;
}

FUNC::LoadCharacter(playerid)
{
	for (new i = 0; i < MAX_CHARS; i ++)
	{
		PlayerChar[playerid][i][0] = EOS;
	}
	for (new i = 0; i < cache_num_rows(); i ++)
	{
		cache_get_value_name(i, "Name", PlayerChar[playerid][i]);
	}
  	ShowCharacterList(playerid);
  	Load_Vehicle(playerid);
  	return 1;
}

FUNC::OnPlayerPasswordChecked(playerid, bool:success)
{
	new str[256];
    format(str, sizeof(str), "Welcome Back to Roleplay Server!\n\nYour UCP: %s\nPlease insert your Password below to logged in:", GetName(playerid));
    
	if(!success)
        return ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "UCP - Login", str, "Login", "Exit");

	new query[256];
	format(query, sizeof(query), "SELECT `Name` FROM `characters` WHERE `UCP` = '%s' LIMIT %d;", GetName(playerid), MAX_CHARS);
	mysql_tquery(g_SQL, query, "LoadCharacter", "d", playerid);
	return 1;
}

FUNC::InsertPlayerName(playerid, name[])
{
	new count = cache_num_rows(), query[145], Cache:execute;
	if(count > 0)
	{
        ShowPlayerDialog(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Create Character", "ERROR: This name is already used by the other player!\nInsert your new Character Name\n\nExample: Finn_Xanderz, Javier_Cooper etc.", "Create", "Back");
	}
	else
	{
		mysql_format(g_SQL,query,sizeof(query),"INSERT INTO `characters` (`Name`,`UCP`) VALUES('%e','%e')",name,GetName(playerid));
		execute = mysql_query(g_SQL, query);
		PlayerData[playerid][pID] = cache_insert_id();
	 	cache_delete(execute);
	 	SetPlayerName(playerid, name);
		format(PlayerData[playerid][pName], MAX_PLAYER_NAME, name);
	 	ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "Please Insert your Character Age", "Continue", "Cancel");
	}
	return 1;
}

FUNC::SetPlayerToUnfreeze(playerid, Float:x, Float:y, Float:z, Float:a)
{
    if(!IsPlayerInRangeOfPoint(playerid, 15.0, x, y, z))
        return 0;

    PlayerData[playerid][pFreeze] = 0;
    SetPlayerPos(playerid, x, y, z);
	SetPlayerFacingAngle(playerid, a);
    TogglePlayerControllable(playerid, 1);
    return 1;
}