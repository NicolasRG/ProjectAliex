#ifndef ANTNODE_P_H
#define ANTNODE_P_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/node_path.hpp>

namespace godot {

class Antp : public CharacterBody2D {
	GDCLASS(Antp, CharacterBody2D)

	private:
		double time_passed;
		double SPEED = 300.0;
		NodePath animatedspritepath;

	protected:
		static void _bind_methods();

	public:
		Antp();
		~Antp();
	
		void _process(double delta) override;
		void _ready() override;

		void set_animatedspritepath(NodePath _animatedspritepath);
		NodePath get_animatedspritepath();

		void set_speed(double p_speed);
		double get_speed();
	};
}

#endif