
#include <godot_cpp/classes/box_mesh.hpp>

#include "door.h"
#include "defs.h"

using namespace godot;

void Door::_bind_methods() {}

Door::Door() : InteractableItemAbstract() {
    width = 1.0;
}

void Door::_enter_tree ( ){
	if(DEBUG) UtilityFunctions::print("Enter Tree - Door."); 

    create_and_add_as_child<Label>(this, instructions, "Instructions", true);
}

void Door::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - Door."); 

    BoxMesh* self_mesh = memnew(BoxMesh);
    self_mesh->set_size(Vector3(2.0, 2.0, 0.5));

    StandardMaterial3D* material = memnew(StandardMaterial3D);
    material->set_albedo(Color(0.5, 0.5, 0.5, 1));
    self_mesh->surface_set_material(0, material);

    set_mesh(self_mesh);

    instructions->set_text("[E] - To open door");
    instructions->set_position(get_viewport()->get_visible_rect().size / 2 - instructions->get_minimum_size() / 2);
    instructions->set_visible(false);
}

void Door::act (){
    if(DEBUG) UtilityFunctions::print("Door");
}

bool Door::in_range (Vector3 player_pos){
    return InteractableItemAbstract::in_range(width, player_pos);
}