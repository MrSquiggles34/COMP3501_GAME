
#include "collectable_item_abstract.h"

using namespace godot;

void CollectableItemAbstract::_bind_methods() {}

CollectableItemAbstract::CollectableItemAbstract() : Node3D() {
	in_inventory = false;
    icon = NULL;
    lore = "Lorum Ipsum";
}

bool CollectableItemAbstract::in_range(float radius, Vector3 player_pos){
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