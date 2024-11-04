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

#define X_SIZE 500.0f
#define Y_SIZE 1000.0f

#define	BLANK_COL Color(1.0, 1.0, 1.0, 1)
#define ROAD_COL Color(0, 0, 0, 1)
#define BUILDING_COL Color(0.5, 0.5, 0.5, 1)

// everything in gdextension is defined in this namespace
namespace godot {
class Map : public Node3D {
	GDCLASS(Map, Node3D);

private:
	Node* buildings;
    MeshInstance3D* ground;
    Vector<MeshInstance3D*> building_list;
	
protected:
	static void _bind_methods();

public:
	Map();
	
	void _enter_tree ( ) override;
	void _ready ( ) override;

    void add_building (float x1, float y1, float x2, float y2, float h=0);
	void setup_starting_area (float width, float depth, float x, float y); // Coordinates based on bottom middle
	void setup_housing_area (float x, float y, Vector<Vector<int>> houses); // Coordinates based on bottom left
};

}

#endif