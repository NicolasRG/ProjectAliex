#ifndef DROPLSET_RUN_STATE_P_H
#define DROPLSET_RUN_STATE_P_H

#include "dropletstate.h"
#include "idlestate.h"

using namespace godot;
using namespace DropState;

//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??

class RunState: public virtual DropletState
{
public:
    const std::string stateName = "DROPLET_RUN_STATE";

    const int state_id = 2;

    //TODO MAKE SURE THAT ALL OLD STATES ARE EXPLICITLY DELETED WHEN VARIABLE ARE SETUP!!!!!!
    RunState(DropletState* oldstate){
        UtilityFunctions::print("Going into run state");
    };

    // shoule never be used outside of mapping function
    RunState(){
        UtilityFunctions::print("Going into run state");
    };

    ~RunState();

    RunState* deep_copy();
    

    double calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity,DropletAttrs dropletAttrs) ;  
    double calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs) ;
    bool is_dead() ;
    dropletnetworkstate get_networking_data() ;
    DropletState* get_new_state(Vector2 vel,  Input* input_handler,DropletAttrs dropletAttrs) ;
};
#endif