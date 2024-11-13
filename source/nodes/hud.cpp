#include "hud.h"
#include "create_and_add_as_child.h"

using namespace godot;

void HUD::_bind_methods() { }

HUD::HUD() : CanvasLayer() {}

HUD::~HUD() {}

void HUD::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - HUD.");

    create_and_add_as_child<Label>(this, pause_label, "PauseLabel", true);
}

void HUD::_ready() {
    // Setup HUD labels or other elements
    update_pause("PAUSED");
}

void HUD::update_pause(const String& pause_text) {
    if (pause_label) {
        pause_label->set_text(pause_text);
    }
}

