#include "hud.h"
#include "create_and_add_as_child.h"


using namespace godot;

void HUD::_bind_methods() { }

HUD::HUD() : CanvasLayer() {}

HUD::~HUD() {}

void HUD::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - HUD.");

    create_and_add_as_child<ColorRect>(this, pause_background, "PauseBackground", true);
    create_and_add_as_child<Label>(this, pause_label, "PauseLabel", true);


}

void HUD::_ready() {

    // PAUSE BACKGROUND
    pause_background->set_size(Vector2(1920, 1080));
    pause_background->set_position(Vector2(0, 0));
    pause_background->set_visible(false);
    pause_background->set_color(Color(0.0, 0.0, 0.0, 0.5));

    // PAUSE LABEL
    pause_label->set_text("PAUSE");
    pause_label->set_position(get_viewport()->get_visible_rect().size / 2 - pause_label->get_minimum_size() / 2);
    pause_label->set_visible(false);

}

void HUD::toggle_pause_HUD() {
    if (pause_label && pause_panel) {
        bool is_visible = pause_label->is_visible();

        // Toggle visibility for both the background and the label
        pause_label->set_visible(!is_visible);
        pause_background->set_visible(!is_visible);
    }
}