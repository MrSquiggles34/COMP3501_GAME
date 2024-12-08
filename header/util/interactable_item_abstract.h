#ifndef INTERACTABLE_ITEM_ABSTRACT
#define INTERACTABLE_ITEM_ABSTRACT

#include <godot_cpp/classes/mesh_instance3d.hpp>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "create_and_add_as_child.h"
#include "defs.h"

// everything in gdextension is defined in this namespace
namespace godot {
	class InteractableItemAbstract : public MeshInstance3D {
		GDCLASS(InteractableItemAbstract, MeshInstance3D);

	private:
		Label* instructions;
	
	protected:
		static void _bind_methods();

	public:
		InteractableItemAbstract();

		void _enter_tree() override = 0;
		virtual void _ready() override = 0;

		void act();
		bool in_range (float radius, Vector3 player_pos);
		void set_instruct_visible (bool visible);
	};

}

#endif // EXAMPLE_ABSTRACT_CLASS