#include "custom_scene_3501.h"
#include "defs.h"

#include "create_and_add_as_child.h"

using namespace godot;

void CustomScene3501::_bind_methods() { }

CustomScene3501::CustomScene3501() : Node3D() {

	// Time for the scene 
	scene_time_passed = 0.0;
	is_paused = false;

	tabloid_count = 1;
}

CustomScene3501::~CustomScene3501() {
	// Add your cleanup here.
}

void CustomScene3501::_enter_tree() {
	if (DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501.");
	create_and_add_as_child<Map>(this, map, "Map", true);

	create_and_add_as_child<TerrainInstance>(this, terrain, "Terrain", true);

	// For each type of object, create as many as needed
	Node* CollectableGroup;
	create_and_add_as_child<Node>(this, CollectableGroup, "Collectable Items", true);
	create_and_add_as_child<TutorialItem>(CollectableGroup, tutorial_item, "Battery", true);
	tutorial_item->set_lore("A spent battery: Whatever charge it once held has been used up.");
	for (int i = 0; i < tabloid_count; i++) {
		Tabloid* new_tabloid;
		//create_and_add_as_child<Tabloid>(CollectableGroup, new_tabloid, vformat("Page%d", 1), true);
	}

	// PARTICLE SYSTEMS
	create_particle_system(this, "Snow", "snow");
	create_particle_system(this, "Pebbles", "pebbles");

}

void CustomScene3501::_ready() {
	if (DEBUG) UtilityFunctions::print("Ready - CustomScene3501.");

	// Add all collectables to a list
	Node* CollectableGroup;
	create_and_add_as_child<Node>(this, CollectableGroup, "Collectable Items", true);

	//tutorial_item->set_global_position(Vector3(0.0, 1.0, -5.0));
	Tabloid* new_tabloid;
	// for (int i=0; i<tabloid_count; i++){
	// 	create_and_add_as_child<Tabloid>(CollectableGroup, new_tabloid, vformat("Page%d",i), true);
	// 	new_tabloid->set_global_position(Vector3(0.0, 4.0, -5.0));
	// 	tabloid_list.push_back(new_tabloid);
	// }

	// Activate particles systems
	for (int index = 0; index < particle_systems.size(); index++) {
		GPUParticles3D* particle_system = particle_systems[index];

		// this should never be needed, but can't hurt to have. 
		if (particle_system == nullptr) continue;
		
		ShaderMaterial* shader_material = dynamic_cast<ShaderMaterial*>(*particle_system->get_draw_pass_mesh(0)->surface_get_material(0));
		switch (index) {
		case 0:
			particle_system->set_amount(20000);
			shader_material->set_shader_parameter("texture_image", ResourceLoader::get_singleton()->load("res://textures/flame4x4orig.png"));
			break;
		case 1:
			particle_system->set_amount(6);
			shader_material->set_shader_parameter("texture_image", ResourceLoader::get_singleton()->load("res://textures/pebble.png"));
			break;
		}

	}

	// Terrain height
	terrain->set_global_position(Vector3(4.0, 0.5, -16.0));
}

void CustomScene3501::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return;

	Input* _input = Input::get_singleton();
	Vector3 player_position = player->get_global_position();

	// Make the snow follow the player
	if (!particle_systems.is_empty()){
		if (particle_systems[0] != nullptr) {
			Vector3 offset(0.0f, 2.0f, 0.0f);
			particle_systems[0]->set_global_position(player_position + offset);
		}
		if (particle_systems[1] != nullptr && (_input->is_action_pressed("move_right") || _input->is_action_pressed("move_left") || _input->is_action_pressed("move_forward") || _input->is_action_pressed("move_backward"))){
			Vector3 offset(0.0f, -1.5f, 0.0f);
			particle_systems[1]->set_global_position(player_position + offset);
		}
		else if (particle_systems[1] != nullptr){
			Vector3 offset(0.0f, -5.95f, 0.0f);
			particle_systems[1]->set_global_position(player_position + offset);
		}
	}

	// For each collectable, check collision
	player_position.y -= 1;
	// for (int i=0; i<tabloid_list.size(); i++){
	// 	if (tabloid_list[i]->in_range(player_position)){
	// 		tabloid_list[i]->set_visible(false);
	// 		player->add_inventory(tabloid_list[i]);
	// 		tabloid_list.remove_at(i);
	// 	}
	// }
	if(tutorial_item->is_visible()){
		if (tutorial_item->in_range(player_position)){
			tutorial_item->set_visible(false);
			player->add_inventory(tutorial_item);
		}
	}
}

void CustomScene3501::toggle_pause(bool paused) {
	is_paused = paused;
	// Propogate Pause 
	map->toggle_pause(is_paused);

	if (DEBUG) UtilityFunctions::print(is_paused ? "Scene Paused" : "Scene Resumed");
}

void CustomScene3501::create_particle_system(Node* parent, String node_name, String shader_name) {
	ParticleSystem* system = memnew(ParticleSystem(shader_name));
	create_and_add_as_child(parent, system, node_name, true, false);
	particle_systems.push_back(system);
}