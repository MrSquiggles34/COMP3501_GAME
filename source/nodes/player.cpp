#include "defs.h"
#include "player.h"
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Player::_bind_methods() {}

Player::Player() : Node3D(), body(nullptr) {}

Player::~Player() {}

void Player::_enter_tree() {
    if(DEBUG) UtilityFunctions::print("Enter Tree - Player."); 

    create_and_add_as_child<MeshInstance3D>(this, body, "Body", true);

    // YukiCylinder: He a Cylinder Dawg
    CylinderMesh* body_mesh = memnew(CylinderMesh);
    body_mesh->set_height(2.0f);
    body_mesh->set_top_radius(0.5f);
    body_mesh->set_bottom_radius(0.5f);

    // Material for YukiCylinder
    Ref<StandardMaterial3D> material = memnew(StandardMaterial3D);
    material->set_albedo(Color(0.0, 0.0, 1.0, 1)); // He's Blue
    body_mesh->surface_set_material(0, material);

    body->set_mesh(body_mesh);
}

void Player::_ready() {
    if(DEBUG) UtilityFunctions::print("Ready - Player."); 

    body->set_global_position(Vector3(0.0, 1.0, 0.0)); // Position the player
}