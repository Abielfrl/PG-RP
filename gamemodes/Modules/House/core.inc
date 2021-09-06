#define MAX_HOUSE 1500

enum E_HOUSE
{
	hID,
	hOwner[MAX_PLAYER_NAME],
	hType,
	Float:hPos[3],
	Float:hIPos[3],
	Text3D:hText,
	hPickup,
	hInt,
	hPrice
};

new hData[MAX_HOUSE][E_HOUSE],
	Iterator:House<MAX_HOUSE>;