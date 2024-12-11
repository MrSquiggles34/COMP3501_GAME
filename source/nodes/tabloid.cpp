#include "tabloid.h"

#include "defs.h"

using namespace godot;

void Tabloid::_bind_methods() {}

Tabloid::Tabloid() : CollectableItemAbstract() {
    radius = 1.0;
}

void Tabloid::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - Tabloid.");

    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://models/objects/tabloid/low_poly_sci-fi_tablet.glb");
    Node3D *model_instance = Object::cast_to<Node3D>(scene->instantiate());
    model_instance->set_scale(Vector3(0.5, 0.5, 0.5));
    add_child(model_instance);

    Ref<Texture2D> icon_image = ResourceLoader::get_singleton()->load("res://textures/Tabloid.png");
    set_icon(icon_image);
}

void Tabloid::_ready() {
    if (DEBUG) UtilityFunctions::print("Ready - Tutorial Item.");
}

void Tabloid::_process(double delta) {
}

bool Tabloid::in_range(Vector3 player_pos) {
    return CollectableItemAbstract::in_range(radius, player_pos);
}
