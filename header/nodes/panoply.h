#ifndef PANOPLY_H
#define PANOPLY_H

#include "collectable_item_abstract.h"

// everything in gdextension is defined in this namespace
namespace godot {
	class Panoply : public CollectableItemAbstract {
		GDCLASS(Panoply, CollectableItemAbstract);

	private:
		bool in_inventory;
		float radius;

	protected:
		static void _bind_methods();

	public:
		Panoply();

		void _enter_tree() override;
		void _ready() override;
    	void _process(double delta) override;

		bool in_range(Vector3 player_pos);
	};

}

#endif