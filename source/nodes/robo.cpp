#include "robo.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/scene_tree.hpp> // for root

using namespace godot;

void Robo::_bind_methods() {

}

Robo::Robo() : Node3D() {
	is_paused = false;
}

Robo::~Robo() {
	// Add cleanup here, if you have any. I don't, typically. 
}

// Adds the crane parts to the crane in the editor. 
// the add_child and set_owner should happen in _enter_tree, or we will not see them in the editor
void Robo::_enter_tree() {
	// TODO setup your parts with the correct hierarchical relationships here
	create_and_add_as_child<RoboBase>(base1, "RoboBase1", true);
	create_and_add_as_child<RoboBase>(base2, "RoboBase2", true);
	create_and_add_as_child<RoboJoint>(joint1, "RoboJoint1", true);
	create_and_add_as_child<RoboJoint>(joint2, "RoboJoint2", true);
	
	create_and_add_as_child<RoboBase>(arm1, "RoboArm1", true);
	create_and_add_as_child<RoboBase>(arm2, "RoboArm2", true);
	create_and_add_as_child<RoboBase>(arm3, "RoboArm3", true);

	create_and_add_as_child<RoboHead>(head, "RoboHead", true);

	create_and_add_as_child<RoboBase>(pinch1, "Pinch1", true);
	create_and_add_as_child<RoboBase>(pinch2, "Pinch2", true);

	// Hierarchy
	base2->set_parent(base1);
		joint1->set_parent(base2);
		joint2->set_parent(base2);
		arm1->set_parent(base2);
			arm2->set_parent(arm1);
				arm3->set_parent(arm2);
					head->set_parent(arm3);
						pinch1->set_parent(head);
						pinch2->set_parent(head);

	// Perform local transformations
	base2->set_local_position(Vector3(0.0f, 0.5f, 0.0f));
	base2->set_scale(Vector3(0.5f, 2.0f, 0.5f));
	
	joint1->set_local_position(Vector3(0.0f, 1.0f, 1.0f));
	joint2->set_local_position(Vector3(0.0f, 1.0f, -1.0f));

	arm1->set_local_position(Vector3(-1.0f, 2.5f, 0.0f));
	arm1->set_scale(Vector3(0.25f, 9.0, 0.25f));
	arm1->set_local_rotation(Quaternion(Vector3(0, 0, 1), Math::deg_to_rad(25.0f)));

	arm2->set_local_position(Vector3(1.0f, 2.2f, 1.0f));
	arm2->set_scale(Vector3(0.35f, 6.0, 0.35f));
	arm2->set_local_rotation(Quaternion(Vector3(0, 0, 1), Math::deg_to_rad(55.0f)));

	arm3->set_local_position(Vector3(0.0f, -2.0f, 0.0f));
	arm3->set_scale(Vector3(0.2f, 6.0, 0.2f));
	arm3->set_local_rotation(Quaternion(Vector3(0, 0, 1), Math::deg_to_rad(0.0f)));

	head->set_local_position(Vector3(0.0f, -2.0f, 0.0f));

	pinch1->set_local_position(Vector3(-0.75f, -0.5, 0.0f));
	pinch1->set_scale(Vector3(0.1f, 2.0, 0.1f));
	pinch1->set_local_rotation(Quaternion(Vector3(0, 0, 1), Math::deg_to_rad(20.0f)));

	pinch2->set_local_position(Vector3(0.75f, -0.5f, 0.0f));
	pinch2->set_scale(Vector3(0.1f, 2.0, 0.1f));
	pinch2->set_local_rotation(Quaternion(Vector3(0, 0, 1), Math::deg_to_rad(-20.0f)));
}

void Robo::_ready() {
}

void Robo::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return;
	
	if (!is_paused) {

		float rotation_speed = 0.02f;
		float amplitude = 1.0f;

		// Parameters to control motion cycles
		float pause_duration = 3.0f;
		float move_duration = 2.0f;
		float total_cycle_time = pause_duration + move_duration;

		// Update time
		base2->set_time_passed(base2->get_time_passed() + delta);

		// Calculate the current phase within the cycle
		float current_time_in_cycle = fmod(base2->get_time_passed(), total_cycle_time);

		// Calculate swaying motion with wider arcs
		Quaternion y_rotation = Quaternion(
			Vector3(0, 1, 0),
			amplitude * sin(base2->get_time_passed() * Math_PI * 2.0) * rotation_speed
		);

		// Check phases
		if (current_time_in_cycle < move_duration) {
			base2->set_local_rotation(base2->get_local_rotation() * y_rotation);
		}
		else {
			head->set_local_rotation(head->get_local_rotation() * y_rotation);
		}

		// Update the global transform
		base2->set_global_transform(base2->get_transformation_matrix());
		head->set_global_transform(head->get_transformation_matrix());
	}

}

template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool Robo::create_and_add_as_child(T*& pointer, String name, bool search) {
	if (search == false) {
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}

	// always only have to search once if we save it here
	Node* child = find_child(name);

	if (child == nullptr) {
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}
	else {
		pointer = dynamic_cast<T*>(child);
		return false;
	}
}

void Robo::toggle_pause(bool paused) {
	is_paused = paused;
}