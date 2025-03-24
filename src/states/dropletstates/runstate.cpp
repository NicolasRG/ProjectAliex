#include "runstate.h"

using namespace godot;
using namespace DropState;

//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??

RunState* RunState::deep_copy(){
    return new RunState();
}

RunState::~RunState(){

};

double RunState::calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs){
    UtilityFunctions::print(velocity);
    const double DELTA_DILUTANT = .1;

    double direction;

    if(left){
        direction  = -1;
        animatedsprite->set_flip_h(false);
        UtilityFunctions::print("move left");
        animatedsprite->play();
    }else{
        direction = 1;
        UtilityFunctions::print("move right");
        //move this to state
        animatedsprite->set_flip_h(true);
        animatedsprite->play();
    }

    double calcualted_accelartion = (delta * DELTA_DILUTANT * dropletAttrs.RUN_ACCELERATION);
    double calculated_velocity = (dropletAttrs.BASE_RUN_SPEED  + calcualted_accelartion )* direction + velocity;
    //this should be some abs
    if(calculated_velocity > 0){
        calculated_velocity = fmin(calculated_velocity, dropletAttrs.MAX_RUN_SPEED);
    }else if(calculated_velocity < 0){
        calculated_velocity = fmax(calculated_velocity, (-1*dropletAttrs.MAX_RUN_SPEED));
    }
        //if the velocity is zero we dont care

    std::string message = std::to_string(calculated_velocity);
    UtilityFunctions::print(message.data()); 
    return calculated_velocity;
}

double RunState::calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs){  
    double vertical_velocity = -1 * dropletAttrs.GRAVITY;
    UtilityFunctions::print("Jump hoe");
    //todo bind to the jump 
    return vertical_velocity;
}

bool RunState::is_dead(){
    //changes state to death and updates other stuff i guess
    return false;
};

//TODO network impl
dropletnetworkstate RunState::get_networking_data(){
    return dropletnetworkstate{};
};

DropletState* RunState::get_new_state(Vector2 vel,  Input* input_handler,DropletAttrs dropletAttrs){
    //TODO make thie be enabled for jump
    if(vel.y != 0.00){
        //TODO update this for jump
        return new RunState(this);
    }else if(vel.x == 0.00){
        return new IdleState(this);
    }
    return nullptr;
}

