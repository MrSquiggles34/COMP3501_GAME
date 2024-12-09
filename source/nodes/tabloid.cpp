#include <godot_cpp/classes/sphere_mesh.hpp>

#include "tabloid.h"

#include "defs.h"

using namespace godot;

void Tabloid::_bind_methods() {}

Tabloid::Tabloid() : CollectableItemAbstract() {
    radius = 0.5;
}

void Tabloid::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - Tabloid.");

    //indicator = memnew(ParticleSystem("sparkle"));
    //create_and_add_as_child(this, indicator, "indicator", true);
}

void Tabloid::_ready() {
    if (DEBUG) UtilityFunctions::print("Ready - Tabloid.");

    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://models/9v_battery.glb");
    Node3D *model_instance = Object::cast_to<Node3D>(scene->instantiate());
    add_child(model_instance);

}

void Tabloid::_process(double delta) {
    //indicator->set_global_position(get_global_position());
}

bool Tabloid::in_range(Vector3 player_pos) {
    return CollectableItemAbstract::in_range(radius, player_pos);
}
