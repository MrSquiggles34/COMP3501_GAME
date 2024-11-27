#ifndef COLLIDABLE_OBJECT_H
#define COLLIDABLE_OBJECT_H

// Meshes
#include <godot_cpp/classes/capsule_mesh.hpp>
#include <godot_cpp/classes/cylinder_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
// Collision Shapes
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/capsule_shape3d.hpp>
#include <godot_cpp/classes/cylinder_shape3d.hpp>
#include <godot_cpp/classes/box_shape3d.hpp>
// Misc
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/templates/vector.hpp> 
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include "create_and_add_as_child.h"

namespace godot {

class CollidableObject : public StaticBody3D {
    GDCLASS(CollidableObject, StaticBody3D);

private:
    Node3D* model;
    CollisionShape3D* collision_shape;

protected:
    static void _bind_methods();

public:
    CollidableObject();
    ~CollidableObject();

    void _enter_tree() override;
    void _ready() override;

    void set_collision_shape(String shape);
    void set_model(String model_path);

    CollisionShape3D* get_collision_shape(); // So that you can edit the collision shape
    Node3D* get_model(); // So that you can edit the model
    
};

}

#endif // COLLIDABLE_OBJECT_H