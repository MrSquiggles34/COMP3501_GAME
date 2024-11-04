#ifndef COLLECTABLE_ITEM_ABSTRACT
#define COLLECTABLE_ITEM_ABSTRACT

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

#include "create_and_add_as_child.h"
#include "collectable_item_abstract.h"

#include <godot_cpp/classes/mesh_instance3d.hpp> // for the debug statements
#include <godot_cpp/variant/utility_functions.hpp> // for the debug statements

// everything in gdextension is defined in this namespace
namespace godot {
	class CollectableItemAbstract : public MeshInstance3D {
		GDCLASS(CollectableItemAbstract, MeshInstance3D);

	private:
		bool in_inventory;
		MeshInstance3D* self;
	
	protected:
		static void _bind_methods();

	public:
		CollectableItemAbstract();

		virtual void _enter_tree() override = 0;
		virtual void _ready() override = 0;

		inline float get_inventory() { return in_inventory; }
		inline float set_inventory(bool in) { in_inventory = in; }

		bool in_range (float radius, Vector3 player_pos);
	};

}

#endif // EXAMPLE_ABSTRACT_CLASS