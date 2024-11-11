
#include "custom_scene_3501.h"
#include "defs.h"

#include "create_and_add_as_child.h"

using namespace godot;

void CustomScene3501::_bind_methods() { }

CustomScene3501::CustomScene3501() : Node3D() {
	
	// Time for the scene 
	scene_time_passed = 0.0;
	is_paused = false;
	was_paused = false;

	test_obj_count = 1;
}

CustomScene3501::~CustomScene3501() {
	// Add your cleanup here.
}

void CustomScene3501::_enter_tree ( ){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501."); 

	create_and_add_as_child(this, main_camera, "QuatCamera", true);
    create_and_add_as_child<Map>(this, map, "Map", true);
	create_and_add_as_child<Player>(this, player, "Player", true); 

	// For each type of object, create as many as needed
	Node* obj_group;
	create_and_add_as_child<Node>(this, obj_group, "Test Group", true);
	for (int i=0; i<test_obj_count; i++){
		TestCollectable* test_obj;
		create_and_add_as_child(obj_group, test_obj, vformat("Test%d",i), true);
	}

}

void CustomScene3501::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501."); 

	// set the player's position (the camera) 
	main_camera->set_global_position(Vector3(0.0, 0.8, -12.0));
	main_camera->look_at(Vector3(0, 0, 0)); // there are some bugs with this function if the up vector is parallel to the look-at position; check the manual for a link to more info

	// now that we have set the camera's starting state, let's reinitialize its variables
	main_camera->_ready();

	// For each object type, add them to their lists
	Node* obj_group;
	create_and_add_as_child<Node>(this, obj_group, "Test Group", true);
	TestCollectable* test_obj;
	for (int i=0; i<test_obj_count; i++){
		create_and_add_as_child(obj_group, test_obj, vformat("Test%d",i), true);
		test_obj->set_global_position(Vector3(0.0, 1.0, -5.0));
		test_list.push_back(test_obj);
	}
}

void CustomScene3501::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	// Can put this back in a check if it's too slow but probably fine?
	main_camera->toggle_pause(is_paused);

	// For each object, check collision
	for (int i=0; i<test_list.size(); i++){
		if (test_list[i]->in_range(main_camera->get_global_position())){
			test_list[i]->set_visible(false);
			player->add_inventory(test_list[i]);
			test_list.remove_at(i);
		}
	}
}

void CustomScene3501::toggle_pause(bool paused) {
	is_paused = paused;
	if (DEBUG) UtilityFunctions::print(is_paused ? "Game Paused" : "Game Resumed");
}