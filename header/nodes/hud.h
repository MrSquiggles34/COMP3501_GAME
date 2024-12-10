#ifndef HUD_H
#define HUD_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/item_list.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/color_rect.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/texture_rect.hpp>
#include <godot_cpp/classes/texture2d.hpp>

#include "defs.h"
#include "player.h"
#include "collectable_item_abstract.h"

namespace godot {
    class HUD : public CanvasLayer {
        GDCLASS(HUD, CanvasLayer);

    private:
        Label* pause_label;
        ItemList* inventory;
        ColorRect* textBox;
        Label* dialog_label;
        Vector<String> dialog_list;
        int cur_dialog;
        TextureRect* title_screen;

    public:
        HUD();
        ~HUD();

        void _ready() override;
        void _enter_tree() override;

        void toggle_pause_HUD();
        void toggle_inventory(bool is_inv, Player* player);

        int nextDialog();
        void toggle_dialog(bool is_vis);

        void start_game();

    protected:
        static void _bind_methods();
    };
}

#endif