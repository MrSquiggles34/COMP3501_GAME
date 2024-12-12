#include "tabloid.h"

#include "defs.h"

using namespace godot;

void Tabloid::_bind_methods() {}

Tabloid::Tabloid() : CollectableItemAbstract() {
    radius = 1.0;
}

void Tabloid::_enter_tree() {
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://models/objects/tabloid/low_poly_sci-fi_tablet.glb");
    Node3D *model_instance = Object::cast_to<Node3D>(scene->instantiate());
    model_instance->set_scale(Vector3(0.8, 0.8, 0.8));
    add_child(model_instance);

    Ref<Texture2D> icon_image = ResourceLoader::get_singleton()->load("res://textures/Tabloid.png");
    set_icon(icon_image);
    set_global_transform(Transform3D(Quaternion(Vector3(1, 0, 0), Math::deg_to_rad(45.0f))));
}

void Tabloid::_ready() {
}

void Tabloid::_process(double delta) {
}

bool Tabloid::in_range(Vector3 player_pos) {
    return CollectableItemAbstract::in_range(radius, player_pos);
}
