#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/cylinder_mesh.hpp>
#include <godot_cpp/classes/quad_mesh.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/capsule_shape3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/templates/vector.hpp> 
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/image_texture.hpp>

#include "create_and_add_as_child.h"
#include "collectable_item_abstract.h"
#include "quat_camera.h"
#include "custom_mesh.h"

namespace godot {

class Player : public CharacterBody3D {
    GDCLASS(Player, CharacterBody3D);

private:
    MeshInstance3D* body_mesh;
    CollisionShape3D* collision_shape;
    Vector<CollectableItemAbstract*> inventory;
    QuatCamera* main_camera;
    
    // Movement Variables
    float move_speed = 3.0f;
    float acceleration = 5.0f;

    // Screen Space effects
    MeshInstance3D* screen_quad_instance;
    ShaderMaterial* screen_space_shader_material;

    // Skybox
    CustomMesh* skybox;
    ShaderMaterial* skybox_shader_material;

    // Pause
    bool is_paused;

protected:
    static void _bind_methods();

public:
    Player();
    ~Player();

    void _enter_tree() override;
    void _ready() override;
    void _process(double delta) override;

    void toggle_pause(bool paused);
    void add_inventory (CollectableItemAbstract* item) { inventory.push_back(item); };
    Vector<CollectableItemAbstract*> get_inventory () { return inventory; };

    void update_velocity(double delta);

    int get_inventory_size();
    bool inInventory(String name);
    
};

}

#endif // PLAYER_H