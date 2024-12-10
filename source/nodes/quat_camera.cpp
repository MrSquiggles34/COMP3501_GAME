
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

#include "quat_camera.h"

#include "defs.h"

using namespace godot;

void QuatCamera::_bind_methods() {}

QuatCamera::QuatCamera() : Camera3D() {
	our_quaternion = Quaternion(Vector3(0, 0, 1), 0.0f);
	is_paused = false;
}

void QuatCamera::_enter_tree(){
	// screen quad is a child of the camera so that it will follow it around (even though the shader positions it into clip space, this can prevent culling)
	create_and_add_as_child<MeshInstance3D>(this, screen_quad_instance, "Screen Quad", true);

	// Setup the screen-space shader
	QuadMesh* quad_mesh = memnew(QuadMesh);
	quad_mesh->set_size(Vector2(2, 2)); 
	quad_mesh->set_flip_faces(true);

	screen_space_shader_material = memnew(ShaderMaterial);
	Ref<Shader> shader = ResourceLoader::get_singleton()->load("shaders/simple.gdshader", "Shader"); 
	screen_space_shader_material->set_shader(shader);
	quad_mesh->surface_set_material(0, screen_space_shader_material);
	screen_quad_instance->set_mesh(quad_mesh);
	screen_quad_instance->set_extra_cull_margin(50.0f);
}

void QuatCamera::_ready(){
	forward_ = Vector3(get_global_transform().basis[0][2], get_global_transform().basis[1][2], get_global_transform().basis[2][2]);
	side_ = Vector3(get_global_transform().basis[0][0], get_global_transform().basis[1][0], get_global_transform().basis[2][0]);
}

QuatCamera::~QuatCamera() {
}

// FUNCTION FOR MOUSE LOOKING
void QuatCamera::_input(const Ref<InputEvent>& event) {
	if (!is_paused) {
		Input::get_singleton()->set_mouse_mode(Input::MouseMode::MOUSE_MODE_CAPTURED);
	}
	else {
		Input::get_singleton()->set_mouse_mode(Input::MouseMode::MOUSE_MODE_VISIBLE);
	}

	if (Engine::get_singleton()->is_editor_hint() || is_paused) return;

	Ref<InputEventMouseMotion> mouse_event = event;
	if (mouse_event.is_valid()) {
		const float mouse_sensitivity = 0.003f;

		float mouse_x_motion = mouse_event->get_relative().x;
		float mouse_y_motion = mouse_event->get_relative().y;

		Yaw(-mouse_x_motion * mouse_sensitivity);
		Pitch(-mouse_y_motion * mouse_sensitivity);
	}
}

Vector3 QuatCamera::GetForward(void) const {
	Vector3 current_forward = (our_quaternion.xform(forward_));
	current_forward.y = 0;
	return -current_forward.normalized();
}

Vector3 QuatCamera::GetSide(void) const {
	Vector3 current_side = (our_quaternion.xform(side_));
	return current_side.normalized();
}

Vector3 QuatCamera::GetUp(void) const {
	Vector3 current_up = Vector3(0,1,0);
	return current_up.normalized();
}

void QuatCamera::Pitch(float angle) {
	// Declare a max and minimum for pitch
	const float max_pitch = 89.0f * Math_PI / 180.0f;
	const float min_pitch = -89.0f * Math_PI / 180.0f;

	// Calculate the current pitch relative to the forward vector
	Vector3 forward = our_quaternion.xform(Vector3(0, 0, -1)); 
	float current_pitch = Math::asin(forward.y); 

	// Calculate the new pitch and clamp it
	float new_pitch = Math::clamp(current_pitch + angle, min_pitch, max_pitch);
	float delta_pitch = new_pitch - current_pitch;

	// Apply the clamped pitch rotation
	Quaternion pitch_rotation = Quaternion(GetSide(), delta_pitch);
	our_quaternion = (pitch_rotation * our_quaternion).normalized();
	set_quaternion(our_quaternion);
}

void QuatCamera::Yaw(float angle) {
	// Rotate around the global up axis, different from Assignment 2
	Vector3 global_up = Vector3(0, 1, 0);
	Quaternion rotation = Quaternion(global_up, angle);
	our_quaternion = (rotation * our_quaternion).normalized();
	set_quaternion((rotation * get_quaternion()).normalized());
}

void QuatCamera::toggle_pause(bool paused) {
	is_paused = paused;

	if (is_paused) {
		Ref<Shader> shader = ResourceLoader::get_singleton()->load("shaders/blur-effect.gdshader", "Shader");
		screen_space_shader_material->set_shader(shader);
	}
	else {
		Ref<Shader> shader = ResourceLoader::get_singleton()->load("shaders/simple.gdshader", "Shader");
		screen_space_shader_material->set_shader(shader);
	}

	if (DEBUG) UtilityFunctions::print(is_paused ? "Camera Paused" : "Camera Resumed");
}
