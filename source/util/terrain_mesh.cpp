#include "terrain_mesh.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource_saver.hpp>

using namespace godot;

void TerrainMesh::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_array_width", "array_width"), &TerrainMesh::set_array_width);
	ClassDB::bind_method(D_METHOD("get_array_width"), &TerrainMesh::get_array_width);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "array_width"), "set_array_width", "get_array_width");

	ClassDB::bind_method(D_METHOD("set_array_height", "array_height"), &TerrainMesh::set_array_height);
	ClassDB::bind_method(D_METHOD("get_array_height"), &TerrainMesh::get_array_height);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "array_height"), "set_array_height", "get_array_height");

	ClassDB::bind_method(D_METHOD("set_packed_height_map", "packed_height_map"), &TerrainMesh::set_packed_height_map);
	ClassDB::bind_method(D_METHOD("get_packed_height_map"), &TerrainMesh::get_packed_height_map);

	ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "packed_height_map"), "set_packed_height_map", "get_packed_height_map");
}

TerrainMesh::TerrainMesh() {
	array_width = 2;
	array_height = 2;
}

TerrainMesh::~TerrainMesh(){ }

// Square terrain generation
void TerrainMesh::setup(){
	// Initialize OpenSimplexNoise
    OpenSimplexNoise noise(12345); 

    // Adjust the size of the terrain
    array_width = 12;
    array_height = 12;

    // Clear previous data
    vertices.clear();
    colors.clear();
    normals.clear();
    uv.clear();
    indices.clear();

    // Iterate through the terrain grid
    for (int x = 0; x < array_width; x++) {
        for (int y = 0; y < array_height; y++) {
            // Generate height based on noise
            float height = noise.get_noise_2d(x * 0.1f, y * 0.1f) * 10.0f;  

            // Create vertex with noise-based height
            Vector3 vertex(x, height, y);
            vertices.push_back(vertex);

            // Assign color based on height 
            Color vertexColor(0.5f + height * 0.05f, 1.0f - height * 0.05f, 0.2f, 1.0f);
            colors.push_back(vertexColor);

            // Normal (simple flat terrain for now)
            normals.push_back(Vector3(0, 1, 0));

            // Texture coordinates
            uv.push_back(Vector2((float)x / array_width, (float)y / array_height));

            // Create indices 
            if (x < array_width - 1 && y < array_height - 1) {
                int i0 = x * array_height + y;
                int i1 = (x + 1) * array_height + y;
                int i2 = x * array_height + (y + 1);
                int i3 = (x + 1) * array_height + (y + 1);

                indices.push_back(i0);
                indices.push_back(i1);
                indices.push_back(i2);
                indices.push_back(i1);
                indices.push_back(i3);
                indices.push_back(i2);
            }
        }
    }

    // Call setup_mesh to finalize the mesh setup
    setup_mesh();

	// Create a material for the terrain
	StandardMaterial3D* mat = memnew(StandardMaterial3D);
	Ref<Texture2D> texture = ResourceLoader::get_singleton()->load("textures/sand.jpg", "Texture");
	if (!texture.is_valid()) {
		UtilityFunctions::print("Failed to load texture!");
	}

	// Ensures the texture shows properly
	mat->set_texture(BaseMaterial3D::TEXTURE_ALBEDO, texture);
	

	surface_set_material(0, mat);
}

void TerrainMesh::setup_mesh(){
	//  use the arrays that we setup in the other functions to make a mesh.
	Array arrays = Array();
	arrays.resize((int)Mesh::ARRAY_MAX);
	arrays[(int)Mesh::ARRAY_VERTEX] = vertices;
	arrays[(int)Mesh::ARRAY_NORMAL] = normals;
	arrays[(int)Mesh::ARRAY_TEX_UV] = uv;
	arrays[(int)Mesh::ARRAY_COLOR] = colors;
	arrays[(int)Mesh::ARRAY_INDEX] = indices;

	add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);
}

Vector<Vector<float>> TerrainMesh::get_height_map(){
	return height_map;
}

PackedFloat32Array TerrainMesh::get_packed_height_map(){
	return packed_height_map;
}
void TerrainMesh::set_packed_height_map(PackedFloat32Array phm){
	packed_height_map = phm;
}

void TerrainMesh::save_height_map_to_packed(){
	for(int x = 0; x < height_map.size(); x++){
		for(int y = 0; y < height_map.get(0).size(); y++){
			packed_height_map.append(height_map.get(x).get(y));
		}
	}
}

void TerrainMesh::load_height_map_from_packed(){
	int counter = 0;

	for(int x = 0; x < array_width; x++){
		Vector<float> height_map_row;
		for(int y = 0; y < array_height; y++){
			height_map_row.push_back(packed_height_map[counter]);
			counter++;
		}
		height_map.push_back(height_map_row);
	}
}
