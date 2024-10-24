#include "quat_camera.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>


using namespace godot;

void QuatCamera::_bind_methods() {}

QuatCamera::QuatCamera() : Camera3D() {
	our_quaternion = Quaternion(Vector3(0, 0, 1), 0.0f);
}

void QuatCamera::_enter_tree(){
	
}

void QuatCamera::_ready(){

	// Lock the mouse pointer to the camera
	//game_node = Object::cast_to<Game>(get_tree()->get_root()->get_child(0));

	Input::get_singleton()->set_mouse_mode(Input::MouseMode::MOUSE_MODE_CAPTURED);
	
	forward_ = Vector3(get_global_transform().basis[0][2], get_global_transform().basis[1][2], get_global_transform().basis[2][2]);
	side_ = Vector3(get_global_transform().basis[0][0], get_global_transform().basis[1][0], get_global_transform().basis[2][0]);
}

QuatCamera::~QuatCamera() {

}

void QuatCamera::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	// Pause movement when game is paused
	//if (game_node && game_node->get_is_paused()) {
	//	return; 
	//}

	// you can speed up by changing these, if desired. 
	float rotation_factor = 1.0f;	
	float translation_factor = 1.0f;
	
	Input* _input = Input::get_singleton();
	if(_input->is_action_pressed("move_right")){
		set_position(get_position() + GetSide() * delta * translation_factor);
	}
	if(_input->is_action_pressed("move_left")){
		set_position(get_position() - GetSide() * delta * translation_factor);
	}
	if(_input->is_action_pressed("move_up")){
		set_position(get_position() + GetUp() * delta * translation_factor);
	}
	if(_input->is_action_pressed("move_down")){
		set_position(get_position() - GetUp() * delta * translation_factor);
	}
	if(_input->is_action_pressed("move_forward")){
		set_position(get_position() + GetForward() * delta * translation_factor);
	}
	if(_input->is_action_pressed("move_backward")){
		set_position(get_position() - GetForward() * delta * translation_factor);
	}
}

// FUNCTION FOR MOUSE LOOKING
void QuatCamera::_input(const Ref<InputEvent>& event) {

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
	return -current_forward.normalized(); // Return -forward since the camera coordinate system points in the opposite direction
}


Vector3 QuatCamera::GetSide(void) const {
	// what should this be replaced with?
	Vector3 current_side = (our_quaternion.xform(side_));
	return current_side.normalized();
}


Vector3 QuatCamera::GetUp(void) const {
	// how do you get the up vector?
	Vector3 current_up = GetSide().cross(GetForward());
	return current_up.normalized();
}

void QuatCamera::Pitch(float angle) {
	// Declare a max and minimum for pitch
	const float max_pitch = 89.0f * Math_PI / 180.0f;  
	const float min_pitch = -89.0f * Math_PI / 180.0f; 

	// Calculate the current pitch relative to the forward vector
	Vector3 forward = GetForward();
	float current_pitch = Math::asin(forward.y); 

	// Clamp the pitch angle to prevent over-rotation
	float new_pitch = Math::clamp(current_pitch + angle, min_pitch, max_pitch);

	// Calculate the change in pitch and apply the new rotation
	angle = new_pitch - current_pitch;
	Quaternion rotation = Quaternion(GetSide(), angle);
	our_quaternion = (rotation * our_quaternion).normalized();
	set_quaternion((rotation * get_quaternion()).normalized());
}



void QuatCamera::Yaw(float angle) {
	// Rotate around the global up axis, different from Assignment 2
	Vector3 global_up = Vector3(0, 1, 0);
	Quaternion rotation = Quaternion(global_up, angle);
	our_quaternion = (rotation * our_quaternion).normalized();
	set_quaternion((rotation * get_quaternion()).normalized());
}



void QuatCamera::Roll(float angle) {
	Quaternion rotation = Quaternion(GetForward(), angle);
	Quaternion new_quat = rotation * our_quaternion;
	our_quaternion = (new_quat.normalized());
	set_quaternion((rotation * get_quaternion()).normalized());
}



