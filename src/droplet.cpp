#include "droplet.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

#include <godot_cpp/classes/input_map.hpp>
#include <string>
#include <math.h>
// #include "./states/dropletstates/idlestate.h"
// #include "./states/dropletstates/runstate.h"


using namespace godot;
using namespace DropState;

void Droplet::_bind_methods() {

    ClassDB::bind_method(D_METHOD("get_max_run_speed"), &Droplet::get_max_run_speed);
	ClassDB::bind_method(D_METHOD("set_max_run_speed", "p_max_run_speed"), &Droplet::set_max_run_speed);
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "MAX_RUN_SPEED"), "set_max_run_speed", "get_max_run_speed");

    ClassDB::bind_method(D_METHOD("get_run_acceleration"), &Droplet::get_run_acceleration);
	ClassDB::bind_method(D_METHOD("set_run_acceleration", "p_run_acceleration"), &Droplet::set_run_acceleration);
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "RUN_ACCELERATION"), "set_run_acceleration", "get_run_acceleration");

     ClassDB::bind_method(D_METHOD("get_base_run_speed"), &Droplet::get_base_run_speed);
	ClassDB::bind_method(D_METHOD("set_base_run_speed", "p_base_run_speed"), &Droplet::set_base_run_speed);
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "BASE_RUN_SPEED"), "set_base_run_speed", "get_base_run_speed");

    ClassDB::bind_method(D_METHOD("get_gravity"), &Droplet::get_gravity);
	ClassDB::bind_method(D_METHOD("set_gravity", "p_gravity"), &Droplet::set_gravity); 
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "GRAVITY"), "set_gravity", "get_gravity");

    ClassDB::bind_method(D_METHOD("get_log_drag"), &Droplet::get_log_drag);
	ClassDB::bind_method(D_METHOD("set_log_drag", "p_log_drag"), &Droplet::set_log_drag); 
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "LOG_DRAG"), "set_log_drag", "get_log_drag");

    ClassDB::bind_method(D_METHOD("get_state"), &Droplet::get_state);
	ClassDB::bind_method(D_METHOD("set_state", "state_name"), &Droplet::set_state); 
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::INT, "State_Name"), "set_state", "get_state");

    ClassDB::bind_method(D_METHOD("get_animatedspritepath"), &Droplet::get_animatedspritepath);
	ClassDB::bind_method(D_METHOD("set_animatedspritepath", "_animatedSprite"), &Droplet::set_animatedspritepath);
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animatedspritepath"), "set_animatedspritepath", "get_animatedspritepath");
}

Droplet::Droplet() {
    DropletAttrs* attrs_ptr = new DropletAttrs();
    dropletAttrs =  std::unique_ptr<DropletAttrs>(attrs_ptr);
	// Initialize any variables here.
	dropletAttrs->time_passed = 0.0;
    UtilityFunctions::print("Creating My Object");

    Node* animatedsprite_or_null = get_node_or_null(animatedspritepath);
     if(animatedsprite_or_null == nullptr || animatedsprite_or_null == NULL){
        return;
    }
    
    AnimatedSprite2D* animatedsprite = (AnimatedSprite2D*)animatedsprite_or_null;

    if (animatedsprite == nullptr){
        UtilityFunctions::print("Creating DID NOT FIND A ANIMATED SPRITE PANIC");
    }else{
        UtilityFunctions::print("Creating FOUND SPRITE :",animatedsprite);
    }
     UtilityFunctions::print("Created My Object");
}

Droplet::~Droplet() {
    //remove vars related drop  
    UtilityFunctions::print("Deleting Droplet");
    this->dropletAttrs.reset(nullptr);
    delete state;
}

