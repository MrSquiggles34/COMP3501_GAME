#ifndef ROBO_BASE_H
#define ROBO_BASE_H

#include "robo_part.h"


// everything in gdextension is defined in this namespace
namespace godot {
	class RoboBase : public RoboPart {
		// this macro sets up a few internal things
		GDCLASS(RoboBase, RoboPart);

	protected:
		// a static function that Godot will call to find out which methods can be called and which properties it exposes
		static void _bind_methods();

	public:
		RoboBase();
		~RoboBase();

		void _enter_tree() override;
		void _process(double delta) override;
	};

}

#endif