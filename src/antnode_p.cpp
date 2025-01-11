#include "antnode_p.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/node_path.hpp>
//Users/nicolas/Documents/ProjectAliex/godot-cpp/gen/include/godot_cpp/classes/input_map.hpp
#include <godot_cpp/classes/input_map.hpp>
#include <string>
using namespace godot;

void Antp::_bind_methods() {
    // ClassDB::bind_method(D_METHOD("get_animatedsprite"), &Antp::get_animatedsprite);
	// ClassDB::bind_method(D_METHOD("set_animatedsprite", "p_animatedSprite"), &Antp::set_animatedsprite);
    // //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    // ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "animatedsprite", PROPERTY_HINT_NODE_TYPE, "AnimatedSprite2D"), "set_animatedsprite", "get_animatedsprite");
    
    ClassDB::bind_method(D_METHOD("get_speed"), &Antp::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Antp::set_speed);
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "SPEED"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("get_animatedspritepath"), &Antp::get_animatedspritepath);
	ClassDB::bind_method(D_METHOD("set_animatedspritepath", "_animatedSprite"), &Antp::set_animatedspritepath);
    //so turns out if godot editor doesnt have the hints and types it gets real mad and crashes, game runs fine tho
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "animatedspritepath"), "set_animatedspritepath", "get_animatedspritepath");
}

Antp::Antp() {
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
        animatedsprite->stop();
    }
     UtilityFunctions::print("Created My Object");
}

Antp::~Antp() {
	// Add your cleanup here.
    UtilityFunctions::print("Deleting My Object");
}

void Antp::_process(double delta) {
    Vector2 vel = this->get_velocity();
    godot::Input* input_handler = Input::get_singleton();

    Node* animatedsprite_or_null = get_node_or_null(animatedspritepath);
     if(animatedsprite_or_null == nullptr || animatedsprite_or_null == NULL){
        return;
    }
    
    AnimatedSprite2D* animatedsprite = (AnimatedSprite2D*)animatedsprite_or_null;

    if(input_handler->is_action_pressed("character_up")){
        vel.y = SPEED * -1;
        UtilityFunctions::print("move up hoe");
        animatedsprite->play();
    }else if (input_handler->is_action_pressed("character_down")){
        vel.y = SPEED ;
        UtilityFunctions::print("movedown hoe");
        animatedsprite->play();
    }else{
        vel.y = 0;
    }
    
    if (input_handler->is_action_pressed("character_left")){
        vel.x = SPEED * -1 ;
        UtilityFunctions::print("move left hoe");
        animatedsprite->set_flip_h(true);
        animatedsprite->play();
    }else if (input_handler->is_action_pressed("character_right")){
        vel.x = SPEED ;
        UtilityFunctions::print("move right hoe");
        animatedsprite->set_flip_h(false);
        animatedsprite->play();
    }
    else{
        vel.x = 0;
    }

    this->set_velocity(vel);

    this->move_and_slide();
    
}

void Antp::_ready() {
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
// [[property]]
// void Antp::set_animatedsprite(AnimatedSprite2D* p_animatedSprite){
//     UtilityFunctions::print("attmpeting to assigning sprite", p_animatedSprite);
//     if (p_animatedSprite == nullptr){
//         UtilityFunctions::print("trying to assign null sprite go away");
//         return;
//     }

//     UtilityFunctions::print("Got a sprite, to reassign but not implemented", p_animatedSprite->get_name(), &animatedsprite);
//     animatedsprite = p_animatedSprite;
// }
// [[property]]
// AnimatedSprite2D* Antp::get_animatedsprite(){
//     AnimatedSprite2D* ptr = animatedsprite;
//     if (animatedsprite == nullptr){
//         UtilityFunctions::print("GET DID NOT FIND A ANIMATED SPRITE TO RETURN PANIC");
//         //ptr = new AnimatedSprite2D();
//    }else{
//         UtilityFunctions::print("GET FOUND SPRITE TO RETURN", animatedsprite);
//         UtilityFunctions::print( animatedsprite);
//         ptr = animatedsprite;
//    }
//     return ptr;
// }

void Antp::set_speed(double p_speed){
    SPEED = p_speed;
}

double Antp::get_speed(){
    //need to assign it to another var before referncing it as const funciton gets ma
    return (SPEED);
};

void Antp::set_animatedspritepath(NodePath p_animatedSprite){
    animatedspritepath = p_animatedSprite;
}

NodePath Antp::get_animatedspritepath(){
    return animatedspritepath;
}


