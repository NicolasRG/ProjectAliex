#ifndef DROPLSET_IDLE_STATE_P_H
#define DROPLSET_IDLE_STATE_P_H

#include "dropletstate.h"
using namespace godot;


//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??

class IdleState: public DropletState
{
public:
const std::string stateName = "DROPLET_IDLE_STATE";
    //TODO MAKE SURE THAT ALL OLD STATES ARE EXPLICITLY DELETED WHEN VARIABLE ARE SETUP!!!!!!
    IdleState(DropletState* oldstate){
        UtilityFunctions::print("Going into idle state");
    };

    IdleState(){
        UtilityFunctions::print("Going into idle state || THIS SHOULD BE A BRAND NEW DROPLET BEING INSTIATED");
    };


    ~IdleState(){};
    
    //im sure i can do this in an outside declartion with the same syntax
    double calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, 
        double RUN_ACCELERATION, double BASE_RUN_SPEED, double MAX_RUN_SPEED) override{
        return 0.00;
    };   // "= 0" part makes this method pure virtual, and
    double calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity)override{
        return 0.00;
    };
};
#endif