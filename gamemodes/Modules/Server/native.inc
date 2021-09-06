stock GetName(playerid)
{
	new name[MAX_PLAYER_NAME];
 	GetPlayerName(playerid,name,sizeof(name));
	return name;
}

new const g_arrVehicleNames[][] = {
    "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perrenial", "Sentinel", "Dumper", "Firetruck", "Trashmaster",
    "Stretch", "Manana", "Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
    "Esperanto", "Taxi", "Washington", "Bobcat", "Whoopee", "BF Injection", "Hunter", "Premier", "Enforcer",
    "Securicar", "Banshee", "Predator", "Bus", "Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach",
    "Cabbie", "Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral", "Squalo", "Seasparrow",
    "Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair",
    "Berkley's RC Van", "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic",
    "Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350", "Walton",
    "Regina", "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper", "Rancher",
    "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking", "Blista Compact", "Police Maverick",
    "Boxville", "Benson", "Mesa", "RC Goblin", "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher",
    "Super GT", "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stunt", "Tanker", "Roadtrain",
    "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck",
    "Fortune", "Cadrona", "SWAT Truck", "Willard", "Forklift", "Tractor", "Combine", "Feltzer", "Remington", "Slamvan",
    "Blade", "Streak", "Freight", "Vortex", "Vincent", "Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder",
    "Primo", "Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite", "Windsor", "Monster", "Monster",
    "Uranus", "Jester", "Sultan", "Stratum", "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito",
    "Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper", "Broadway", "Tornado", "AT-400", "DFT-30",
    "Huntley", "Stafford", "BF-400", "News Van", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club",
    "Freight Box", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch", "LSPD Car", "SFPD Car", "LVPD Car",
    "Police Rancher", "Picador", "S.W.A.T", "Alpha", "Phoenix", "Glendale", "Sadler", "Luggage", "Luggage", "Stairs",
    "Boxville", "Tiller", "Utility Trailer"
};

Database_Connect()
{
	g_SQL = mysql_connect(DATABASE_ADDRESS,DATABASE_USERNAME,DATABASE_PASSWORD,DATABASE_NAME);

	if(mysql_errno(g_SQL) != 0){
	    print("[MySQL] - Connection Failed!");
	}
	else{
		print("[MySQL] - Connection Estabilished!");
	}
}

stock IsRoleplayName(player[])
{
    for(new n = 0; n < strlen(player); n++)
    {
        if (player[n] == '_' && player[n+1] >= 'A' && player[n+1] <= 'Z') return 1;
        if (player[n] == ']' || player[n] == '[') return 0;
	}
    return 0;
}

stock IsPlayerNearPlayer(playerid, targetid, Float:radius)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetPlayerPos(targetid, fX, fY, fZ);

	return (GetPlayerInterior(playerid) == GetPlayerInterior(targetid) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid)) && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ);
}

stock SendNearbyMessage(playerid, Float:radius, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 16)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 16); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit CONST.alt 4
		#emit SUB
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (IsPlayerNearPlayer(i, playerid, radius) && PlayerData[i][pSpawned])
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (IsPlayerNearPlayer(i, playerid, radius) && PlayerData[i][pSpawned])
		{
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

stock SendClientMessageEx(playerid, colour, const text[], va_args<>)
{
    new str[145];
    va_format(str, sizeof(str), text, va_start<3>);
    return SendClientMessage(playerid, colour, str);
}

stock CheckAccount(playerid)
{
	new query[256];
	format(query, sizeof(query), "SELECT * FROM `PlayerUCP` WHERE `UCP` = '%s' LIMIT 1;", GetName(playerid));
	mysql_tquery(g_SQL, query, "CheckPlayerUCP", "d", playerid);
	return 1;
}

stock SetupPlayerData(playerid)
{
    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], 1642.1681, -2333.3689, 13.5469, 0.0, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    return 1;
}

