#include "terrain_instance.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource_saver.hpp>

using namespace godot;

void TerrainInstance::_bind_methods() {
}

TerrainInstance::TerrainInstance() {
	// Initialize any variables here.
}

void TerrainInstance::_enter_tree(){
	// if the mesh hasn't been added to the node yet
	if(get_mesh().is_null()){
		terrain_mesh = memnew(TerrainMesh);
		terrain_mesh->setup();
		set_mesh(terrain_mesh);
		
		terrain_mesh->take_over_path("res://resource_files/terrain.mesh");
		ResourceSaver::get_singleton()->save(terrain_mesh);
		UtilityFunctions::print(terrain_mesh->get_path());
	}
	else{
		terrain_mesh = dynamic_cast<TerrainMesh*>(get_mesh().ptr());
		terrain_mesh->load_height_map_from_packed(); 
	}
}
