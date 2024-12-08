#include "hud.h"
#include "create_and_add_as_child.h"
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

void HUD::_bind_methods() { }

HUD::HUD() : CanvasLayer() {}

HUD::~HUD() {}

void HUD::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - HUD.");
    create_and_add_as_child<Label>(this, pause_label, "PauseLabel", true);
    create_and_add_as_child<ItemList>(this, inventory, "Inventory", true);
    create_and_add_as_child<Label>(this, inv_label, "InvLabel", true);
}

void HUD::_ready() {

    Vector2 screen_size = get_viewport()->get_visible_rect().size;
    screen_size = screen_size / 2;

    // PAUSE LABEL
    pause_label->set_text("PAUSE");
    pause_label->set("theme_override_colors/font_color", Color(1,1,1,1));
    pause_label->set("theme_override_constants/outline_size", 5);
    pause_label->set("theme_override_font_sizes/font_size", 50);
    pause_label->set("theme_override_colors/font_outline_color", Color(0,0,0,1));
    pause_label->set_position(screen_size - pause_label->get_minimum_size() / 2);
    pause_label->set_visible(false);

    // INVENTORY LABEL
    inv_label->set_text("INVENTORY");
    screen_size.x -= inv_label->get_minimum_size().x / 2;
    screen_size.y = inv_label->get_minimum_size().y;
    inv_label->set_position(screen_size);
    inv_label->set_visible(false);

    // INVENTORY
    inventory->set_size(get_viewport()->get_visible_rect().size);
    inventory->set_max_columns(5);
    inventory->set_fixed_icon_size(Vector2i(25, 25));
    inventory->set("theme_override_font_sizes/font_size", 20);
    inventory->set_visible(false);

}

void HUD::toggle_pause_HUD() {
    if (pause_label) {
        bool is_visible = pause_label->is_visible();
        pause_label->set_visible(!is_visible);
    }
}

void HUD::toggle_inventory(bool is_inv, Player* player) {
    if (!is_inv) {
        inventory->clear();
        Vector<CollectableItemAbstract*> player_inv = player->get_inventory();
        for (int i=0; i<player_inv.size(); i++){
            int index = inventory->add_item(player_inv[i]->get_name(), player_inv[i]->get_icon());
            UtilityFunctions::print(player_inv[i]->get_name());
            inventory->set_item_tooltip(index, player_inv[i]->get_lore());
        }
    }
    inventory->set_visible(is_inv);
    inv_label->set_visible(is_inv);
}