stock SaveData(playerid)
{
	new query[1012];
	if(PlayerData[playerid][pSpawned])
	{
		GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

	    format(query, sizeof(query), "UPDATE `characters`\
	     SET\
	      `PosX` = '%.4f', `PosY` = '%.4f', `PosZ` = '%.4f',\
	       `Health` = '%.4f', `World` = '%d', `Interior` = '%d',\
	        `Age` = '%d', `Origin` = '%s', `Gender` = '%d', `Skin` = '%d',\
	         `UCP` = '%s', `Admin` = '%d', `Money` = '%d', \
	          `Bandage` = '%d', `Ciggar` = '%d', `Snack` = '%d', \
	           `Phone` = '%d', `PhoneCredit` = '%d'\
	            `Sprunk` = '%d',`Hunger` = '%d', `Thirst` = '%d'\
	          WHERE `pID`= '%d'",
			PlayerData[playerid][pPos][0],
			PlayerData[playerid][pPos][1],
			PlayerData[playerid][pPos][2],
			PlayerData[playerid][pHealth],
			GetPlayerVirtualWorld(playerid),
			GetPlayerInterior(playerid),
			PlayerData[playerid][pAge],
			PlayerData[playerid][pOrigin],
			PlayerData[playerid][pGender],
			PlayerData[playerid][pSkin],
			PlayerData[playerid][pUCP],
			PlayerData[playerid][pAdmin],
			PlayerData[playerid][pMoney],
			PlayerData[playerid][pBandage],
			PlayerData[playerid][pCiggar],
			PlayerData[playerid][pSnack],
			PlayerData[playerid][pPhone],
			PlayerData[playerid][pPhoneCredit],
			PlayerData[playerid][pSprunk],
			PlayerData[playerid][pHunger],
			PlayerData[playerid][pThirst],
			PlayerData[playerid][pID]
		);
		mysql_tquery(g_SQL, query);
		Save_Vehicle(playerid);
	}
	return 1;
}

ShowCharacterList(playerid)
{
	new name[256], count, sgstr[128];

	for (new i; i < MAX_CHARS; i ++) if(PlayerChar[playerid][i][0] != EOS)
	{
	    format(sgstr, sizeof(sgstr), "%s\n", PlayerChar[playerid][i]);
		strcat(name, sgstr);
		count++;
	}
	if(count < MAX_CHARS)
		strcat(name, "Create Character");

	ShowPlayerDialog(playerid, DIALOG_CHARLIST, DIALOG_STYLE_LIST, "Character List", name, "Select", "Quit");
	return 1;
}

DisplayStats(playerid, p2)
{
	new str[512], header[128];
	format(header, sizeof(header), "%s(%s)", PlayerData[p2][pName], PlayerData[pID]);
	format(str, sizeof(str), "{FF0000}In Character:{FFFFFF}\n");
	format(str, sizeof(str), "%sName: [%s] | Gender: [%s] | Age: [%d] | Origin: [%s]\n", str, PlayerData[p2][pName], (PlayerData[p2][pGender] == 2) ? ("Female") : ("Male"), PlayerData[p2][pAge], PlayerData[p2][pOrigin]);
	format(str, sizeof(str), "%s{FF0000}Out Of Character:{FFFFFF}\n", str);
	format(str, sizeof(str), "%sUCP: [%s] | UID: [%d]", str, PlayerData[p2][pUCP], PlayerData[p2][pID]);
	ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_MSGBOX, header, str, "Select", "Cancel");
	return 1;
}

DisplayItem(playerid, p2)
{
	new mstr[512], str[1024];
	format(mstr, sizeof(mstr), "Items (%s)", PlayerData[p2][pName]);
	format(str, sizeof(str), "Name\tAmmount\t\n{00FF00}Money\t{00FF00}%s\n", FormatMoney(PlayerData[p2][pMoney]));
	if(PlayerData[p2][pBandage] > 0)
	{
		format(str, sizeof(str), "%sBandage\t%s", str, PlayerData[p2][pBandage]);	
	}
	ShowPlayerDialog(playerid, DIALOG_ITEMS, DIALOG_STYLE_TABLIST_HEADERS, mstr, str, "Close", "");
}

IsNumeric(const string[])
{
    for (new i = 0, j = strlen(string); i < j; i++)
    {
        if (string[i] > '9' || string[i] < '0') return 0;
    }
    return 1;
}

GetVehicleModelByName(const name[])
{
    if(IsNumeric(name) && (strval(name) >= 400 && strval(name) <= 611))
        return strval(name);

    for (new i = 0; i < sizeof(g_arrVehicleNames); i ++)
    {
        if(strfind(g_arrVehicleNames[i], name, true) != -1)
        {
            return i + 400;
        }
    }
    return 0;
}

