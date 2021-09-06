FUNC::Save_Vehicle(playerid)
{
	new i = GetPlayerVehicleID(playerid);
	GetVehiclePos(i, vData[i][vPos][0], vData[i][vPos][1], vData[i][vPos][2]);
	GetVehicleZAngle(i, vData[i][vPos][3]);
	new query[1024];
	mysql_format(g_SQL, query, sizeof(query), "UPDATE `vehicle` SET `Owner` = '%d', `Model` = '%d', `Color1` = '%d', `Color2` = '%d', `X` = '%f', `Y` = '%f', `Z` = '%f', `A` = '%f' WHERE `ID` = '%d'",
		vData[i][vOwner],
		vData[i][vModel],
		vData[i][vColor1],
		vData[i][vColor2],
		vData[i][vPos][0],
		vData[i][vPos][1],
		vData[i][vPos][2],
		vData[i][vPos][3],
		vData[i][vID]);
	mysql_tquery(g_SQL, query);
	return 1;
}

FUNC::Load_Vehicle(playerid)
{
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `vehicle` WHERE `Owner` = '%d'", PlayerData[playerid][pID]);
	mysql_tquery(g_SQL, query);

	new count = cache_num_rows();
	if(count > 0)
	{
		for(new z = 0; z < count; z++)
		{
			new i = GetPlayerVehicleID(playerid);
			cache_get_value_name_int(z, "ID", vData[i][vID]);
			cache_get_value_name_int(z, "Owner", vData[i][vOwner]);
			cache_get_value_name_int(z, "Model", vData[i][vModel]);
			cache_get_value_name_int(z, "Color1", vData[i][vColor1]);
			cache_get_value_name_int(z, "Color2", vData[i][vColor2]);
			cache_get_value_name_float(z, "X", vData[i][vPos][0]);
			cache_get_value_name_float(z, "Y", vData[i][vPos][1]);
			cache_get_value_name_float(z, "Z", vData[i][vPos][2]);
			cache_get_value_name_float(z, "A", vData[i][vPos][3]);
		}
		printf("[VEHICLE] Loaded Vehicle from %d", playerid);
	}
}

FUNC::OnVehicleCreated(id, playerid)
{
	if(id == -1)
		return 0;

	vData[id][vID] = cache_insert_id();
	Save_Vehicle(playerid);
	return 1;
}

VehicleCreate(playerid, ownerid, modelid, Float:x, Float:y, Float:z, Float:a, color1, color2)
{
	new i = GetPlayerVehicleID(playerid);
	vData[i][vID] = cache_insert_id();
	vData[i][vOwner] = ownerid;
	vData[i][vModel] = modelid;
	vData[i][vPos][0] = x;
	vData[i][vPos][1] = y;
 	vData[i][vPos][2] = z;
	vData[i][vPos][3] = a;
	vData[i][vColor1] = color1;
	vData[i][vColor2] = color2;
	vData[i][Vehicle] = CreateVehicle(modelid, x, y, z, a, color1, color2, -1);

	mysql_tquery(g_SQL, "INSERT INTO `vehicle` (`Model`) VALUES(0)", "OnVehicleCreated", "dd", i, playerid);
	return -1;
}