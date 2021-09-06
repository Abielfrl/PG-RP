CMD:aveh(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 9)
		return SendErrorMessage(playerid, "Kamu tidak memiliki akses untuk menggunakan CMD Ini");

	new veh;
	if(sscanf(params, "d", veh))
		return SendUsageMessage(playerid, "/aveh [vehicletype]");

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	CreateVehicle(veh, x, y, z, 0.0, 1, 1, 1);
	return 1;
}

new pOldName[MAX_PLAYER_NAME][24];
CMD:aod(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (!PlayerData[playerid][pAdminDuty])
	{
		SetPlayerColor(playerid, COLOR_RED);
        format(pOldName[playerid], 24, "%s", GetName(playerid));
        SetPlayerName(playerid, PlayerData[playerid][pUCP]);
		PlayerData[playerid][pAdminDuty] = 1;
	}
	else
	{
	    SetPlayerColor(playerid, DEFAULT_COLOR);
		PlayerData[playerid][pAdminDuty] = 0;
		SetPlayerName(playerid, pOldName[playerid]);
	}
	return 1;
}

CMD:kick(playerid, params[])
{
	SendClientMessageEx(playerid, X11_TOMATO, "AdmCmd:"WHITE"Anda di kick dari dari server");
	return 1;
}

CMD:resetmoney(playerid, params[])
{
	return 1;
}