FormatMoney(cCash)
{
    new szStr[18], dollar[40];
    format(szStr, sizeof(szStr), "%i", cCash);

    for(new iLen = strlen(szStr) - 3; iLen > 0; iLen -= 3)
    {
        strins(szStr, ",", iLen);
    }
    format(dollar, sizeof(dollar), "$%s", szStr);
    return dollar;
}

SetPlayerPositionEx(playerid, Float:x, Float:y, Float:z, Float:a, time = 3000)
{
    if(PlayerData[playerid][pFreeze])
    {
        KillTimer(PlayerData[playerid][pFreezeTimer]);
        PlayerData[playerid][pFreeze] = 0;
        TogglePlayerControllable(playerid, 1);
    }
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, 0);
    PlayerData[playerid][pFreeze] = 1;
    SetPlayerPos(playerid, x, y, z + 0.5);
    SetPlayerFacingAngle(playerid, a);
    PlayerData[playerid][pFreezeTimer] = SetTimerEx("SetPlayerToUnfreeze", time, false, "iffff", playerid, x, y, z, a);
}

ShowServerTextdraw(playerid)
{
	Hunger[playerid] = CreatePlayerTextDraw(playerid, 610.000000, 390.000000, "HUD:radar_burgershot");
	PlayerTextDrawFont(playerid, Hunger[playerid], 4);
	PlayerTextDrawLetterSize(playerid, Hunger[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Hunger[playerid], 27.500000, 25.000000);
	PlayerTextDrawSetOutline(playerid, Hunger[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Hunger[playerid], 0);
	PlayerTextDrawAlignment(playerid, Hunger[playerid], 1);
	PlayerTextDrawColor(playerid, Hunger[playerid], 16711935);
	PlayerTextDrawBackgroundColor(playerid, Hunger[playerid], -16776961);
	PlayerTextDrawBoxColor(playerid, Hunger[playerid], 16711730);
	PlayerTextDrawUseBox(playerid, Hunger[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Hunger[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Hunger[playerid], 0);

	Thirst[playerid] = CreatePlayerTextDraw(playerid, 610.000000, 421.000000, "HUD:radar_diner");
	PlayerTextDrawFont(playerid, Thirst[playerid], 4);
	PlayerTextDrawLetterSize(playerid, Thirst[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Thirst[playerid], 31.000000, 25.000000);
	PlayerTextDrawSetOutline(playerid, Thirst[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Thirst[playerid], 0);
	PlayerTextDrawAlignment(playerid, Thirst[playerid], 1);
	PlayerTextDrawColor(playerid, Thirst[playerid], 16711935);
	PlayerTextDrawBackgroundColor(playerid, Thirst[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Thirst[playerid], 50);
	PlayerTextDrawUseBox(playerid, Thirst[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Thirst[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Thirst[playerid], 0);

	Blackline[playerid] = CreatePlayerTextDraw(playerid, 602.000000, 379.000000, "ld_chat:dpad_64");
	PlayerTextDrawFont(playerid, Blackline[playerid], 4);
	PlayerTextDrawLetterSize(playerid, Blackline[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Blackline[playerid], 55.000000, 87.000000);
	PlayerTextDrawSetOutline(playerid, Blackline[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Blackline[playerid], 0);
	PlayerTextDrawAlignment(playerid, Blackline[playerid], 1);
	PlayerTextDrawColor(playerid, Blackline[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Blackline[playerid], -1);
	PlayerTextDrawBoxColor(playerid, Blackline[playerid], -206);
	PlayerTextDrawUseBox(playerid, Blackline[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Blackline[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Blackline[playerid], 0);

	ThirstAlert[playerid] = CreatePlayerTextDraw(playerid, 631.000000, 419.000000, "ld_chat:badchat");
	PlayerTextDrawFont(playerid, ThirstAlert[playerid], 4);
	PlayerTextDrawLetterSize(playerid, ThirstAlert[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ThirstAlert[playerid], 9.500000, 7.000000);
	PlayerTextDrawSetOutline(playerid, ThirstAlert[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ThirstAlert[playerid], 0);
	PlayerTextDrawAlignment(playerid, ThirstAlert[playerid], 1);
	PlayerTextDrawColor(playerid, ThirstAlert[playerid], -3841);
	PlayerTextDrawBackgroundColor(playerid, ThirstAlert[playerid], 255);
	PlayerTextDrawBoxColor(playerid, ThirstAlert[playerid], 50);
	PlayerTextDrawUseBox(playerid, ThirstAlert[playerid], 1);
	PlayerTextDrawSetProportional(playerid, ThirstAlert[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, ThirstAlert[playerid], 0);

	HungerAlert[playerid] = CreatePlayerTextDraw(playerid, 631.000000, 388.000000, "ld_chat:badchat");
	PlayerTextDrawFont(playerid, HungerAlert[playerid], 4);
	PlayerTextDrawLetterSize(playerid, HungerAlert[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, HungerAlert[playerid], 9.500000, 7.000000);
	PlayerTextDrawSetOutline(playerid, HungerAlert[playerid], 1);
	PlayerTextDrawSetShadow(playerid, HungerAlert[playerid], 0);
	PlayerTextDrawAlignment(playerid, HungerAlert[playerid], 1);
	PlayerTextDrawColor(playerid, HungerAlert[playerid], -3841);
	PlayerTextDrawBackgroundColor(playerid, HungerAlert[playerid], 255);
	PlayerTextDrawBoxColor(playerid, HungerAlert[playerid], 50);
	PlayerTextDrawUseBox(playerid, HungerAlert[playerid], 1);
	PlayerTextDrawSetProportional(playerid, HungerAlert[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, HungerAlert[playerid], 0);

	//Skin Model
	SkinModel[playerid] = CreatePlayerTextDraw(playerid, 538.000000, 383.000000, "Nowy_TextDraw");
	PlayerTextDrawFont(playerid, SkinModel[playerid], 5);
	PlayerTextDrawLetterSize(playerid, SkinModel[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, SkinModel[playerid], 95.000000, 67.000000);
	PlayerTextDrawSetOutline(playerid, SkinModel[playerid], 0);
	PlayerTextDrawSetShadow(playerid, SkinModel[playerid], 0);
	PlayerTextDrawAlignment(playerid, SkinModel[playerid], 2);
	PlayerTextDrawColor(playerid, SkinModel[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, SkinModel[playerid], 1747094272);
	PlayerTextDrawBoxColor(playerid, SkinModel[playerid], 50);
	PlayerTextDrawUseBox(playerid, SkinModel[playerid], 0);
	PlayerTextDrawSetProportional(playerid, SkinModel[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, SkinModel[playerid], 0);
	PlayerTextDrawSetPreviewModel(playerid, SkinModel[playerid], GetPlayerSkin(playerid));
	PlayerTextDrawSetPreviewRot(playerid, SkinModel[playerid], -10.000000, 0.000000, -20.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, SkinModel[playerid], 1, 1);

	BlacklineModel[playerid] = CreatePlayerTextDraw(playerid, 569.000000, 379.000000, "ld_chat:dpad_64");
	PlayerTextDrawFont(playerid, BlacklineModel[playerid], 4);
	PlayerTextDrawLetterSize(playerid, BlacklineModel[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, BlacklineModel[playerid], 35.000000, 87.000000);
	PlayerTextDrawSetOutline(playerid, BlacklineModel[playerid], 1);
	PlayerTextDrawSetShadow(playerid, BlacklineModel[playerid], 0);
	PlayerTextDrawAlignment(playerid, BlacklineModel[playerid], 1);
	PlayerTextDrawColor(playerid, BlacklineModel[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, BlacklineModel[playerid], -1);
	PlayerTextDrawBoxColor(playerid, BlacklineModel[playerid], -206);
	PlayerTextDrawUseBox(playerid, BlacklineModel[playerid], 1);
	PlayerTextDrawSetProportional(playerid, BlacklineModel[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, BlacklineModel[playerid], 0);		
}

GivePlayerMoneyEx(playerid, money)
{
	PlayerData[playerid][pMoney] += money;
	GivePlayerMoney(playerid, money);
}

ResetPlayerMoneyEx(playerid)
{
	PlayerData[playerid][pMoney] == 0;
	ResetPlayerMoney(playerid);
}

SetPlayerHealthEx(playerid, Float:health)
{
	PlayerData[playerid][pHealth] += health;
	SetPlayerHealth(playerid, health);
}