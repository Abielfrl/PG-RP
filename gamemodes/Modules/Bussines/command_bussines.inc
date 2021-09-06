CMD:createbiz(playerid, params[])
{
	new bid = Iter_Free(Bussines);
	if(bid == -1)
		return SendErrorMessage(playerid, "Tidak dapat membuat Bussines lagi / Terkena limit");

	new price, type, query[512];
	if(sscanf(params, "dd", price, type))
		return SendUsageMessage(playerid, "/createbiz [price] [type, 1.Retail Store | 2.Electronic Store | 3.Clothes Store | 4.Furniture]");

	format(bData[bid][bOwner], 128, "-");
	GetPlayerPos(playerid, bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2]);
	bData[bid][bPrice] = price;
	bData[bid][bType] = type;
	bData[bid][bP][0] = 0;
	bData[bid][bP][1] = 0;
	bData[bid][bP][2] = 0;
	bData[bid][bP][3] = 0;
	bData[bid][bP][4] = 0;
	bData[bid][bP][5] = 0;
	bData[bid][bP][6] = 0;
	bData[bid][bP][7] = 0;
	bData[bid][bP][8] = 0;
	bData[bid][bP][9] = 0;
	bData[bid][bInt] = 0;
	bData[bid][bIPos][0] = 0;
	bData[bid][bIPos][1] = 0;
	bData[bid][bIPos][2] = 0;

	Bussines_Refresh(bid);
	Iter_Add(Bussines, bid);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO bussines SET `ID` = '%d', `Owner` = '%s', `bX` = '%f', `bY` = '%f', `bZ` = '%f', `Price` = '%d', `Type` = '%d'", bid, bData[bid][bOwner], bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2], bData[bid][bPrice], bData[bid][bType]);
	mysql_tquery(g_SQL, query, "OnBizCreated", "i", bid);
	return 1;
}

CMD:buy(playerid, params[])
{
	foreach(new bid : Bussines)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, bData[bid][bPointPos][0], bData[bid][bPointPos][1], bData[bid][bPointPos][2]))
		{
			Bussines_ShowProduct(playerid, bid);
		}
	}
	return 1;
}

CMD:editbiz(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 10)
		return SendErrorMessage(playerid, "Kamu tidak bisa menggunakan CMD Ini");

    static
        bid,
        type[24],
        string[128];

    if(sscanf(params, "ds[24]S()[128]", bid, type, string))
    {
    	SendUsageMessage(playerid, "/editbiz [bizid] [entity]");
    	SendClientMessageEx(playerid, X11_GRAY, "[ENTITY] Location, Interior, Point, Price, Remove");
    	return 1;
    }

    if((bid < 0 || bid >= MAX_BUSSINES))
    	return SendErrorMessage(playerid, "You have specified an Invalid ID");

    if(!strcmp(type, "location", true))
    {
    	GetPlayerPos(playerid, bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2]);

    	Bussines_Refresh(bid);
    	Bussines_Save(bid);

    	SendServerMessage(playerid, "You have been Update Location bussines ID %d", bid);
    }
    else if(!strcmp(type, "interior", true))
    {
    	GetPlayerPos(playerid, bData[bid][bIPos][0], bData[bid][bIPos][1], bData[bid][bIPos][2]);

    	Bussines_Refresh(bid);
    	Bussines_Save(bid);

    	SendServerMessage(playerid, "You have been update Interior bussines ID %d", bid);
    }
    else if(!strcmp(type, "point", true))
    {
    	new
    		Float:x,
    		Float:y,
    		Float:z;

    	GetPlayerPos(playerid, x, y, z);
    	bData[bid][bPointPos][0] = x;
    	bData[bid][bPointPos][1] = y;
    	bData[bid][bPointPos][2] = z;

    	Bussines_Refresh(bid);
    	Bussines_Save(bid);

    	SendServerMessage(playerid, "You have been update Buy Point bussines ID %d", bid);
    }
    else if(!strcmp(type, "remove", true))
    {
    	Bussines_Reset(bid);

		DestroyDynamic3DTextLabel(bData[bid][bLable]);
        DestroyDynamicPickup(bData[bid][bPickup]);
        DestroyDynamicCP(bData[bid][bCP]);

        bData[bid][bPos][0] = 0;
        bData[bid][bPos][1] = 0;
        bData[bid][bPos][2] = 0;
        bData[bid][bIPos][0] = 0;
        bData[bid][bIPos][1] = 0;
        bData[bid][bIPos][2] = 0;
		bData[bid][bLable] = Text3D:INVALID_3DTEXT_ID;
		bData[bid][bPickup] = -1;             
		bData[bid][bInt] = 0;

		Iter_Remove(Bussines, bid);
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM bussines WHERE `ID` = '%d'", bid);
		mysql_tquery(g_SQL, query);
		SendServerMessage(playerid, "You has been deleted Bussines ID %d", bid);   
    }
	return 1;
}

CMD:sellbiz(playerid, params[])
{
	return 1;
}

CMD:sealbiz(playerid, params[])
{
	// TODO: Goverment / Police seal a Bussines
	return 1;
}