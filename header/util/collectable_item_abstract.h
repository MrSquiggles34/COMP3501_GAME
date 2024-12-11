#ifndef COLLECTABLE_ITEM_ABSTRACT
#define COLLECTABLE_ITEM_ABSTRACT

#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "create_and_add_as_child.h"
#include "defs.h"

// everything in gdextension is defined in this namespace
namespace godot {
	class CollectableItemAbstract : public Node3D {
		GDCLASS(CollectableItemAbstract, Node3D);

	private:
		bool in_inventory;
		String lore;
		Ref<Texture2D> icon;
	
	protected:
		static void _bind_methods();

	public:
		CollectableItemAbstract();

		virtual void _enter_tree() override = 0;
		virtual void _ready() override = 0;

		inline String get_lore() { return lore; }
		inline void set_lore(String i_lore) { lore = i_lore; }

		inline Ref<Texture2D> get_icon() { return icon; }
		inline void set_icon(Ref<Texture2D> i_icon) { icon = i_icon; }

		inline float get_inventory() { return in_inventory; }
		inline void set_inventory(bool in) { in_inventory = in; }

		bool in_range (float radius, Vector3 player_pos);
	};

}

#endif // EXAMPLE_ABSTRACT_CLASS