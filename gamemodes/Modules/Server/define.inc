/* SETUP CONNECTION */

#define DATABASE_ADDRESS 	"localhost"
#define DATABASE_USERNAME 	"root" 
#define DATABASE_PASSWORD 	"" 
#define DATABASE_NAME 		"basicrp"

/* Other Define */

#define FUNC::%0(%1) forward %0(%1); public %0(%1)

#define COLOR_YELLOW 0xFFFF00FF

#define SendServerMessage(%1,%2) \
	SendClientMessageEx(%1, X11_LIGHTBLUE, "SERVER:{FFFFFF} "%2)

#define SendErrorMessage(%1,%2) \
	SendClientMessageEx(%1, X11_RED, "ERROR:{FFFFFF} "%2)

#define SendUsageMessage(%1,%2) \
	SendClientMessageEx(%1, X11_GRAY, "USAGE:{FFFFFF} "%2)

#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))	

#define MAX_CHARS 3 

#if !defined BCRYPT_HASH_LENGTH
	#define BCRYPT_HASH_LENGTH 250
#endif

#if !defined BCRYPT_COST
	#define BCRYPT_COST 12
#endif