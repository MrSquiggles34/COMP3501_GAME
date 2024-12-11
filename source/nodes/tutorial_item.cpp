#include "tutorial_item.h"

#include "defs.h"

using namespace godot;

void TutorialItem::_bind_methods() {}

TutorialItem::TutorialItem() : CollectableItemAbstract() {
    radius = 0.5;
}

void TutorialItem::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - Tutorial Item.");

    Ref<Texture2D> icon_image = ResourceLoader::get_singleton()->load("res://textures/Battery.png");
    set_icon(icon_image);

    //indicator = memnew(ParticleSystem("sparkle"));
    //create_and_add_as_child(this, indicator, "indicator", true);
}

void TutorialItem::_ready() {
    if (DEBUG) UtilityFunctions::print("Ready - Tutorial Item.");

    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load("res://models/objects/battery/9v_battery.glb");
    Node3D *model_instance = Object::cast_to<Node3D>(scene->instantiate());
    model_instance->set_scale(Vector3(5, 5, 5));
    add_child(model_instance);

}

void TutorialItem::_process(double delta) {
    //indicator->set_global_position(get_global_position());
}

bool TutorialItem::in_range(Vector3 player_pos) {
    return CollectableItemAbstract::in_range(radius, player_pos);
}
