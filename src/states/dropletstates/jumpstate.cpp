#include "dropletstate.h"
using namespace godot;
using namespace DropState;

//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??

class JumpState: public DropletState
{
public:
const std::string stateName = "DROPLET_JUMP_STATE";
    //TODO MAKE SURE THAT ALL OLD STATES ARE EXPLICITLY DELETED WHEN VARIABLE ARE SETUP!!!!!!
    JumpState(DropletState* oldstate){
        UtilityFunctions::print("Going into jump state");
    };

    ~JumpState(){};
    

    double calculate_run_veloicty(double delta, bool left, double velocity);    // "= 0" part makes this method pure virtual, and
    double calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity);
};

double JumpState::calculate_run_veloicty(double delta, bool left, double velocity){
    return 0.00;
}

double JumpState::calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity){
    return 0.00;
}