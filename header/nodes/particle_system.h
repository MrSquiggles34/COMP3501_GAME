#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

// parent class
#include <godot_cpp/classes/gpu_particles3d.hpp>
#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/input.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>

// you can adjust these if you want. 
#define MIN_SPEED 0.0f
#define ACCELERATION 2.0f


// everything in gdextension is defined in this namespace
namespace godot {
	class ParticleSystem : public GPUParticles3D {
		// this macro sets up a few internal things
		GDCLASS(ParticleSystem, GPUParticles3D);

	private:
		int something;

		String shader_name; // assumes that the particle shader and spatial shader have the same name + _ps.gdshader or + _ss.gdshader

	protected:
		// a static function that Godot will call to find out which methods can be called and which properties it exposes
		static void _bind_methods();

	public:
		ParticleSystem();
		ParticleSystem(String shader_name);
		~ParticleSystem();

		void _enter_tree() override;
		void _ready() override;
		void _process(double delta) override;

		inline void set_shader_name(String name) { shader_name = name; }
		inline String get_shader_name() { return shader_name; }

	};

}

#endif