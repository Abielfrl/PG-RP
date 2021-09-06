#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_CTRL_BACK))
	{
		foreach(new bid : Bussines)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2]))
			{
				if(bData[bid][bIPos][0], bData[bid][bIPos][1], bData[bid][bIPos][2])
					return SendErrorMessage(playerid, "Bussines ini tidak mempunya Interior");

				PlayerData[playerid][pInHouse] = bid;
				SetPlayerPositionEx(playerid, bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2], 0.0);

				SetPlayerInterior(playerid, bData[bid][bInt]);
				SetPlayerVirtualWorld(playerid, bid);
				SetCameraBehindPlayer(playerid);				
			}
		}
		new bid = PlayerData[playerid][pInBussines];
		if(PlayerData[playerid][pInBussines] != -1 && IsPlayerInRangeOfPoint(playerid, 3.0, bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2]))
		{
			PlayerData[playerid][pInBussines] = -1;
			SetPlayerPositionEx(playerid, bData[bid][bPos][0], bData[bid][bPos][1], bData[bid][bPos][2], 0.0);

			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			SetCameraBehindPlayer(playerid);
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == BUSSINES_BUYMENU)
	{
		static
        bid = -1,
        price;

        if((bid = PlayerData[playerid][pInBussines]) != -1 && response)
        {
        	price = bData[bid][bP][listitem];

        	if(GetPlayerMoney(playerid) < price)
        		return SendErrorMessage(playerid, "Not enough money");

        	new Float:health;
        	GetPlayerHealth(playerid, health);
        	if(bData[bid][bType] == 1)
        	{
        		switch(listitem)
        		{
        			case 0:
        			{
        				GivePlayerMoneyEx(playerid, -price);
        				SetPlayerHealthEx(playerid, health+50);
        				PlayerData[playerid][pHunger] += 50;
        				SendNearbyMessage(playerid, 30.0, X11_PURPLE, "** %s has buy a Fried Chicken for %d", PlayerData[playerid][pName], price);
        				bData[bid][bProduct]--;
        				bData[bid][bMoney] += price;
        				Bussines_Save(bid);
        			}
        			case 1:
        			{
        				GivePlayerMoneyEx(playerid, -price);
        				SetPlayerHealthEx(playerid, health+30);
        				PlayerData[playerid][pHunger] += 30;
        				SendNearbyMessage(playerid, 30.0, X11_PURPLE, "** %s has buy a Chicken Nugget for %d", PlayerData[playerid][pName], price);
        				bData[bid][bProduct]--;
        				bData[bid][bMoney] += price;
        				Bussines_Save(bid);
        			}
         			case 2:
        			{
        				GivePlayerMoneyEx(playerid, -price);
        				PlayerData[playerid][pThirst] += 50;
        				SendNearbyMessage(playerid, 30.0, X11_PURPLE, "** %s has buy a Sprunk for %d", PlayerData[playerid][pName], price);
        				bData[bid][bProduct]--;
        				bData[bid][bMoney] += price;
        				Bussines_Save(bid);
        			}
        		}
        	}
        	else if(bData[bid][bType] == 2)
        	{
        		switch(listitem)
        		{
        			case 0:
        			{
        				GivePlayerMoneyEx(playerid, -price);
        				PlayerData[playerid][pBandage] += 1;
        				SendNearbyMessage(playerid, 30.0, X11_PURPLE, "** %s has buy a Bandage for %d", PlayerData[playerid][pName], price);
        				bData[bid][bProduct]--;
        				bData[bid][bMoney] += price;
        				Bussines_Save(bid); 
        			}
        			case 1:
        			{
        				GivePlayerMoneyEx(playerid, -price);
        				PlayerData[playerid][pCiggar] += 1;
        				SendNearbyMessage(playerid, 30.0, X11_PURPLE, "** %s has buy a Cigarette for %d", PlayerData[playerid][pName], price);
        				bData[bid][bProduct]--;
        				bData[bid][bMoney] += price;
        				Bussines_Save(bid); 
        			}
        			case 2:
        			{
        				GivePlayerMoneyEx(playerid, -price);
        				PlayerData[playerid][pSnack] += 1;
        				SendNearbyMessage(playerid, 30.0, X11_PURPLE, "** %s has buy a Snack for %d", PlayerData[playerid][pName], price);
        				bData[bid][bProduct]--;
        				bData[bid][bMoney] += price;
        				Bussines_Save(bid); 
        			}
        			case 3:
        			{
        				GivePlayerMoneyEx(playerid, -price);
        				PlayerData[playerid][pSprunk] += 1;
        				SendNearbyMessage(playerid, 30.0, X11_PURPLE, "** %s has buy a Sprunk for %d", PlayerData[playerid][pName], price);
        				bData[bid][bProduct]--;
        				bData[bid][bMoney] += price;
        				Bussines_Save(bid); 
        			}        			
        		}
        	}
        	else if(bData[bid][bType] == 3)
        	{
        		switch(listitem)
        		{
        			case 0:
        			{
         				GivePlayerMoneyEx(playerid, -price);
        				PlayerData[playerid][pPhone] += 1;
        				SendNearbyMessage(playerid, 30.0, X11_PURPLE, "** %s has buy a Phone for %d", PlayerData[playerid][pName], price);
        				bData[bid][bProduct]--;
        				bData[bid][bMoney] += price;
        				Bussines_Save(bid);        				
        			}
        			case 1:
        			{
        				GivePlayerMoneyEx(playerid, -price);
        				PlayerData[playerid][pPhoneCredit] += 1;
        				SendNearbyMessage(playerid, 30.0, X11_PURPLE, "** %s has buy a Phone Credit(1000) for %d", PlayerData[playerid][pName], price);
        				bData[bid][bProduct]--;
        				bData[bid][bMoney] += price;
        				Bussines_Save(bid);         				
        			}
        			case 3:
        			{
        				SendClientMessageEx(playerid, X11_LIGHTBLUE, "Item ini untuk sementara tidak ada");
        			}
        		}
        	}
        }
	}
	return 1;
}