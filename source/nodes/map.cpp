#include "defs.h"
#include "map.h"

#include <godot_cpp/core/memory.hpp> 
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp> 
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Map::_bind_methods() {}

Map::Map() : Node3D() {
    x_size = 500.0f;
    y_size = 1000.0f;	
}

void Map::_enter_tree ( ){
	if(DEBUG) UtilityFunctions::print("Enter Tree - Map."); 

    create_and_add_as_child<MeshInstance3D>(this, ground, "Ground", true);

    // Add a rectangle for the ground
    BoxMesh* ground_mesh = memnew(BoxMesh);
    ground_mesh->set_size(Vector3(x_size, 1.0f, y_size));

    StandardMaterial3D* material = memnew(StandardMaterial3D);
    material->set_albedo(Color(1.0, 1.0, 1.0, 1));
    ground_mesh->surface_set_material(0, material);

    ground->set_mesh(ground_mesh);
    
    create_and_add_as_child<Node>(this, buildings, "Buildings", true);
}

void Map::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - Map."); 

    ground->set_global_position(Vector3(0.0, 0.0, 25.0-y_size/2));

    // Figure out a good way to put this into an array of sorts and loop it
    add_building(-12.0, 0.0, 12.0, -10.0); //0
    add_building(-20.0, 28.0, -12.0, 0.0); //1
    add_building(12.0, 18.0, 30.0, 0.0); //2
    add_building(12.0, 28.0, 23.0, 18.0); //3
    add_building(-38.0, 35.0, -2.0, 28.0); //4
    add_building(2.0, 36.0, 15.0, 28.0); //5
}

// Function for adding buildings based on 2 x/y coordinates (4 floats)
void Map::add_building (float x1, float y1, float x2, float y2){
    MeshInstance3D* new_building;
    create_and_add_as_child<MeshInstance3D>(buildings, new_building, vformat("Building%d", building_list.size()), true);

    RandomNumberGenerator* rng = memnew(RandomNumberGenerator);

    BoxMesh* building = memnew(BoxMesh);
    float x_len = abs(x1 - x2);
    float y_len = abs(y1 - y2);
    float height = rng->randf_range(5.0f, 20.0f);
    building->set_size(Vector3(x_len, height, y_len));

    StandardMaterial3D* material = memnew(StandardMaterial3D);
    material->set_albedo(Color(0.5, 0.5, 0.5, 1));
    building->surface_set_material(0, material);

    new_building->set_mesh(building);
    new_building->set_global_position(Vector3(x1+x_len/2.0, height/2.0, -y1+y_len/2.0));
    building_list.push_back(new_building);
}