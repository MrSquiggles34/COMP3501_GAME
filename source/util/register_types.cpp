#include "register_types.h"

#include "quat_camera.h"
#include "custom_scene_3501.h"
#include "map.h"
#include "player.h"
#include "collidable_object.h"
#include "building.h"

#include "collectable_item_abstract.h"
#include "test_collectable.h"

#include "game.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

// gets called when godot loads our plugin
void initialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
    // register classes you made 
	ClassDB::register_class<QuatCamera>();
	ClassDB::register_class<CustomScene3501>();
	ClassDB::register_abstract_class<CollectableItemAbstract>();
	ClassDB::register_class<TestCollectable>();
	ClassDB::register_class<Game>();
	ClassDB::register_class<Map>();
	ClassDB::register_class<Player>();
	ClassDB::register_class<HUD>();
	ClassDB::register_class<ParticleSystem>();
	ClassDB::register_class<CustomMesh>();
	ClassDB::register_class<CollidableObject>();
	ClassDB::register_class<Building>();
}

// gets called when godot unloads our plugin
void uninitialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}


extern "C" {

/* --- Initialization ---
The important function is the this function called example_library_init. 
We first call a function in our bindings library that creates an initialization object. 
This object registers the initialization and termination functions of the GDExtension. 
Furthermore, it sets the level of initialization (core, servers, scene, editor, level).
*/
GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	// initialization object
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_example_module);
	init_obj.register_terminator(uninitialize_example_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}



}