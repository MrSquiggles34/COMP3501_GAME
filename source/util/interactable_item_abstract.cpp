
#include "interactable_item_abstract.h"

using namespace godot;

void InteractableItemAbstract::_bind_methods() {}

InteractableItemAbstract::InteractableItemAbstract() : MeshInstance3D() {
}

void InteractableItemAbstract::_enter_tree ( ){
	create_and_add_as_child<Label>(this, instructions, "Instructions", true);
}

bool InteractableItemAbstract::in_range(float radius, Vector3 player_pos){
	Vector3 self_pos = get_global_position();
    if(self_pos[0]-radius <= player_pos[0] && player_pos[0] <= self_pos[0]+radius){
        if(self_pos[1]-radius <= player_pos[1] && player_pos[1] <= self_pos[1]+radius){
            if(self_pos[2]-radius <= player_pos[2] && player_pos[2] <= self_pos[2]+radius){
                return true;
            }
        }
    }

    return false;
}

void InteractableItemAbstract::set_instruct_visible(bool visible){
    instructions->set_visible(visible);
}