#include "jumpstate.h"

using namespace godot;
using namespace DropState;


//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??
JumpState* JumpState::deep_copy(){
    return new JumpState();
}


JumpState::~JumpState(){
     UtilityFunctions::print("Jump state being deleted");
};

//initiating a jumpe keeps the same velocity of the jump you initiate it with
double JumpState::calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs){
     //UtilityFunctions::print(velocity);

    double direction;

    if(left){
        direction  = -1;
        animatedsprite->set_flip_h(false);
        //UtilityFunctions::print("move left");
        animatedsprite->play();
    }else{
        direction = 1;
        //UtilityFunctions::print("move right");
        //move this to state
        animatedsprite->set_flip_h(true);
        animatedsprite->play();
    }

    //this should be some abs
    if(velocity > 0){
        velocity = fmin(velocity, dropletAttrs.MAX_RUN_SPEED);
    }else if(velocity < 0){
    velocity = fmax(velocity, (-1*dropletAttrs.MAX_RUN_SPEED));
    }
        //if the velocity is zero we dont care

    // std::string message = std::to_string(calculated_velocity);
    // UtilityFunctions::print(message.data()); 
    return velocity;
   
};  
double JumpState::calculate_jump_velocity(double delta, bool left, Input* input_handler, 
    AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs, bool is_on_floor){
    
    double vertical_velocity = velocity;
    if(input_handler->is_action_just_pressed("character_jump") && is_on_floor){
        vertical_velocity = -1 * dropletAttrs.GRAVITY;
        UtilityFunctions::print("Jump hoe");
        animatedsprite->play();
    }else if(!is_on_floor){
        //FIXME log drag is fucking with this it should always pull down x
        vertical_velocity += dropletAttrs.GRAVITY * delta + dropletAttrs.LOG_DRAG;
        UtilityFunctions::print(vertical_velocity);
    }
    return vertical_velocity;
};

bool JumpState::is_dead(){
    //changes state to death and updates other stuff i guess
    return false;
};

//TODO network impl
dropletnetworkstate JumpState::get_networking_data(){
    return dropletnetworkstate{};
};

// this method checks to see if the state of the droplet needs to be updated only based on its actions
DropletState* JumpState::get_new_state(Vector2 vel,  Input* input_handler,DropletAttrs dropletAttrs){
    if(vel.y != 0){
        //TODO update this for jump
        return nullptr;
    }else if(vel.x != 0){
        return new RunState(this);
    }else{
        return new IdleState(this);
    }

    
   
}