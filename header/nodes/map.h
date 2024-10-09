#ifndef MAP_H
#define MAP_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/random_number_generator.hpp> 
#include <godot_cpp/templates/vector.hpp>

#include "create_and_add_as_child.h"

// everything in gdextension is defined in this namespace
namespace godot {
class Map : public Node3D {
	GDCLASS(Map, Node3D);

private:
	float x_size;
    float y_size;

    Node* buildings;
    MeshInstance3D* ground;
    Vector<MeshInstance3D*> building_list;
	
protected:
	static void _bind_methods();

public:
	Map();
	
	void _enter_tree ( ) override;
	void _ready ( ) override;

    void add_building (float x1, float y1, float x2, float y2);
};

}

#endif