#include "defs.h"
#include "collectable_item_abstract.h"

using namespace godot;

void CollectableItemAbstract::_bind_methods() {}

CollectableItemAbstract::CollectableItemAbstract() : MeshInstance3D() {
	in_inventory = false;
}