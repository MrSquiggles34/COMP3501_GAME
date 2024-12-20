#ifndef ROBO_PART_H
#define ROBO_PART_H

#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/cylinder_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>

#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/transform3d.hpp>

#include <godot_cpp/variant/utility_functions.hpp> // for the debug statements

#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/torus_mesh.hpp>

#include "custom_mesh.h"

#define DEBUG true
#define LINEUP_SPACE_ROBO 0.0f

namespace godot {
	class RoboPart : public CustomMesh {
		// this macro sets up a few internal things
		GDCLASS(RoboPart, CustomMesh);

	private:
		double time_passed;

	protected:
		static void _bind_methods();

		// the position relative to the transformation hierarchy parent (*T*orso)
		Vector3 local_position;

		// these two are to set up the orbit matrix (t*O*rso)
		Vector3 joint_position;
		Quaternion orbit_rotation;

		// the rotation relative to the transformation hierarchy parent (to*R*so)
		Quaternion local_rotation;

		Vector3 scale; // (x-scale, y-scale, z-scale) (tor*S*o)

		// parent for our transformation hierarchy
		RoboPart* parent;

	public:
		RoboPart();
		~RoboPart();

		void _enter_tree() override;
		void _ready() override;

		// for our transformation hierarchy, since we will not be using the built-in one. 
		
		void set_parent(RoboPart* parent);
		RoboPart* get_parent();

		// These functions are specifically for hierarchical transformations 
		Transform3D get_transformation_matrix();
		Transform3D get_transformation_matrix_without_scaling();

		// Getters and Setters for the primary variables, if you want / need them
		Vector3 get_local_position();
		void set_local_position(Vector3);
		Quaternion get_local_rotation();
		void set_local_rotation(Quaternion);
		Vector3 get_scale();
		void set_scale(Vector3);
		Quaternion get_orbit_rotation();
		void set_orbit_rotation(Quaternion);
		Vector3 get_joint_position();
		void set_joint_position(Vector3);

		float get_time_passed() const { return time_passed; }
		void set_time_passed(float value) { time_passed = value; }
	};

}

#endif // ROBO_PART_H