#ifndef CUSTOM_MESH_H
#define CUSTOM_MESH_H

// parent class
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/shader.hpp>

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/resource.hpp> 
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/torus_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/compressed_texture2d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

#include <godot_cpp/classes/input_event.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/string.hpp>

#include "defs.h"

#define DEBUG true

// everything in gdextension is defined in this namespace
namespace godot {
class CustomMesh : public MeshInstance3D {
    // this macro sets up a few internal things
	GDCLASS(CustomMesh, MeshInstance3D);

private:
	double time_passed;
	String shader_name;

	ShaderMaterial* shader_material;
	Vector3 base_color;

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	CustomMesh();
	~CustomMesh();

	void _enter_tree ( ) override;
	void _ready ( ) override;
	void _process(double delta) override;

	// both of these should be called in the container's _enter_tree; so that they can be used in this->_ready()
	// they will have no effect if called after
	// *if* you wanted to change them to be able to work at any point, think about the cascading effect of changing the shader... What will you need to carry over to the new ShaderMaterial?
	void set_base_color(Vector3 color);
	inline void set_shader_name(String shader) { shader_name = shader; }

	inline Vector3 get_base_color() { return base_color; }
	inline String get_shader_name() { return shader_name; }

	// for when you want to do some parameter setting that isn't one of the ones below; you can also add member functions for different parameter setting if you want. 
	inline ShaderMaterial* get_shader_material() { return shader_material; }

	// these two functions set the texture to "texture_1"
	void set_texture(String name);
	void set_texture_from_data(PackedFloat32Array*);


};

}

#endif