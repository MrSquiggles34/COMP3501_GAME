#include "custom_scene_3501.h"
#include "defs.h"

#include "create_and_add_as_child.h"

using namespace godot;

void CustomScene3501::_bind_methods() { }

CustomScene3501::CustomScene3501() : Node3D() {

	// Time for the scene 
	scene_time_passed = 0.0;
	is_paused = false;

	tabloid_count = 10;

	locations.append(Vector3(0.0, 1.0, -30.0)); // 1
	locations.append(Vector3(-50.0, 1.0, -40.0)); // 2
	locations.append(Vector3(85.0, 1.0, -60.0)); // 3
	locations.append(Vector3(-60.0, 1.0, -85.0)); // 4
	locations.append(Vector3(32.0, 1.0, -153.0)); // 5
	locations.append(Vector3(-54.0, 1.0, -183.0)); // 6
	locations.append(Vector3(54.0, 1.0, -205.0)); // 7
	locations.append(Vector3(-50.0, 1.0, -158.0)); // 8
	locations.append(Vector3(42.0, 1.0, -118.0)); // 9
	locations.append(Vector3(0.0, 1.0, -100.0)); // 10

	flavor_text.append("-ENTRY NUMBER 215-\nToday marks the beginning of something truly glorious.\nAll those years of slaving away, all my travels spent trying to bring this project into existence, will finally be worth it.\nTo think that I would be chosen to herald humanity's greatest accomplishment...\nAs if there was ever any other choice.\nMy precious boy... Mark my words, we shall see each other again very soon.\n...");
	flavor_text.append("-ENTRY NUMBER 32-\nI have finally arrived in Aurelia.\nThe rumors about this continent were true, finding it was no easy feat. This land has both technology and mother nature on its side.\nStill, my genius has prevailed as was to be expected. My submarine design worked perfectly in taking me all the way to shore. That being said...\nThe submarine is no longer operable. I can only hope that the people of Aurelia are as kind and accepting as I have heard.\n...");
	flavor_text.append("-ENTRY NUMBER 235-\nMy initial hypothesis has reached a dead end.\nThe lifeform does not respond to stimuli, and dies before completing embryo development.\nThis will not do. I have to find a way to speed things up. \nThis is MY research, and it WILL be completed within my lifetime.\nAn idea has come to mind.\nYou know what they say about desperate times...\n...");
	flavor_text.append("-ENTRY NUMBER 37-\nThere is no reason left to continue my research.\nThey let him die. My precious grandson did nothing to deserve the fate he met. But they certainly will.\nThey will all pay for what I have lost. I will make sure of it. Mark my words, history will remember this day.\n...");
	flavor_text.append("-ENTRY NUMBER 245-\nLife and work in Aurelia has been exciting, for good and for ill.\nThe self-governing nature of Aurelia means that my research goes undisturbed as long as I do my part for the community. No board of ethics to contend with either.\nThere's no price too high to pay for what I am attempting. I cannot allow it to weigh on my mind.\n");
	flavor_text.append("-ENTRY NUMBER 50-\nSince the dawn of civilization, man has been seeking intelligent life outside himself. Failing that, he seeks to create his own.\nIt must be me. It can only be me. There is no other reason I am still here when all else has been lost.\n... They called me crazy. Perhaps they were right.\nBut such is the life of a visionary. And I will stop at nothing to bring you back to me.\nThen they'll be sorry...\nOsiris, wait for me.");
	flavor_text.append("-ENTRY NUMBER 295-\nA whole year has passed since I first began my research.\nI have long since lost count of the failures. But with every failure comes significant progress for my next iteration.\n#$#&*#&@&#*$%@%!*#&$%@^\nHow blind they are, those fools sitting on their ivory towers.\nThey keep asking me to name the project.\nI know that they're desperate to claim authority over MY work.\nLet them call it whatever they want, I said.\nThey don't see its true purpose anyway. They won't until it's completed. But by then it will be too late.\nThen they will TRULY understand the depth of what they have taken away from me.");
	flavor_text.append("-ENTRY NUMBER 70-\nIdiots, all of them. They do not understand. How could they not understand my vision?\nIf my plans were to be realized, I would be playing on the same playing field as God himself.\nNot only do they rob me of my grandson by denying him care, they won't even let me fix what they've done! Calling it blasphemy.\nThey dare deny him his right to live!? His right to be reborn anew!?\nHe was perfect in every way, he could have become a greater mind than I. Yet his future was cut so short.\nNo. I will not allow this to happen.\nI will deliver justice.");
	flavor_text.append("-ENTRY NUMBER 80-\nI am leaving Aurelia. It's the only way to make more progress. I WILL find a way to proceed with my research, one way or another.\nOsiris… One day, I will return to Aurelia. As much as I loathe them, they are the only ones who can help me bring you back into this world.\nAfterwards...\nYou may choose to live as you see fit.");
	flavor_text.append("Page 10");
}

