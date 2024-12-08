#include <godot_cpp/classes/sphere_mesh.hpp>

#include "test_collectable.h"

#include "defs.h"

using namespace godot;

void TestCollectable::_bind_methods() {}

TestCollectable::TestCollectable() : CollectableItemAbstract() {
    radius = 0.5;
}

void TestCollectable::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - TestCollectable.");

    //indicator = memnew(ParticleSystem("sparkle"));
    //create_and_add_as_child(this, indicator, "indicator", true);
}

void TestCollectable::_ready() {
    if (DEBUG) UtilityFunctions::print("Ready - TestCollectable.");

    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://models/9v_battery.glb");
    Node3D *model_instance = Object::cast_to<Node3D>(scene->instantiate());
    add_child(model_instance);

}

void TestCollectable::_process(double delta) {
    //indicator->set_global_position(get_global_position());
}

bool TestCollectable::in_range(Vector3 player_pos) {
    return CollectableItemAbstract::in_range(radius, player_pos);
}
