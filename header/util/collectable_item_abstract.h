#ifndef COLLECTABLE_ITEM_ABSTRACT
#define COLLECTABLE_ITEM_ABSTRACT

#include <godot_cpp/classes/mesh_instance3d.hpp> // for the debug statements
#include <godot_cpp/variant/utility_functions.hpp> // for the debug statements

// everything in gdextension is defined in this namespace
namespace godot {
	class CollectableItemAbstract : public MeshInstance3D {
		GDCLASS(CollectableItemAbstract, MeshInstance3D);

	protected:
		static void _bind_methods();
		bool in_inventory;

	public:
		CollectableItemAbstract();

		virtual void _enter_tree() override = 0;
		virtual void _ready() override = 0;

		inline float get_some_shared_attribute() { return in_inventory; }
		inline float set_some_shared_attribute(bool in) { in_inventory = in; }
	};

}

#endif // EXAMPLE_ABSTRACT_CLASS