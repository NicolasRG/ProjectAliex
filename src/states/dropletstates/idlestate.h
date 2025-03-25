#ifndef DROPLSET_IDLE_STATE_P_H
#define DROPLSET_IDLE_STATE_P_H

#include "dropletstate.h"
#include "runstate.h"
using namespace godot;
using namespace DropState;


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

    const int state_id = 1;
    //TODO MAKE SURE THAT ALL OLD STATES ARE EXPLICITLY DELETED WHEN VARIABLE ARE SETUP!!!!!!
    IdleState(DropletState* oldstate);

    IdleState();

    ~IdleState() override;

    IdleState* deep_copy() override;
    
    //im sure i can do this in an outside declartion with the same syntax
    double calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs) override;
    double calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs) override;

    bool is_dead()override;
    //TODO network impl
    dropletnetworkstate get_networking_data()override;

    // this method checks to see if the state of the droplet needs to be updated only based on its actions
    DropletState* get_new_state(Vector2 vel,  Input* input_handler,DropletAttrs dropletAttrs) override;
};
#endif