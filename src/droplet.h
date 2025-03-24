#ifndef DROPLET_NODE_P_H
#define DROPLET_NODE_P_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include "states/dropletstates/dropletstate.h"
#include "states/dropletstates/idlestate.h"
#include "states/dropletstates/runstate.h"
#include "states/dropletstates/util_operations.h"
#include "dropletattrs.h"
#include <string>
#include <map>
#include <memory>

using namespace DropState;

namespace godot {

class Droplet : public CharacterBody2D {
	GDCLASS(Droplet, CharacterBody2D)

	private:
		std::unique_ptr<DropletAttrs> dropletAttrs;

		NodePath animatedspritepath;

		double calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity);
		double calculate_jump_velocity(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity);

		// DropletState* map_state_name(int state_id){
		// 	return internal_map_state_idl( state_id);
		// }

		DropletState* state = new IdleState();

	protected:
		static void _bind_methods();

	public:
		Droplet();
		~Droplet();
		//needs to have a default so uhh idle event it is
		
	
		void _process(double delta) override;
		void _ready() override;

		//getters :: setters
		void set_animatedspritepath(NodePath _animatedspritepath);
		NodePath get_animatedspritepath();

		void set_max_run_speed(double p_max_run_speed);
		double get_max_run_speed();

		void set_run_acceleration(double p_run_acceleration);
		double get_run_acceleration();

		void set_base_run_speed(double p_base_run_speed);
		double get_base_run_speed();

		void set_gravity(double p_gravity);
		double get_gravity();

		void set_log_drag(double p_log_drag);
		double get_log_drag();

		// void set_state(int new_state_name);
		// int get_state();
	};
}


#endif