//file is meant to be independent of godot deps
#include "steaminit.h"
#include "steam/steam_api.h"


bool Networking::init_steam_connection_game()
{
	//TODO : Figure out how to properlly handle this steam_id
	if ( SteamAPI_RestartAppIfNecessary(1228304) ) // Replace with your App ID
	{
		printf("Restarting app?");
		return false;
	}

	if ( !SteamAPI_Init() )
	{
		printf( "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n" );
		return false;
	}

	return true;
}