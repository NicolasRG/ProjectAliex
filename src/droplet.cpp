#include "droplet.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/node_path.hpp>
//Users/nicolas/Documents/ProjectAliex/godot-cpp/gen/include/godot_cpp/classes/input_map.hpp
#include <godot_cpp/classes/input_map.hpp>
#include <string>
#include <math.h>
using namespace godot;

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

    ClassDB::bind_method(D_METHOD("get_animatedspritepath"), &Droplet::get_animatedspritepath);
	ClassDB::bind_method(D_METHOD("set_animatedspritepath", "_animatedSprite"), &Droplet::set_animatedspritepath);
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animatedspritepath"), "set_animatedspritepath", "get_animatedspritepath");
}

Droplet::Droplet() {
	// Initialize any variables here.
	time_passed = 0.0;
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
	// Add your cleanup here.
    UtilityFunctions::print("Deleting My Object");
}

void Droplet::_process(double delta) {
    Vector2 vel = this->get_velocity();
    godot::Input* input_handler = Input::get_singleton();

    Node* animatedsprite_or_null = get_node_or_null(animatedspritepath);
     if(animatedsprite_or_null == nullptr || animatedsprite_or_null == NULL){
        return;
    }
    
    AnimatedSprite2D* animatedsprite = (AnimatedSprite2D*)animatedsprite_or_null;

    if(input_handler->is_action_just_pressed("character_jump") && is_on_floor()){
        vel.y = -1 * GRAVITY;
        UtilityFunctions::print("Jump hoe");
        animatedsprite->play();
    }else if(!is_on_floor()){
        vel.y += GRAVITY * delta + LOG_DRAG;
    }
    
    if (input_handler->is_action_pressed("character_left")){
        vel.x = calculate_run_veloicty(delta, true, vel.x);
        UtilityFunctions::print("move left hoe");
        animatedsprite->set_flip_h(false);
        animatedsprite->play();
    }else if (input_handler->is_action_pressed("character_right")){
        vel.x = calculate_run_veloicty(delta, false, vel.x);
        UtilityFunctions::print("move right hoe");
        animatedsprite->set_flip_h(true);
        animatedsprite->play();
    }
    else{
        //if we want to disable the movement slide then rework to set value to zero when switching sides
        animatedsprite->stop();
        vel.x = 0;
    }

    this->set_velocity(vel);

    this->move_and_slide();
    
}
//internal methods

double Droplet::calculate_run_veloicty(double delta, bool left, double velocity){
    UtilityFunctions::print(velocity);
    const double DELTA_DILUTANT = .1;

    double direction;

    if(left){
        direction  = -1;
    }else{
        direction = 1;
    }

    double calcualted_accelartion = (delta * DELTA_DILUTANT * RUN_ACCELERATION);
    double calculated_velocity = (BASE_RUN_SPEED  + calcualted_accelartion )* direction + velocity;
    //this should be some abs
    if(calculated_velocity > 0){
        calculated_velocity = fmin(calculated_velocity, MAX_RUN_SPEED);
    }else if(calculated_velocity < 0){
        calculated_velocity = fmax(calculated_velocity, (-1*MAX_RUN_SPEED));
    }
        //if the velocity is zerio we dont care

    std::string message = std::to_string(calculated_velocity);
    UtilityFunctions::print(message.data()); 
    return calculated_velocity;

}

//getter and setters
void Droplet::_ready() {
    InputMap::get_singleton()->load_from_project_settings();
    UtilityFunctions::print("ready got called");
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
    MAX_RUN_SPEED = p_max_run_speed;
}

double Droplet::get_max_run_speed(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (MAX_RUN_SPEED);
};

void Droplet::set_run_acceleration(double p_run_acceleration){
    RUN_ACCELERATION = p_run_acceleration;
}

double Droplet::get_run_acceleration(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (RUN_ACCELERATION);
};

void Droplet::set_base_run_speed(double p_base_run_speed){
    BASE_RUN_SPEED = p_base_run_speed;
}

double Droplet::get_base_run_speed(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (BASE_RUN_SPEED);
};

double Droplet::get_gravity(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (GRAVITY);
};

void Droplet::set_gravity(double p_gravity){
    GRAVITY = p_gravity;
}

void Droplet::set_log_drag(double p_log_drag){
    LOG_DRAG = p_log_drag;
}

double Droplet::get_log_drag(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (LOG_DRAG);
};

void Droplet::set_animatedspritepath(NodePath p_animatedSprite){
    animatedspritepath = p_animatedSprite;
}

NodePath Droplet::get_animatedspritepath(){
    return animatedspritepath;
}


