CMD:giveveh(playerid, params[])
{
    static
        userid,
        Model[32];

    if(sscanf(params, "us[32]", userid, Model))
    	return SendUsageMessage(playerid, "/giveveh [playerid][modelid]");
    new
        Float:x,
        Float:y,
        Float:z,
        Float:a;

    if((Model[0] = GetVehicleModelByName(Model)) == 0)
        return SendErrorMessage(playerid, "Invalid model");

    GetPlayerPos(userid, x, y, z);
    GetPlayerFacingAngle(userid, a);

    VehicleCreate(playerid, PlayerData[userid][pID], Model[0], x, y + 2, z + 1, a, random(127), random(127));
    SendServerMessage(playerid, "Kamu telah memberikan kendaraan %d kepada {FFFF00}%s's", Model, PlayerData[playerid][pName]);
    return 1;
}