#ifndef CUSTOM_SCENE_H
#define CUSTOM_SCENE_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/templates/vector.hpp> 

#include <godot_cpp/variant/rect2.hpp> // for viewport size
#include <godot_cpp/classes/canvas_item.hpp> // for viewport size
#include <godot_cpp/classes/control.hpp> // for the anchors preset
#include <godot_cpp/classes/color_rect.hpp>

#include "quat_camera.h"
#include "map.h"
#include "player.h"
#include "test_collectable.h"
#include "hud.h"
#include "particle_system.h"
#include "collidable_object.h"
#include "building.h"

// everything in gdextension is defined in this namespace
namespace godot {
class CustomScene3501 : public Node3D {
	// this macro sets up a few internal things
	GDCLASS(CustomScene3501, Node3D);

private:
	double scene_time_passed;
	
	bool is_paused;
	bool was_paused = false;

	int test_obj_count;

	QuatCamera* main_camera;
    Map* map;
	Player* player;
	Vector<TestCollectable*> test_list;
	HUD* hud;
	Vector<ParticleSystem*> particle_systems;
	Building* building;

protected:
	// a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	CustomScene3501();
	~CustomScene3501();

	void _process(double delta) override;
	void _enter_tree ( ) override;
	void _ready ( ) override;

	void toggle_pause(bool paused);
	void create_particle_system(String node_name, String shader_name);
	

	template <class T> 
	bool add_as_child(T*& pointer, String name, bool search);
};

}

#endif