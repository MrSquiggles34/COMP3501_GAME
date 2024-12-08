#ifndef ROBO_H
#define ROBO_H

// parent class
#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/input.hpp>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/transform3d.hpp>

#include "robo_part.h"
#include "robo_base.h"
#include "robo_joint.h"
#include "robo_head.h"

#include "robo.h"

#define NUM_PARTS_ROBO 10


// everything in gdextension is defined in this namespace
namespace godot {
	class Robo : public Node3D {
		// this macro sets up a few internal things
		GDCLASS(Robo, Node3D);

	private:
		RoboBase* base1;
		RoboBase* base2;
		RoboJoint* joint1;
		RoboJoint* joint2;

		RoboBase* arm1;
		RoboBase* arm2;
		RoboBase* arm3;

		RoboHead* head;

		RoboBase* pinch1;
		RoboBase* pinch2;

		bool is_paused;

	protected:
		// a static function that Godot will call to find out which methods can be called and which properties it exposes
		static void _bind_methods();


	public:
		Robo();
		~Robo();

		void _enter_tree() override;
		void _ready() override;
		void _process(double delta) override;

		// the return type represents whether it existed already; true if it is brand-new; false if it was retrieved from the SceneTree
		// search defines whether the scenetree should be checked for an instance
		template <class T>
		bool create_and_add_as_child(T*& pointer, String name, bool search = false);
		void toggle_pause(bool paused);

	};

}

#endif // ROBO_H