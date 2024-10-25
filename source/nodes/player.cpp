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

void Player::_ready() {
    if(DEBUG) UtilityFunctions::print("Ready - Player."); 

    this->set_global_position(Vector3(0.0, 1.0, 0.0)); // Position the player
}