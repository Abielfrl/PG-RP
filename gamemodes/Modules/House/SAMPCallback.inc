#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_CTRL_BACK))
	{
		foreach(new hid : House)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, hData[hid][hPos][0], hData[hid][hPos][1], hData[hid][hPos][2]))
			{
				if(hData[hid][hIPos][0], hData[hid][hIPos][1], hData[hid][hIPos][2])
					return SendErrorMessage(playerid, "Bussines ini tidak mempunya Interior");

				PlayerData[playerid][pInHouse] = hid;
				SetPlayerPositionEx(playerid, hData[hid][hPos][0], hData[hid][hPos][1], hData[hid][hPos][2], 0.0);

				SetPlayerInterior(playerid, hData[hid][hInt]);
				SetPlayerVirtualWorld(playerid, hid);
				SetCameraBehindPlayer(playerid);				
			}
		}
		new hid = PlayerData[playerid][pInHouse];
		if(PlayerData[playerid][pInHouse] != -1 && IsPlayerInRangeOfPoint(playerid, 3.0, hData[hid][hPos][0], hData[hid][hPos][1], hData[hid][hPos][2]))
		{
			PlayerData[playerid][pInHouse] = -1;
			SetPlayerPositionEx(playerid, hData[hid][hPos][0], hData[hid][hPos][1], hData[hid][hPos][2], 0.0);

			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			SetCameraBehindPlayer(playerid);
		}
	}
	return 1;
}