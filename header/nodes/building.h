#ifndef BUILDING_H
#define BUILDING_H

// Misc
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/templates/vector.hpp> 
#include <godot_cpp/classes/resource_loader.hpp>
#include "create_and_add_as_child.h"
#include "collidable_object.h"

namespace godot {

class Building : public Node3D {
    GDCLASS(Building, Node3D);

private:
    CollidableObject* building;

protected:
    static void _bind_methods();

public:
    Building();
    ~Building();

    void _enter_tree() override;
    void _ready() override;
    
};

}

#endif // BUILDING_H