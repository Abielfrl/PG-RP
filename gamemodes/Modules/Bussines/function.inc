Bussines_Save(bid)
{
	new cQuery[1536];
	format(cQuery, sizeof(cQuery), "UPDATE bussines SET\
	 `Owner` = '%s', `Name` = '%s', `Type` = '%d', `Price` = '%d',\
	  `Product` = '%d', `Money` = '%d', `Int` = '%d',\
	   `bX` = '%f', `bY` = '%f', `bZ` = '%f',\
	    `bIX` = '%f', `bIY` = '%f', `bIZ` = '%f',\
	     `pX` = '%f', `pY` = '%f', `pZ` = '%f',\
	      `bP0` = '%d', `bP1` = '%d', `bP2` = '%d', `bP3` = '%d', `bP4` = '%d', `bP5` = '%d',\
	       `bP6` = '%d', `bP7` = '%d', `bP8` = '%d', `bP9` = '%d', `bP10` = '%d'\
	        WHERE\
	         `ID` = '%d'",
		bData[bid][bOwner],
		bData[bid][bName],
		bData[bid][bType],
		bData[bid][bPrice],
		bData[bid][bProduct],
		bData[bid][bMoney],
		bData[bid][bInt],
		bData[bid][bPos][0],
		bData[bid][bPos][1],
		bData[bid][bPos][2],
		bData[bid][bIPos][0],
		bData[bid][bIPos][1],
		bData[bid][bIPos][2],
		bData[bid][bPointPos][0],
		bData[bid][bPointPos][1],
		bData[bid][bPointPos][2],
		bData[bid][bP][0],
		bData[bid][bP][1],
		bData[bid][bP][2],
		bData[bid][bP][3],
		bData[bid][bP][4],
		bData[bid][bP][5],
		bData[bid][bP][6],
		bData[bid][bP][7],
		bData[bid][bP][8],
		bData[bid][bP][9],
		bData[bid][bP][10],
		bid);
	return mysql_tquery(g_SQL, cQuery);
}

Bussines_Refresh(bid)
{
	if(bid != -1)
	{
		if(IsValidDynamic3DTextLabel(bData[bid][bLable]))
			DestroyDynamic3DTextLabel(bData[bid][bLable]);

		if(IsValidDynamic3DTextLabel(bData[bid][bLablePoint]))
			DestroyDynamic3DTextLabel(bData[bid][bLablePoint]);

		if(IsValidDynamicPickup(bData[bid][bPickup]))
			DestroyDynamicPickup(bData[bid][bPickup]);

		if(IsValidDynamicPickup(bData[bid][bPickPoint]))
			DestroyDynamicPickup(bData[bid][bPickPoint]);

		if(IsValidDynamicCP(bData[bid][bCP]))
			DestroyDynamicCP(bData[bid][bCP]);

		static
			string[522], tstr[128];

		new type[128];
		if(bData[bid][bType] == 1)
		{
			type = "Restaurant";
		}
		else if(bData[bid][bType] == 2)
		{
			type = "Retail Store";
		}
		else if(bData[bid][bType] == 3)
		{
			type = "Electronic Store";
		}
		else if(bData[bid][bType] == 4)
		{
			type = "Furniture";
		}
		else
		{
			type = "Unkown";
		}

		if(strcmp(bData[bid][bOwner], "-"))
		{
			format(string, sizeof(string), "[Bisnis ID : %d]\n"WHITE"Name {FFFF00}%s\n"WHITE"Owned By {FFFF00}%s{FFFFFF}\nBussines Type {FFFF00}%s{FFFFFF}\nPress '{FF0000}H{FFFFFF}' to Enter", bid, bData[bid][bName], bData[bid][bOwner], type);
			bData[bid][bPickup] = CreateDynamicPickup(19133, 23, bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2]+0.2, 0, 0, _, 8.0);
		}
		else
		{
			format(string, sizeof(string), "[Bisnis ID : %d]\n"WHITE"This Bussines for sell\nPrice : {FFFF00}%d{FFFFFF}\nType: {FFFF00}%s\n"WHITE"Type /buy to buy this Bussines", bid, bData[bid][bPrice], type);
			bData[bid][bPickup] = CreateDynamicPickup(19133, 23, bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2]+0.2, 0, 0, _, 8.0);
		}

		bData[bid][bPickPoint] = CreateDynamicPickup(1274, 23, bData[bid][bPointPos][0], bData[bid][bPointPos][1], bData[bid][bPointPos][2]+0.2, bid, bData[bid][bInt], _, 4);

		bData[bid][bLable] = CreateDynamic3DTextLabel(string, X11_LIGHTBLUE, bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2]+0.5, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);

		format(tstr, 128, "[ID : %d]\n{7fffd4}Bisnis Point\n{FF00FF}use '/buy' here", bid);
		bData[bid][bLablePoint] = CreateDynamic3DTextLabel(tstr, X11_LIGHTBLUE, bData[bid][bPointPos][0], bData[bid][bPointPos][1], bData[bid][bPointPos][2]+0.5, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);				
	}
	return 1;
}

