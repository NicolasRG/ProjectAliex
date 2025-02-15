/**
 * This Logic Layer will hold the parent state of the game. 
 * Properties meant for this to hanlde
 * - high level steam info
 *    - player name, steam avatar
 * - save states
 * - parent confgurations 
 *     - load controller specs?
 *     - language details
 *     - any global preferences
 * - what game app state : MAIN_MENU, LOBBY, IN-MULTI-GAME, IN-SINGLE-GAME 
 */
#include "maingame.h"

#include <godot_cpp/classes/node.hpp>
#include "controllers/mastercontroller.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <string>

using namespace godot;
using namespace controller;


void MainGame::_bind_methods(){
}

MainGame::MainGame(){
    UtilityFunctions::print("Instatiating MainGame");
}

MainGame::~MainGame() {
	// Add your cleanup here.
    UtilityFunctions::print("Shutting Down MainGame");
}

void MainGame::_ready(){
  bool isConnectedToSteam = MasterController::GetInstance()->GetInstance()->get_is_connected_to_steam();
 
  if(!isConnectedToSteam){
    UtilityFunctions::print("Not connected to steam , trying to connect");
    MasterController::GetInstance()->init(inEditor);
  }
  //TODO: read from config
}

