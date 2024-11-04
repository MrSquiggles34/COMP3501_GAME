#include "defs.h"
#include "test_collectable.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp> 
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void TestCollectable::_bind_methods() {}

TestCollectable::TestCollectable() : CollectableItemAbstract() {
	in_inventory = false;
	radius = 1.0;
}

void TestCollectable::_enter_tree ( ){
	if(DEBUG) UtilityFunctions::print("Enter Tree - TestCollectable."); 
}

void TestCollectable::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - TestCollectable."); 

    SphereMesh* self_mesh = memnew(SphereMesh);
    self_mesh->set_radius(radius);
	self_mesh->set_height(radius*2.0);

    StandardMaterial3D* material = memnew(StandardMaterial3D);
    material->set_albedo(Color(1.0, 1.0, 0.0, 1.0f));
    self_mesh->surface_set_material(0, material);

    set_mesh(self_mesh);
}

bool TestCollectable::in_range (Vector3 player_pos){
    return CollectableItemAbstract::in_range(radius, player_pos);
}