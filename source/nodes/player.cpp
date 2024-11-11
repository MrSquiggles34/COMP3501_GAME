#include "defs.h"
#include "player.h"
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Player::_bind_methods() {}

Player::Player() : CharacterBody3D() {}

Player::~Player() {}

void Player::_enter_tree() {
    if(DEBUG) UtilityFunctions::print("Enter Tree - Player."); 

    // The player has a child CylinderMesh
    create_and_add_as_child<MeshInstance3D>(this, body_mesh, "BodyMesh", true);

    // The player has a child CollisionShape3D
    create_and_add_as_child<CollisionShape3D>(this, collision_shape, "CollisionShape", true);    

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
}

Vector3 Player::get_input_vector() {
    // Get raw input vector
    Vector2 input_2d = Input::get_singleton()->get_vector("ui_left", "ui_right", "ui_up", "ui_down");
    return Vector3(input_2d.x, 0.0, input_2d.y); // Return the input vector
}

void Player::update_velocity(float delta) {
    Vector3 move_direction = get_input_vector();    // Get movement direction
    Vector3 target_velocity = move_direction * move_speed;  // Calculate target velocity

    // Set new velocity
    Vector3 new_velocity = get_velocity().move_toward(target_velocity, acceleration * delta);
    set_velocity(new_velocity);
}


void Player::_ready() {
    if(DEBUG) UtilityFunctions::print("Ready - Player."); 

    this->set_global_position(Vector3(0.0, 1.0, 0.0)); // Position the player

    // Set collision layer and mask
    set_collision_mask(1); // For Player
    set_collision_layer(2); // For Environment/Walls/Etc.
}

void Player::_process(double delta) {
    //if(DEBUG) UtilityFunctions::print("Process - Player."); 

    update_velocity(delta); // Update the player's velocity
    move_and_slide(); // Move the player

    // Check for collisions after movement
    // Requires all objects to have collision shapes
}

String Player::printInventory(){
    String iString = "";
    for (int i=0; i<inventory.size(); i++){
        iString += inventory[i]->get_name();
        iString += "\n";
    }
    return iString;
}