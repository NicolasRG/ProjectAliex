//#include "runstate.h"
#include "idlestate.h"
using namespace godot;
using namespace DropState;

//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??

//TODO MAKE SURE THAT ALL OLD STATES ARE EXPLICITLY DELETED WHEN VARIABLE ARE SETUP!!!!!!
IdleState::IdleState(DropletState* oldstate){
    UtilityFunctions::print("Going into idle state");
};

IdleState::IdleState(){
    UtilityFunctions::print("Going into idle state || THIS SHOULD BE A BRAND NEW DROPLET BEING INSTIATED");
};

IdleState* IdleState::deep_copy(){
    return new IdleState();
}


IdleState::~IdleState(){
     UtilityFunctions::print("Idle state being deleted");
};

//im sure i can do this in an outside declartion with the same syntax
double IdleState::calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs){
    //if this thing has movement needs to set new state to moving and run the process to reurn base speed + any other modifier   
    animatedsprite->play();
    return dropletAttrs.BASE_RUN_SPEED;
};  
double IdleState::calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs){
    
    double vertical_velocity = -1 * dropletAttrs.GRAVITY;
    UtilityFunctions::print("Jump hoe");
    //todo bind to the jump 
    return vertical_velocity;
};

bool IdleState::is_dead(){
    //changes state to death and updates other stuff i guess
    return false;
};

//TODO network impl
dropletnetworkstate IdleState::get_networking_data(){
    return dropletnetworkstate{};
};

// this method checks to see if the state of the droplet needs to be updated only based on its actions
DropletState* IdleState::get_new_state(Vector2 vel,  Input* input_handler,DropletAttrs dropletAttrs){
    if(vel.y != 0){
        //TODO update this for jump
        return new IdleState(this);
        }else if(vel.x != 0){
        return new RunState(this);
    }

    return nullptr;
   
}