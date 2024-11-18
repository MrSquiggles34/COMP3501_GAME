#ifndef HUD_H
#define HUD_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/color_rect.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "defs.h"

namespace godot {
    class HUD : public CanvasLayer {
        GDCLASS(HUD, CanvasLayer);

    private:
        Label* pause_label;
        Panel* pause_panel;
        ColorRect* pause_background;

    public:
        HUD();
        ~HUD();

        void _ready() override;
        void _enter_tree() override;

        void toggle_pause_HUD();

    protected:
        static void _bind_methods();
    };
}

#endif