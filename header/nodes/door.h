#ifndef DOOR_H
#define DOOR_H

#include "interactable_item_abstract.h"

// everything in gdextension is defined in this namespace
namespace godot {
	class Door : public InteractableItemAbstract {
		GDCLASS(Door, InteractableItemAbstract);

	private:
		Label* instructions;
		float width;

	protected:
		static void _bind_methods();

	public:
		Door();

		void _enter_tree() override;
		void _ready() override;

		void act();
		bool in_range(Vector3 player_pos);
		void set_instruct_visible(bool visible) { InteractableItemAbstract::set_instruct_visible(visible); };
	};

}

#endif