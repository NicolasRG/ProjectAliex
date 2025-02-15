#include "mastercontroller.h"
#include "../steam/steaminit.h"


controller::MasterController *controller::MasterController::GetInstance(){
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new controller::MasterController();
    }
    return pinstance_;
}

 void controller::MasterController::init(bool is_editor){
            if(is_editor){
                 is_connected_to_steam = false;
            }else{
                is_connected_to_steam= Networking::init_steam_connection_game();
            }
            return;
        }

bool controller::MasterController::get_is_connected_to_steam(){
    return is_connected_to_steam;
}

controller::MasterController* controller::MasterController::pinstance_{nullptr};
std::mutex controller::MasterController::mutex_;