FUNC::Bussines_Load()
{
	static bid;

	new rows = cache_num_rows(), owner[128], name[128];
	if(rows)
	{
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "ID", bid);
			cache_get_value_name(i, "Owner", owner);
			format(bData[bid][bOwner], 128, owner);
			cache_get_value_name(i, "Name", name);
			format(bData[bid][bName], 128, name);
			cache_get_value_name_int(i, "Type", bData[bid][bType]);
			cache_get_value_name_int(i, "Price", bData[bid][bPrice]);
			cache_get_value_name_int(i, "Product", bData[bid][bProduct]);
			cache_get_value_name_int(i, "Money", bData[bid][bMoney]);
			cache_get_value_name_int(i, "Int", bData[bid][bInt]);
			cache_get_value_name_float(i, "bX", bData[bid][bPos][0]);
			cache_get_value_name_float(i, "bY", bData[bid][bPos][1]);
			cache_get_value_name_float(i, "bZ", bData[bid][bPos][2]);
			cache_get_value_name_float(i, "bIX", bData[bid][bIPos][0]);
			cache_get_value_name_float(i, "bIY", bData[bid][bIPos][1]);
			cache_get_value_name_float(i, "bIZ", bData[bid][bIPos][2]);
			cache_get_value_name_float(i, "pX", bData[bid][bPointPos][0]);
			cache_get_value_name_float(i, "pY", bData[bid][bPointPos][1]);
			cache_get_value_name_float(i, "pZ", bData[bid][bPointPos][2]);
			cache_get_value_name_int(i, "bP0", bData[bid][bP][0]);
			cache_get_value_name_int(i, "bP1", bData[bid][bP][1]);
			cache_get_value_name_int(i, "bP2", bData[bid][bP][2]);
			cache_get_value_name_int(i, "bP3", bData[bid][bP][3]);
			cache_get_value_name_int(i, "bP4", bData[bid][bP][4]);
			cache_get_value_name_int(i, "bP5", bData[bid][bP][5]);
			cache_get_value_name_int(i, "bP6", bData[bid][bP][6]);
			cache_get_value_name_int(i, "bP7", bData[bid][bP][7]);
			cache_get_value_name_int(i, "bP8", bData[bid][bP][8]);
			cache_get_value_name_int(i, "bP9", bData[bid][bP][9]);
			cache_get_value_name_int(i, "bP10", bData[bid][bP][10]);

			Bussines_Refresh(bid);
			Iter_Add(Bussines, bid);
		}
		printf("[Bussines] Loaded Bussines : %d", rows);
	}
}

Bussines_ShowProduct(playerid, bid)
{
	if(bid <= -1)
		return 0;

	static
		string[512];

	switch(bData[bid][bType])
	{
		case 1: // Restaurant Bussines
		{
			format(string, sizeof(string), "Product\tPrice\n{FFFFFF}Fried Chicken\t{7fff00}%d\n{FFFFFF}Chicken Nugget\t{7fff00}%d\n{FFFFFF}Sprunk\t{7fff00}%d",
				FormatMoney(bData[bid][bP][0]),
				FormatMoney(bData[bid][bP][1]),
				FormatMoney(bData[bid][bP][2]));
			ShowPlayerDialog(playerid, BUSSINES_BUYMENU, DIALOG_STYLE_TABLIST_HEADERS, bData[bid][bName], string, "Buy", "Cancel");
		}
		case 2: // Retail Bussines
		{
			format(string, sizeof(string), "Product\tPrice\n{FFFFFF}Bandage\t{7fff00}%d\n{FFFFFF}Cigarette\t{7fff00}%d\n{FFFFFF}Snack\t{7fff00}%d\n{FFFFFF}Sprunk\t{7fff00}%d",
				FormatMoney(bData[bid][bP][0]),
				FormatMoney(bData[bid][bP][1]),
				FormatMoney(bData[bid][bP][2]),
				FormatMoney(bData[bid][bP][3]));
			ShowPlayerDialog(playerid, BUSSINES_BUYMENU, DIALOG_STYLE_TABLIST_HEADERS, bData[bid][bName], string, "Buy", "Cancel");
		}
		case 3: // Electronic Store
		{
			format(string, sizeof(string), "Product\tPrice\n{FFFFFF}Phone\t{7fff00}%d\n{FFFFFF}Phone Credit(1000)\t{7fff00}%d\n{FFFFFF}Radio MP3\t{7fff00}%d",
				FormatMoney(bData[bid][bP][0]),
				FormatMoney(bData[bid][bP][1]),
				FormatMoney(bData[bid][bP][2]));
			ShowPlayerDialog(playerid, BUSSINES_BUYMENU, DIALOG_STYLE_TABLIST_HEADERS, bData[bid][bName], string, "Buy", "Cancel");
		}
	}
	return 1;
}

FUNC::OnBizCreated(bid)
{
	Bussines_Save(bid);
	return 1;
}

Bussines_Reset(id)
{
	format(bData[id][bOwner], MAX_PLAYER_NAME, "-");
	Bussines_Refresh(id);
}