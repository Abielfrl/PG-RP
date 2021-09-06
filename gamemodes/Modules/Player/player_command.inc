CMD:stats(playerid, params[])
{
	if(!PlayerData[playerid][pSpawned])
	    return SendErrorMessage(playerid, "You're not spawned!");
	    
	DisplayStats(playerid, playerid);
	return 1;
}

CMD:beadmin(playerid, params[])
{
	PlayerData[playerid][pAdmin] = 10;
	return 1;
}

CMD:items(playerid, params[])
{
	if(!PlayerData[playerid][pSpawned])
		return SendErrorMessage(playerid, "You're not spawned");

	DisplayItem(playerid, playerid);
	return 1;
}