#include "defs.h"
#include "building.h"
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Building::_bind_methods() {}

Building::Building() : Node3D() {}

Building::~Building() {}

void Building::_enter_tree() {
    if(DEBUG) UtilityFunctions::print("Enter Tree - Building."); 

    create_and_add_as_child(this, building, "Building", true);

    // DO NOT CHANGE: START

    // Set the Model
    building->set_model("res://models/sci-fi_building.glb");

    // Change the scale and position of the model
    building->get_model()->set_scale(Vector3(0.1, 0.1, 0.1));
    building->get_model()->set_global_position(Vector3(-0.3, -10.0, 0.0));

    // Set the Collision Shape
    Ref<BoxShape3D> box_shape = memnew(BoxShape3D);
    box_shape->set_size(Vector3(7.0, 20.0, 4.0));
    building->get_collision_shape()->set_shape(box_shape); 

    // DO NOT CHANGE: END
    
}

void Building::_ready() {
    if(DEBUG) UtilityFunctions::print("Ready - Building."); 

    this->set_global_position(Vector3(25.0, 10.0, 0.0)); // Position the object
}