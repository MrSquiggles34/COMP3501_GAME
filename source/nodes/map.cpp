
#include <godot_cpp/core/memory.hpp> 
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

#include "map.h"

#include "defs.h"
#include "create_and_add_as_child.h"

using namespace godot;

void Map::_bind_methods() {}

Map::Map() : Node3D() {
}

void Map::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - Map.");

    create_and_add_as_child<CustomMesh>(this, ground, "Ground", true);
    ground->set_shader_name(vformat("%s%s.gdshader", "shaders/", "lighting"));

    // Add a rectangle for the ground
    BoxMesh* ground_mesh = memnew(BoxMesh());
    ground_mesh->set_size(Vector3(X_SIZE, 1.0f, Y_SIZE));

    // Set the ground lighting shader
    ShaderMaterial* ground_material = memnew(ShaderMaterial());
    Ref<Shader> shader = ResourceLoader::get_singleton()->load(vformat("%s%s.gdshader", "shaders/", "lighting"), "Shader");
    ground_material->set_shader(shader);
    ground_mesh->surface_set_material(0, ground_material);

    ground->set_mesh(ground_mesh);
    ground_material->set_shader_parameter("color_in", BLANK_COL);
    ground_material->set_shader_parameter("light_position", Vector3(0.0f, 5.0f, 0.0f));
    ground_material->set_shader_parameter("specular_power", 20.0f);

    create_and_add_as_child<Robo>(this, robo1, "Robo1", true);

    create_and_add_as_child<Node>(this, buildings, "Buildings", true);
}

void Map::_ready() {
    if (DEBUG) UtilityFunctions::print("Ready - Map.");

    ground->set_global_position(Vector3(0.0, 0.0, 25.0 - Y_SIZE / 2));

    // Note the grid is upside down (as in reflect, not rotated, so left is still left)
    Vector<Vector<int>> main_city = {
        {1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
        {1,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1},
        {1,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1},
        {1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1},
        {1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,1,1},
        {1,0,1,0,0,0,1,1,1,0,0,0,0,0,1,0,1,0,1,1,1,0,1},
        {1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
        {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
        {1,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    setup_starting_area(24.0, 18.0, 0, 0);
    setup_housing_area(-90.0, 35.0, main_city);
}

// Function for adding buildings based on 2 x/y coordinates (4 floats)
void Map::add_building(float x1, float y1, float x2, float y2, float h) {
    CustomMesh* new_building;
    create_and_add_as_child<CustomMesh>(buildings, new_building, vformat("Building%d", building_list.size()), true);

    RandomNumberGenerator* rng = memnew(RandomNumberGenerator);

    BoxMesh* building = memnew(BoxMesh);
    float x_len = abs(x1 - x2);
    float y_len = abs(y1 - y2);
    float height = h;
    if (height == 0) height = rng->randf_range(5.0f, 20.0f);

    building->set_size(Vector3(x_len, height, y_len));

    ShaderMaterial* building_material = memnew(ShaderMaterial);
    Ref<Shader> shader = ResourceLoader::get_singleton()->load(vformat("%s%s.gdshader", "shaders/", "lighting"), "Shader");
    building_material->set_shader(shader);
    building->surface_set_material(0, building_material);

    new_building->set_mesh(building);
    new_building->set_global_position(Vector3(x1 + x_len / 2.0, height / 2.0, -y1 + y_len / 2.0));

    // Shader uniforms
    building_material->set_shader_parameter("color_in", BUILDING_COL);
    building_material->set_shader_parameter("light_position", Vector3(0.0f, 5.0f, 0.0f));
    building_material->set_shader_parameter("specular_power", 1.0f);

    building_list.push_back(new_building);


}

void Map::setup_starting_area(float width, float depth, float x, float y) {
    float radius = width / 2;

    add_building(x - radius, y, x + radius, y - 10.0); // Back Building
    add_building(x - radius - 10.0, y + depth, x - radius, y); // Left Building
    add_building(x + radius, y + (depth * 0.4), x - radius + 20.0, y); // Right Building (South)
    add_building(x + radius, y + depth, x - radius + 10.0, y + (depth * 0.4)); // Right Building (North)
    add_building(x - radius - 20.0, y + depth + 10.0, x - 2.5, y + depth); // Upper Left Building
    add_building(x + 2.5, y + depth + 20.0, x + radius + 5.0, y + depth); // Upper Right Building
}

void Map::setup_housing_area(float x, float y, Vector<Vector<int>> houses) {
    float house_size = 8;
    float road_size = 0;

    for (int i = 0; i < houses.size(); i++) {
        for (int j = 0; j < houses[i].size(); j++) {
            if (houses[i][j] == 1) {
                float x1 = x + ((house_size + road_size) * j);
                float y1 = y + (house_size * i);
                float x2 = x + (house_size * (j + 1)) + (road_size * j);
                float y2 = y + (house_size * (i + 1));

                add_building(x1, y1, x2, y2);
            }
        }

    }
}

void Map::toggle_pause(bool paused) {
    is_paused = paused;

    // Propogate Pause 
    robo1->toggle_pause(is_paused);

    if (DEBUG) UtilityFunctions::print(is_paused ? "Map Paused" : "Map Resumed");
}