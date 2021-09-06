#define MAX_BUSSINES 1500
enum E_BUSSINES
{
	bID,
	bName,
	bOwner[MAX_PLAYER_NAME],
	bP[11],
	bType,
	Float:bPos[3],
	Float:bIPos[3],
	Float:bPointPos[3],
	Text3D:bLablePoint,	
	Text3D:bLable,
	bPickup,
	bPickPoint,
	bVisit,
	bCP,
	bPrice,
	bInt,
	bProduct,
	bMoney
};

new bData[MAX_BUSSINES][E_BUSSINES],
	Iterator:Bussines<MAX_BUSSINES>;