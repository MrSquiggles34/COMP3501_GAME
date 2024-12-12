#include "panoply.h"

#include "defs.h"

using namespace godot;

void Panoply::_bind_methods() {}

Panoply::Panoply() : CollectableItemAbstract() {
    radius = 0.5;
}

void Panoply::_enter_tree() {
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://models/objects/panoply/sci-fi_box.glb");
    Node3D *model_instance = Object::cast_to<Node3D>(scene->instantiate());
    model_instance->set_scale(Vector3(5, 5, 5));
    add_child(model_instance);
}

void TutorialItem::_ready() {

}

void TutorialItem::_process(double delta) {
}

bool TutorialItem::in_range(Vector3 player_pos) {
    return CollectableItemAbstract::in_range(radius, player_pos);
}
