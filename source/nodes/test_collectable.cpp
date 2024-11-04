
#include <godot_cpp/classes/sphere_mesh.hpp>

#include "test_collectable.h"

#include "defs.h"

using namespace godot;

void TestCollectable::_bind_methods() {}

TestCollectable::TestCollectable() : CollectableItemAbstract() {
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