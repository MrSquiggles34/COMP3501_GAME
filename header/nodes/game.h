#ifndef GAME_H
#define GAME_H

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "custom_scene_3501.h"

#include "player.h"
#include "custom_mesh.h"
#include "hud.h"

namespace godot {

    class Game : public Node {
        GDCLASS(Game, Node);

    private:
        CustomScene3501* main_scene;
        int state;
        bool is_paused;
        double global_time_passed;
        Player* player;
	    HUD* hud;
        int progress_check;
        bool picked_up_first_item;
        bool checked_first_item;

        Vector<int> read_pages;

        Vector<String> page_1;
        Vector<String> second_page;
        Vector<String> page_4;
        Vector<String> page_5;
        Vector<String> page_6;
        Vector<String> page_7;

    protected:
        static void _bind_methods();  // Bind methods for GDExtension

    public:
        Game();
        ~Game();

        void _ready() override;
        void _input(const Ref<InputEvent>&);
        void _process(double delta) override;
        void _enter_tree() override;

    };

}

#endif

// General Game object. Tracks:
// Pause
