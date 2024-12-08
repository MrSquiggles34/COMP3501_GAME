#ifndef MAP_H
#define MAP_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/templates/vector.hpp>

#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


#include "custom_mesh.h"
#include "robo.h"

#define X_SIZE 250.0f
#define Y_SIZE 250.0f

#define	BLANK_COL Color(1.0, 1.0, 1.0, 1)
#define ROAD_COL Color(0, 0, 0, 1)
#define BUILDING_COL Color(0.5, 0.5, 0.5, 1)

// everything in gdextension is defined in this namespace
namespace godot {
class Map : public Node3D {
	GDCLASS(Map, Node3D);

private:
	Node* buildings;
    CustomMesh* ground;
    Vector<CustomMesh*> building_list;

	Robo* robo1;

	bool is_paused;
	
protected:
	static void _bind_methods();

public:
	Map();
	
	void _enter_tree ( ) override;
	void _ready ( ) override;

    void add_building (float x1, float y1, float x2, float y2, float h=0);
	void setup_starting_area (float width, float depth, float x, float y); // Coordinates based on bottom middle
	void setup_housing_area (float x, float y, Vector<Vector<int>> houses); // Coordinates based on bottom left
	void toggle_pause(bool paused);
};

}

#endif