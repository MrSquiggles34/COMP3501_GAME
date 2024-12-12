#ifndef TERRAIN_INSTANCE_H_
#define TERRAIN_INSTANCE_H_

// parent class
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "defs.h"
#include "terrain_mesh.h"

namespace godot {

class TerrainInstance : public MeshInstance3D {
    // this macro sets up a few internal things
	GDCLASS(TerrainInstance, MeshInstance3D);

private:
	TerrainMesh* terrain_mesh;

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	TerrainInstance();
	// ~TerrainInstance();

	void _enter_tree() override;

	inline TerrainMesh* get_terrain_mesh() { return terrain_mesh; }
	float get_height_at(float x, float z);
};

}

#endif // ADVANCED_INSTANCE_H_