#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/cylinder_mesh.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/capsule_shape3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/templates/vector.hpp> 
#include "create_and_add_as_child.h"
#include "collectable_item_abstract.h"

namespace godot {

class Player : public CharacterBody3D {
    GDCLASS(Player, CharacterBody3D);

private:
    MeshInstance3D* body_mesh;
    CollisionShape3D* collision_shape;
    Vector<CollectableItemAbstract*> inventory;

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