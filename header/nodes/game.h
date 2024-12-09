#ifndef GAME_H
#define GAME_H

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
        bool picked_up_first_item;
        bool checked_first_item;

    protected:
        static void _bind_methods();  // Bind methods for GDExtension

    public:
        Game();
        ~Game();

        void _ready() override;
        void _process(double delta) override;
        void _enter_tree() override;

    };

}

#endif

// General Game object. Tracks:
// Pause
