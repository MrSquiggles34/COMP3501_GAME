#ifndef GAME_H
#define GAME_H

#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/transform3d.hpp>

#include <godot_cpp/templates/vector.hpp> 

#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

#include <godot_cpp/variant/rect2.hpp> // for viewport size
#include <godot_cpp/classes/canvas_item.hpp> // for viewport size
#include <godot_cpp/classes/control.hpp> // for the anchors preset
#include <godot_cpp/classes/color_rect.hpp>

#include "defs.h"
#include "custom_scene_3501.h"

namespace godot {

    class Game : public Node {
        GDCLASS(Game, Node);

    private:
        bool paused;

    protected:
        static void _bind_methods();  // Bind methods for GDExtension

    public:
        Game();
        ~Game();

        void _process(double delta) override;
        void load_scene(const String& scene_path);
        void _ready() override;
    };

}

#endif
