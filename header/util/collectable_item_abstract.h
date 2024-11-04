#ifndef COLLECTABLE_ITEM_ABSTRACT
#define COLLECTABLE_ITEM_ABSTRACT

#include <godot_cpp/classes/mesh_instance3d.hpp>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/shader_material.hpp>

#include "create_and_add_as_child.h"
#include "defs.h"

// everything in gdextension is defined in this namespace
namespace godot {
	class CollectableItemAbstract : public MeshInstance3D {
		GDCLASS(CollectableItemAbstract, MeshInstance3D);

	private:
		bool in_inventory;
	
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