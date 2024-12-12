#ifndef TERRAIN_MESH_H_
#define TERRAIN_MESH_H_

// parent class
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/object.hpp>

#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/array.hpp>

#include <godot_cpp/variant/packed_vector3_array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/variant/packed_color_array.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>

#include "defs.h"
#include "noise.h"
#include "custom_mesh.h"

namespace godot {

class TerrainMesh : public ArrayMesh {
    // this macro sets up a few internal things
	GDCLASS(TerrainMesh, ArrayMesh);

private:
	OpenSimplexNoise noise;

	PackedVector3Array vertices; 	// vertex positions in model space
	PackedVector3Array normals; 	// vertex normals
	PackedVector2Array uv;	 		// texture coordinates
	PackedColorArray colors;		// color associated with that vertex
	PackedInt32Array indices;		// creates the triangles; interpreted as triples.

	// dimensions of mesh in number of vertices
	int array_width;
	int array_height;
	
	// since Vector<Vector<float>> is not an option for saving, we need to have a PackedFloat32Array that has the same information. 
	Vector<Vector<float>> height_map;
	PackedFloat32Array packed_height_map; // for serialization

	// You will likely want to add a bunch of other member variables and functions

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	TerrainMesh();
	~TerrainMesh();

	void setup();

	#pragma region SETUP HELPERS
	// this one should be called after the arrays have been setup by another helper function.
	void setup_mesh(void);
	#pragma endregion SETUP HELPERS

	// allows for saving and loading the height map
	void save_height_map_to_packed();
	void load_height_map_from_packed();

	#pragma region SIMPLE GETTERS AND SETTERS
	Vector<Vector<float>> get_height_map();

	inline void set_array_width(float aw) { array_width = aw; }
	inline float get_array_width() { return array_width; }
	inline void set_array_height(float ah) { array_height = ah; }
	inline float get_array_height() { return array_height; }

	PackedFloat32Array get_packed_height_map();
	void set_packed_height_map(PackedFloat32Array);
	#pragma endregion SIMPLE GETTERS AND SETTERS

};

}

#endif // TERRAIN_MESH_H_