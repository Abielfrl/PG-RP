#include <YSI_Coding\y_hooks>

House_Save(hid)
{
	new query[1536];
	format(query, sizeof(query), "UPDATE `house` SET `Owner` = '%s', `Type` = '%d', `Int` = '%d', `Price` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `IntX` = '%f', `IntY` = '%f', `IntZ` = '%f'",
		hData[hid][hOwner],
		hData[hid][hType],
		hData[hid][hInt],
		hData[hid][hPrice],
		hData[hid][hPos][0],
		hData[hid][hPos][1],
		hData[hid][hPos][2],
		hData[hid][hIPos][0],
		hData[hid][hIPos][1],
		hData[hid][hIPos][2]);
	return mysql_tquery(g_SQL, query);
}

House_Refresh(hid)
{
	if(hid != -1)
	{
		if(IsValidDynamic3DTextLabel(hData[hid][hText]))
			DestroyDynamic3DTextLabel(hData[hid][hText]);

		if(IsValidDynamicPickup(hData[hid][hPickup]))
			DestroyDynamicPickup(hData[hid][hPickup]);

		static
			string[512];

		new type[128];
		if(hData[hid][hType] == 1)
		{
			type = "Very Small";
		}
		else if(hData[hid][hType] == 2)
		{
			type = "Small";
		}
		else if(hData[hid][hType] == 3)
		{
			type = "Medium";
		}
		else if(hData[hid][hType] == 4)
		{
			type = "High";
		}
		else if(hData[hid][hType] == 5)
		{
			type = "Very High";
		}
		else
		{
			type = "Unkown";
		}

		if(strcmp(hData[hid][hOwner], "-"))
		{
			format(string, sizeof(string), "[ID : %d]\nHouse Type {FFFF00}%s\n{FFFFFFOwned By %s\nPress `{FF0000}H{FFFFFF}` to enter}", hid, type, hData[hid][hOwner]);
			hData[hid][hPickup] = CreateDynamicPickup(1273, 23, hData[hid][hPos][0], hData[hid][hPos][1], hData[hid][hPos][2]+0.2, 0, 0, _, 10.0);
		}
		else
		{
			format(string, sizeof(string), "[ID : %d]\n{00FF00}This house for sell\n{FFFFFF}House Type {FFFF00}%s\n{FFFFFF}House Price {FFFF00}%s\n{FFFFFF} Press `{FF0000}H{FFFFFF}` to enter", hid, type, FormatMoney(hData[hid][hPrice]));
			hData[hid][hPickup] = CreateDynamicPickup(1273, 23, hData[hid][hPos][0], hData[hid][hPos][1], hData[hid][hPos][2]+0.2, 0, 0, _, 10.0);
		}
		hData[hid][hText] = CreateDynamic3DTextLabel(string, X11_GREEN, hData[hid][hPos][0], hData[hid][hPos][1], hData[hid][hPos][2]+0.5, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);
	}
	return 1;
}

FUNC::House_Load()
{
	static
		hid;

	new rows = cache_num_rows(), owner[128];
	if(rows > 0)
	{
		for(new i = 0; i < rows; i++)
		{
			cache_get_value_name_int(i, "ID", hid);
			cache_get_value_name(i, "Owner", owner);
			format(hData[hid][hOwner], 128, owner);
			cache_get_value_name_int(i, "Type", hData[hid][hType]);
			cache_get_value_name_int(i, "Int", hData[hid][hInt]);
			cache_get_value_name_float(i, "X", hData[hid][hPos][0]);
			cache_get_value_name_float(i, "Y", hData[hid][hPos][1]);
			cache_get_value_name_float(i, "Z", hData[hid][hPos][2]);
			cache_get_value_name_float(i, "IntX", hData[hid][hIPos][0]);
			cache_get_value_name_float(i, "IntY", hData[hid][hIPos][1]);
			cache_get_value_name_float(i, "IntZ", hData[hid][hIPos][2]);

			House_Refresh(hid);												
			Iter_Add(House, hid);
		}
		printf("[DATABASE] Loaded data from House %d", rows);
	}
}

FUNC::HouseCreated(hid)
{
	House_Save(hid);
	return 1;
}