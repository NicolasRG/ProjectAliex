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

#include "dropletnetworkstate.h"
#include "dropletattrs.h"

using namespace godot;

//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??

namespace DropState {class DropletState //: public Object
{
    //GDCLASS(DropletState, Object);

    // protected:
    //     static void _bind_methods(){}

public:
    //TODO MAKE SURE THAT ALL OLD STATES ARE EXPLICITLY DELETED WHEN VARIABLE ARE SETUP!!!!!!
    std::string StateName =  "";
    // std::shared_ptr<DropletState> next_state = new std::shared_ptr<>;
    int state_id = -1;

    //state initing events
    virtual DropletState* deep_copy() = 0;

    //movement events
    virtual double calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs) = 0;    // "= 0" part makes this method pure virtual, and
    virtual double calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, DropletAttrs dropletAttrs) = 0;
    virtual bool is_dead() = 0;
    virtual dropletnetworkstate get_networking_data() =0;
    //virtual DropletState* get_new_state(Vector2 vel,  Input* input_handler,DropletAttrs dropletAttrs)=0;
};
}

#endif