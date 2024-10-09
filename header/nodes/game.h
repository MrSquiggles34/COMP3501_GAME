#ifndef GAME_H
#define GAME_H

#include <godot_cpp/classes/node.hpp>

#include "defs.h"
#include "custom_scene_3501.h"
#include "create_and_add_as_child.h"


namespace godot {

    class Game : public Node {
        GDCLASS(Game, Node);

    private:
        CustomScene3501* main_scene;
        bool is_paused;
        double global_time_passed;

    protected:
        static void _bind_methods();  // Bind methods for GDExtension


    public:
        Game();
        ~Game();


        void _ready() override;
        void _process(double delta) override;
        void _enter_tree() override;

        void _pause();
    
    };

}

#endif

// General Game object. Tracks:
// Pause
