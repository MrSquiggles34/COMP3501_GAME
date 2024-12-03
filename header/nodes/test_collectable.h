#ifndef TEST_COLLECTABLE_H
#define TEST_COLLECTABLE_H

#include "collectable_item_abstract.h"

// everything in gdextension is defined in this namespace
namespace godot {
	class TestCollectable : public CollectableItemAbstract {
		GDCLASS(TestCollectable, CollectableItemAbstract);

	private:
		bool in_inventory;
		float radius;
		ParticleSystem* indicator;

	protected:
		static void _bind_methods();

	public:
		TestCollectable();

		void _enter_tree() override;
		void _ready() override;
    	void _process(double delta) override;

		bool in_range(Vector3 player_pos);
	};

}

#endif