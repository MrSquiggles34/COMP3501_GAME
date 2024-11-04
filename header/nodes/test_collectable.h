#ifndef TEST_COLLECTABLE_H
#define TEST_COLLECTABLE_H

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

// everything in gdextension is defined in this namespace
namespace godot {
	class TestCollectable : public CollectableItemAbstract {
		GDCLASS(TestCollectable, CollectableItemAbstract);

	private:
		bool in_inventory;
		float radius;
		MeshInstance3D* self;

	protected:
		static void _bind_methods();

	public:
		TestCollectable();

		void _enter_tree() override;
		void _ready() override;

		bool in_range(Vector3 player_pos);
	};

}

#endif