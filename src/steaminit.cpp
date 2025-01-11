#include "steam/steam_api.h"

int main()
{
	if ( SteamAPI_RestartAppIfNecessary(480) ) // Replace with your App ID
	{
		return 1;
	}

	if ( !SteamAPI_Init() )
	{
		printf( "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n" );
		return 1;
	}

	return 0;
}