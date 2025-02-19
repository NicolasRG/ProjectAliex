#ifndef DROPLSET_STATE_P_H
#define DROPLSET_STATE_P_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <string>
using namespace godot;


//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??

class DropletState
{


public:
    //TODO MAKE SURE THAT ALL OLD STATES ARE EXPLICITLY DELETED WHEN VARIABLE ARE SETUP!!!!!!
    DropletState(){};
    const std::string StateName;
    virtual ~DropletState(){}

    //movement events
    virtual double calculate_run_veloicty(  ) = 0;    // "= 0" part makes this method pure virtual, and
    virtual double calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity) = 0;

    
};

#endif