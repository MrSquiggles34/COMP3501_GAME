#include "quat_camera.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event.hpp>

using namespace godot;

void QuatCamera::_bind_methods() {}

QuatCamera::QuatCamera() : Camera3D() {
	our_quaternion = Quaternion(Vector3(0, 0, 1), 0.0f);
}

void QuatCamera::_enter_tree(){

}

void QuatCamera::_ready(){
	
	forward_ = Vector3(get_global_transform().basis[0][2], get_global_transform().basis[1][2], get_global_transform().basis[2][2]);
	side_ = Vector3(get_global_transform().basis[0][0], get_global_transform().basis[1][0], get_global_transform().basis[2][0]);
}

QuatCamera::~QuatCamera() {

}

void QuatCamera::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

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
		
	if(_input->is_action_pressed("yaw_increase")){
		Yaw(1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("yaw_decrease")){
		Yaw(-1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("pitch_increase")){
		Pitch(1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("pitch_decrease")){
		Pitch(-1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("roll_increase")){
		Roll(1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("roll_decrease")){
		Roll(-1.0f * delta * rotation_factor);
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
	// put the proper functionality in here
	Quaternion rotation = Quaternion(GetSide(), angle);
	Quaternion new_quat = rotation * our_quaternion;
	our_quaternion = (new_quat.normalized());
	set_quaternion((rotation * get_quaternion()).normalized());	
}


void QuatCamera::Yaw(float angle) {
	Quaternion rotation = Quaternion(GetUp(), angle);
	Quaternion new_quat = rotation * our_quaternion;
	our_quaternion = (new_quat.normalized());
	set_quaternion((rotation * get_quaternion()).normalized());	
}


void QuatCamera::Roll(float angle) {
	Quaternion rotation = Quaternion(GetForward(), angle);
	Quaternion new_quat = rotation * our_quaternion;
	our_quaternion = (new_quat.normalized());
	set_quaternion((rotation * get_quaternion()).normalized());
}