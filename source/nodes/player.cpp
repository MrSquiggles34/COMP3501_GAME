#include "defs.h"
#include "player.h"
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Player::_bind_methods() {}

Player::Player() : CharacterBody3D() {
    is_paused = false;
}

Player::~Player() {}

void Player::_enter_tree() {
    if(DEBUG) UtilityFunctions::print("Enter Tree - Player."); 

    // The player has a child CylinderMesh
    create_and_add_as_child<MeshInstance3D>(this, body_mesh, "BodyMesh", true);

    // The player has a child CollisionShape3D
    create_and_add_as_child<CollisionShape3D>(this, collision_shape, "CollisionShape", true);   

    // The player has a child QuatCamera
    create_and_add_as_child(this, main_camera, "QuatCamera", true); 

    // Create a cylinder mesh for the player
    Ref<CylinderMesh> cylinder_mesh = memnew(CylinderMesh);
    cylinder_mesh->set_height(1.0f);
    cylinder_mesh->set_top_radius(0.5f);
    cylinder_mesh->set_bottom_radius(0.5f);

    // Set the collision shape of the player as a capsuleshape3d
    Ref<CapsuleShape3D> capsule_shape = memnew(CapsuleShape3D);
    capsule_shape->set_radius(0.5f);
    capsule_shape->set_height(2.0f);
    collision_shape->set_shape(capsule_shape);

    // Set the material of the player
    Ref<StandardMaterial3D> material = memnew(StandardMaterial3D);
    material->set_albedo(Color(0.0, 0.0, 1.0, 1)); // Blue
    cylinder_mesh->surface_set_material(0, material);

    // Set the mesh of the player
    body_mesh->set_mesh(cylinder_mesh);

    // Creating a quad for Screen SPace Effects
    create_and_add_as_child<MeshInstance3D>(main_camera, screen_quad_instance, "Screen Quad", true);

    // Setup the screen-space shader
    QuadMesh* quad_mesh = memnew(QuadMesh);
    quad_mesh->set_size(Vector2(2, 2)); // this will cover the whole screen
    quad_mesh->set_flip_faces(true);
    
    screen_space_shader_material = memnew(ShaderMaterial);
    Ref<Shader> shader = ResourceLoader::get_singleton()->load("shaders/no-effect.gdshader", "Shader"); 
    screen_space_shader_material->set_shader(shader);
    quad_mesh->surface_set_material(0, screen_space_shader_material);
    screen_quad_instance->set_mesh(quad_mesh);
    screen_quad_instance->set_extra_cull_margin(50.0f);
    
}

void Player::update_velocity(double delta) {
    Vector3 move_direction = Vector3(0.0, 0.0, 0.0); // Get movement direction

    Input* _input = Input::get_singleton();
	if(_input->is_action_pressed("move_right")){
		move_direction = main_camera->GetSide();
	}
	if(_input->is_action_pressed("move_left")){
		move_direction = -main_camera->GetSide();
	}
	if(_input->is_action_pressed("move_forward")){
		move_direction = main_camera->GetForward();
	}
	if(_input->is_action_pressed("move_backward")){
		move_direction = -main_camera->GetForward();
	}

    Vector3 target_velocity = move_direction * move_speed;  // Calculate target velocity

    // Set new velocity
    Vector3 new_velocity = get_velocity().move_toward(target_velocity, delta * acceleration);
    set_velocity(new_velocity);
}


void Player::_ready() {
    if(DEBUG) UtilityFunctions::print("Ready - Player."); 

    // set the player's position (the camera) 
	//main_camera->set_global_position(Vector3(0.0, 0.8, -12.0));
	main_camera->look_at(Vector3(0, 0, 0)); // there are some bugs with this function if the up vector is parallel to the look-at position; check the manual for a link to more info

	// now that we have set the camera's starting state, let's reinitialize its variables
	main_camera->_ready();

    this->set_global_position(Vector3(0.0, 1.0, 0.0)); // Position the player

    // Set collision layer and mask
    set_collision_mask(1); // For Player
    set_collision_layer(2); // For Environment/Walls/Etc.
}

void Player::_process(double delta) {
    if (Engine::get_singleton()->is_editor_hint()) return;
    
    update_velocity(delta); // Update the player's velocity
    move_and_slide(); // Move the player
}

String Player::printInventory(){
    String iString = "";
    for (int i=0; i<inventory.size(); i++){
        iString += inventory[i]->get_name();
        iString += "\n";
    }
    return iString;
}

void Player::toggle_pause(bool paused) {
    is_paused = paused;
    
    // Propogate Pause
    main_camera->toggle_pause(is_paused);

    if (DEBUG) UtilityFunctions::print(is_paused ? "Player Paused" : "Player Resumed");
}