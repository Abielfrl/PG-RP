CMD:createhouse(playerid, params[])
{
	new hid = Iter_Free(House);
	if(hid == -1)
		return SendErrorMessage(playerid, "Kamu tidak bisa melakukan ini");

	new price, type, query[512];
	if(sscanf(params, "dd", price, type))
		return SendUsageMessage(playerid, "/createhouse [price] [type, 1 : Very Small | 2 : Small | 3 : Medium | 4 : High | 5 : Very High]");

	format(hData[hid][hOwner], 128,  "-");
	GetPlayerPos(playerid, hData[hid][hPos][0], hData[hid][hPos][1], hData[hid][hPos][2]);
	hData[hid][hPrice] = price;
	hData[hid][hType] = type;
	hData[hid][hIPos][0] = 0;
	hData[hid][hIPos][1] = 0;
	hData[hid][hIPos][2] = 0;

	House_Refresh(hid);
	Iter_Add(House, hid);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO house SET ID='%d', Owner='%s', Price='%d', Type='%d', IntX='%f', IntY='%f', IntZ='%f'", hid, hData[hid][hOwner], hData[hid][hPrice], hData[hid][hType], hData[hid][hIPos][0], hData[hid][hIPos][1], hData[hid][hIPos][2]);
	mysql_tquery(g_SQL, query, "HouseCreated", "i", hid);	
	return 1;
}