void Droplet::_process(double delta) {
    Vector2 vel = this->get_velocity();
    godot::Input* input_handler = Input::get_singleton();

    Node* animatedsprite_or_null = get_node_or_null(animatedspritepath);
     if(animatedsprite_or_null == nullptr || animatedsprite_or_null == NULL){
        return;
    }
    
    AnimatedSprite2D* animatedsprite = (AnimatedSprite2D*)animatedsprite_or_null;
    DropletAttrs dropAttrs = *this->dropletAttrs;
    //todo fix arg for direction
    if(input_handler->is_action_pressed("character_jump")){
        vel.y = this->state->calculate_jump_velocity(delta, false,input_handler, animatedsprite, vel.y, dropAttrs, is_on_floor());
    }
    
    
    if (input_handler->is_action_pressed("character_left")){
        //vel.x = calculate_run_veloicty(delta, true,input_handler, animatedsprite, vel.x);
        vel.x = this->state->calculate_run_veloicty(delta, true,input_handler, animatedsprite, vel.x, dropAttrs);
    }else if (input_handler->is_action_pressed("character_right")){
        //vel.x = calculate_run_veloicty(delta, false,input_handler, animatedsprite, vel.x);
        vel.x = this->state->calculate_run_veloicty(delta, false,input_handler, animatedsprite, vel.x, dropAttrs);
        
    }
    else{
        //if we want to disable the movement slide then rework to set value to zero when switching sides
        animatedsprite->stop();
        vel.x = 0;
    }

    //check if interacting with world


    //apply changes
    this->set_velocity(vel);

    this->move_and_slide();

    //update state
    DropletState* new_state = this->state->get_new_state(vel, input_handler, dropAttrs);

    if(new_state != nullptr){
        delete state;
        state = new_state;
    }
}
//internal methods


//getter and setters
void Droplet::_ready() {
    InputMap::get_singleton()->load_from_project_settings();
    UtilityFunctions::print("ready got called");
    UtilityFunctions::print(animatedspritepath);
    Node* animatedsprite_or_null = get_node_or_null(animatedspritepath);

    if (animatedsprite_or_null == nullptr){
        UtilityFunctions::print("READY DID NOT FIND A ANIMATED SPRITE PANIC EMOJI");
    }else{
        UtilityFunctions::print("READY FOUND SPRITE EMOJI");
        AnimatedSprite2D* animatedsprite = (AnimatedSprite2D*)animatedsprite_or_null;
        animatedsprite->stop();
    }
}

void Droplet::set_max_run_speed(double p_max_run_speed){
    dropletAttrs->MAX_RUN_SPEED = p_max_run_speed;
}

double Droplet::get_max_run_speed(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (dropletAttrs->MAX_RUN_SPEED);
};

void Droplet::set_run_acceleration(double p_run_acceleration){
    dropletAttrs->RUN_ACCELERATION = p_run_acceleration;
}

double Droplet::get_run_acceleration(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (dropletAttrs->RUN_ACCELERATION);
};

void Droplet::set_base_run_speed(double p_base_run_speed){
    dropletAttrs->BASE_RUN_SPEED = p_base_run_speed;
}

double Droplet::get_base_run_speed(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (dropletAttrs->BASE_RUN_SPEED);
};

double Droplet::get_gravity(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (dropletAttrs->GRAVITY);
};

void Droplet::set_gravity(double p_gravity){
    dropletAttrs->GRAVITY = p_gravity;
}

void Droplet::set_log_drag(double p_log_drag){
    dropletAttrs->LOG_DRAG = p_log_drag;
}

double Droplet::get_log_drag(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (dropletAttrs->LOG_DRAG);
};

void Droplet::set_state(int state_id){    
    //figure out how to handle this
    DropletState* new_state = map_state_name(state_id);
    delete this->state;
    state = new_state;

}

int Droplet::get_state(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return this->state->state_id;
};

void Droplet::set_animatedspritepath(NodePath p_animatedSprite){
    UtilityFunctions::print("SET ANIMATED SPRITE");
    UtilityFunctions::print(p_animatedSprite);
    animatedspritepath = p_animatedSprite;
}

NodePath Droplet::get_animatedspritepath(){
    UtilityFunctions::print("GET ANIMATED SPRITE");
    UtilityFunctions::print(animatedspritepath);
    return animatedspritepath;
}