CustomScene3501::~CustomScene3501() {
	// Add your cleanup here.
}

void CustomScene3501::_enter_tree() {
	create_and_add_as_child<Map>(this, map, "Map", true);
	create_and_add_as_child<Robo>(this, robo, "Robot Arm", true);

	create_and_add_as_child<TerrainInstance>(this, terrain, "Terrain", true);

	// For each type of object, create as many as needed
	Node* CollectableGroup;
	create_and_add_as_child<Node>(this, CollectableGroup, "Collectable Items", true);
	create_and_add_as_child<TutorialItem>(CollectableGroup, tutorial_item, "Battery", true);
	tutorial_item->set_lore("A spent battery\nWhatever charge it once held has been used up.");
	
	// To work around the bug, I will no longer be putting the tabloids in groups
	// However, in order for the game to work, this still needs to be here
	// Disregard
	Node* TabloidGroup;
	create_and_add_as_child<Node>(this, TabloidGroup, "Tabloids", true);
	for (int i = 0; i < 1; i++) {
		Tabloid* new_tabloid;
		create_and_add_as_child<Tabloid>(TabloidGroup, new_tabloid, vformat("Page%d", i+1), true);
	}

	// REAL TABLOIDS
	for (int i = 0; i < tabloid_count; i++) {
		Tabloid* new_tabloid;
		create_and_add_as_child<Tabloid>(this, new_tabloid, vformat("Page%d", i), true);
	}

	create_and_add_as_child<Panoply>(this, panoply, "Panoply", true);

	// PARTICLE SYSTEMS
	create_particle_system(this, "Snow", "snow");
	create_particle_system(this, "Pebbles", "pebbles");

}

void CustomScene3501::_ready() {
	tutorial_item->set_global_position(Vector3(0.0, 1.0, -5.0));
	panoply->set_global_position(Vector3(9.0, 1.0, -134.0));

	// Add all tabloids to a list and place them in the world
	Tabloid* new_tabloid;
	for (int i=0; i<tabloid_count; i++){
		create_and_add_as_child<Tabloid>(this, new_tabloid, vformat("Page%d",i), true);
		new_tabloid->set_global_position(locations[i]);
		new_tabloid->set_lore(flavor_text[i]);
		tabloid_list.push_back(new_tabloid);
	}

	// Activate particles systems
	for (int index = 0; index < particle_systems.size(); index++) {
		GPUParticles3D* particle_system = particle_systems[index];

		// this should never be needed, but can't hurt to have. 
		if (particle_system == nullptr) continue;
		
		ShaderMaterial* shader_material = dynamic_cast<ShaderMaterial*>(*particle_system->get_draw_pass_mesh(0)->surface_get_material(0));
		switch (index) {
		case 0:
			particle_system->set_amount(10000);
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
	for (int i=0; i<tabloid_list.size(); i++){
		if (tabloid_list[i]->in_range(player_position)){
			tabloid_list[i]->set_visible(false);
			player->add_inventory(tabloid_list[i]);
			tabloid_list.remove_at(i);
		}
	}
	if(tutorial_item->is_visible()){
		if (tutorial_item->in_range(player_position)){
			tutorial_item->set_visible(false);
			player->add_inventory(tutorial_item);
		}
	}
	if(tutorial_item->is_visible()){
		if (panoply->in_range(player_position)){
			panoply->set_visible(false);
			player->add_inventory(tutorial_item);
		}
	}
}

void CustomScene3501::toggle_pause(bool paused) {
	is_paused = paused;
	// Propogate Pause 
	robo->toggle_pause(is_paused);
}

void CustomScene3501::create_particle_system(Node* parent, String node_name, String shader_name) {
	ParticleSystem* system = memnew(ParticleSystem(shader_name));
	create_and_add_as_child(parent, system, node_name, true, false);
	particle_systems.push_back(system);
}