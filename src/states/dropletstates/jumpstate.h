#ifndef DROPLSET_JUMP_STATE_P_H
#define DROPLSET_JUMP_STATE_P_H

#include "dropletstate.h"
#include "idlestate.h"
#include "runstate.h"

using namespace godot;
using namespace DropState;

//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??

class JumpState: public virtual DropletState
{
public:
    const std::string stateName = "DROPLET_JUMP_STATE";

    const int state_id = 3;

    //TODO MAKE SURE THAT ALL OLD STATES ARE EXPLICITLY DELETED WHEN VARIABLE ARE SETUP!!!!!!
    JumpState(DropletState* oldstate){
        UtilityFunctions::print("Going into jump state");
    };

    // shoule never be used outside of mapping function
    JumpState(){
        UtilityFunctions::print("Going into jump state");
    };

    ~JumpState() override;

    JumpState* deep_copy() override;
    

    double calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity,DropletAttrs dropletAttrs) override;  
    double calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs, bool is_on_floor) override;
    Vector2 process_movement(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , Vector2 velocity, DropletAttrs dropletAttrs, bool is_on_floor) override;

    
    bool is_dead() override;
    dropletnetworkstate get_networking_data() override;
    DropletState* get_new_state(Vector2 vel,  Input* input_handler,DropletAttrs dropletAttrs) override;
};
#endif