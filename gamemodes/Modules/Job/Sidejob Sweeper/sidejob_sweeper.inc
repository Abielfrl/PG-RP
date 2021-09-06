#define sweeperpoint1 1617.6018,-1874.0321,13.3828
#define sweeperpoint2 1558.2468,-1872.4255,12.9520
#define sweeperpoint3 1426.1484,-1872.4293,12.9494
#define sweeperpoint4 1391.4893,-1865.9651,12.9529
#define sweeperpoint5 1392.8096,-1735.7073,12.9547
#define sweeperpoint6 1530.6918,-1732.2140,12.9584
#define sweeperpoint7 1688.2314,-1739.3573,12.9551
#define sweeperpoint8 1689.6422,-1811.6910,12.9292
#define sweeperpoint9 1652.4985,-1871.5748,12.9529
#define sweeperpoint10 1621.5284,-1879.6655,12.9308

new SweeperVehicle[3]

CreateSweeperVehicle()
{
	SweeperVehicle[0] = AddStaticVehicleEx(171, 1611.2560,-1893.6320,13.5469, 0.0000,1,1, VEHICLE_RESPAWN);
	SweeperVehicle[1] = AddStaticVehicleEx(171, 1610.8843,-1890.8018,13.5469, 0.0000,1,1, VEHICLE_RESPAWN);
	SweeperVehicle[2] = AddStaticVehicleEx(171, 1611.2651,-1887.6864,13.5469, 0.0000,1,1, VEHICLE_RESPAWN);
}

IsASweeperVeh(carid)
{
	for(new v = 0; v < sizeof(SweeperVehicle); v++) {
	    if(carid == SweeperVehicle[v]) return 1;
	}
	return 0;
}