#ifndef ANTNODE_P_H
#define ANTNODE_P_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include "./states/dropletstates/dropletstate.h"

namespace godot {

class Droplet : public CharacterBody2D {
	GDCLASS(Droplet, CharacterBody2D)

	private:
		double time_passed;
		//TODD MOVE THIS TO SCENE BASED VAR/STATE 
		//MOVEMENT RELATED STATS
		double MAX_RUN_SPEED = 300.0;
		double RUN_ACCELERATION = 5;
		double BASE_RUN_SPEED = 100.0;  
		

		//JUMP RELATED STATS
		double GRAVITY = 100.0;
		double LOG_DRAG = 25.0;

		NodePath animatedspritepath;

		double calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity);
		double calculate_jump_velocity(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity);

	protected:
		static void _bind_methods();

	public:
		Droplet();
		~Droplet();
		 
		DropletState *state;
	
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
	};
}

#endif