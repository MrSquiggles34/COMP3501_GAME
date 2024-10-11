#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/cylinder_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include "create_and_add_as_child.h"

namespace godot {

class Player : public Node3D {
    GDCLASS(Player, Node3D);

private:
    MeshInstance3D* body;

protected:
    static void _bind_methods();

public:
    Player();
    ~Player();

    void _enter_tree() override;
    void _ready() override;
};

}

#endif // PLAYER_H