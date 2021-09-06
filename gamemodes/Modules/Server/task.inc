ptask PlayerUpdate[999](playerid)
{
	PlayerData[playerid][pSeconds]++;

	foreach(new i : Player)
	{
		if(PlayerData[i][pHunger] <= 100)
		{
			PlayerTextDrawHide(i, HungerAlert[i]);
			PlayerTextDrawHide(i, Hunger[i]);
			PlayerTextDrawColor(i, Hunger[i], 16711815);
			PlayerTextDrawShow(i, Hunger[i]);
		}
		if(PlayerData[i][pHunger] <= 90)
		{
			PlayerTextDrawHide(i, HungerAlert[i]);
			PlayerTextDrawHide(i, Hunger[i]);
			PlayerTextDrawColor(i, Hunger[i], -65401);
			PlayerTextDrawShow(i, Hunger[i]);
		}
		if(PlayerData[i][pHunger] <= 80)
		{
			PlayerTextDrawHide(i, HungerAlert[i]);
			PlayerTextDrawHide(i, Hunger[i]);
			PlayerTextDrawColor(i, Hunger[i], -2686841);
			PlayerTextDrawShow(i, Hunger[i]);
		}
		if(PlayerData[i][pHunger] <= 70)
		{
			PlayerTextDrawHide(i, HungerAlert[i]);
			PlayerTextDrawHide(i, Hunger[i]);
			PlayerTextDrawColor(i, Hunger[i], -8388473);
			PlayerTextDrawShow(i, Hunger[i]);
		}
		if(PlayerData[i][pHunger] <= 60)
		{
			PlayerTextDrawHide(i, HungerAlert[i]);
			PlayerTextDrawHide(i, Hunger[i]);
			PlayerTextDrawColor(i, Hunger[i], -16777081);
			PlayerTextDrawShow(i, Hunger[i]);
		}
		if(PlayerData[i][pHunger] == 50)
		{
			PlayerTextDrawHide(i, Hunger[i]);
			PlayerTextDrawColor(i, Hunger[i], -1523963257);
			PlayerTextDrawShow(i, Hunger[i]);

			PlayerTextDrawHide(i, HungerAlert[i]);
			PlayerTextDrawShow(i, HungerAlert[i]);

			PlayerPlaySound(i, 1085,0.0,0.0,0.0);
			SendClientMessage(i, X11_WHITE, "{FF3333}ALERT: {FFFFFF}You are starving you need some food!");
		}
		if(PlayerData[i][pHunger] <= 40)
		{
			PlayerTextDrawHide(i, Hunger[i]);
			PlayerTextDrawColor(i, Hunger[i], -1962934137);
			PlayerTextDrawShow(i, Hunger[i]);

			PlayerTextDrawHide(i, HungerAlert[i]);
			PlayerTextDrawColor(i, HungerAlert[i], -3841);
			PlayerTextDrawShow(i, HungerAlert[i]);
		}
		//Thirst
		if(PlayerData[i][pThirst] <= 100)
		{
			PlayerTextDrawHide(i, ThirstAlert[i]);
			PlayerTextDrawHide(i, Thirst[i]);
			PlayerTextDrawColor(i, Thirst[i], 16711815);
			PlayerTextDrawShow(i, Thirst[i]);
		}
		if(PlayerData[i][pThirst] <= 90)
		{
			PlayerTextDrawHide(i, ThirstAlert[i]);
			PlayerTextDrawHide(i, Thirst[i]);
			PlayerTextDrawColor(i, Thirst[i], -65401);
			PlayerTextDrawShow(i, Thirst[i]);
		}
		if(PlayerData[i][pThirst] <= 80)
		{
			PlayerTextDrawHide(i, ThirstAlert[i]);
			PlayerTextDrawHide(i, Thirst[i]);
			PlayerTextDrawColor(i, Thirst[i], -2686841);
			PlayerTextDrawShow(i, Thirst[i]);
		}
		if(PlayerData[i][pThirst] <= 70)
		{
			PlayerTextDrawHide(i, ThirstAlert[i]);
			PlayerTextDrawHide(i, Thirst[i]);
			PlayerTextDrawColor(i, Thirst[i], -8388473);
			PlayerTextDrawShow(i, Thirst[i]);
		}
		if(PlayerData[i][pThirst] <= 60)
		{
			PlayerTextDrawHide(i, ThirstAlert[i]);
			PlayerTextDrawHide(i, Thirst[i]);
			PlayerTextDrawColor(i, Thirst[i], -16777081);
			PlayerTextDrawShow(i, Thirst[i]);
		}
		if(PlayerData[i][pThirst] == 50)
		{
			PlayerTextDrawHide(i, Thirst[i]);
			PlayerTextDrawColor(i, Thirst[i], -1523963257);
			PlayerTextDrawShow(i, Thirst[i]);

			PlayerTextDrawHide(i, ThirstAlert[i]);
			PlayerTextDrawColor(i, ThirstAlert[i], -3841);
			PlayerTextDrawShow(i, ThirstAlert[i]);

			PlayerPlaySound(i, 1085,0.0,0.0,0.0);
		}
		if(PlayerData[i][pThirst] <= 40)
		{
			PlayerTextDrawHide(i, Thirst[i]);
			PlayerTextDrawColor(i, Thirst[i], -1962934137);
			PlayerTextDrawShow(i, Thirst[i]);

			PlayerTextDrawHide(i, ThirstAlert[i]);
			PlayerTextDrawColor(i, ThirstAlert[i], -3841);
			PlayerTextDrawShow(i, ThirstAlert[i]);
		}
	}
	if(PlayerData[playerid][pSeconds] == 60)
	{
		new scoremath = ((PlayerData[playerid][pLevel])*5);

		PlayerData[playerid][pMinutes]++;
		PlayerData[playerid][pSeconds] = 0;

		switch(PlayerData[playerid][pMinutes])
		{
			case 60:
			{
				PlayerData[playerid][pHours] ++;
				PlayerData[playerid][pLevelUp] += 1;
				PlayerData[playerid][pMinutes] = 0;
				SaveData(playerid);

				if(PlayerData[playerid][pLevelUp] >= scoremath)
				{
					new mstr[128];
					PlayerData[playerid][pLevel] += 1;
					PlayerData[playerid][pHours] ++;
					SetPlayerScore(playerid, PlayerData[playerid][pLevel]);
					format(mstr,sizeof(mstr),"~g~Level Up!~n~~w~Sekarang anda level ~r~%d", PlayerData[playerid][pLevel]);
					GameTextForPlayer(playerid, mstr, 6000, 1);
				}					
			}		
		}
	}
}