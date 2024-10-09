#include "custom_scene_3501.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp> 


using namespace godot;

void CustomScene3501::_bind_methods() { }

CustomScene3501::CustomScene3501() : Node3D() {
	
	// Time for the scene 
	scene_time_passed = 0.0;
}

CustomScene3501::~CustomScene3501() {
	// Add your cleanup here.
}

void CustomScene3501::_enter_tree ( ){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501."); 


	create_and_add_as_child(this, main_camera, "QuatCamera", true);

}

void CustomScene3501::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501."); 

	// set the player's position (the camera) 
	main_camera->set_global_position(Vector3(5.0, 5.0, 25.0f));
	main_camera->look_at(Vector3(0, 0, 0)); // there are some bugs with this function if the up vector is parallel to the look-at position; check the manual for a link to more info

	// now that we have set the camera's starting state, let's reinitialize its variables
	main_camera->_ready();
}

void CustomScene3501::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

}