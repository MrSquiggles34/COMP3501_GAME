#include "robo_joint.h"

using namespace godot;

void RoboJoint::_bind_methods() {
}

// You may not unset this class as top level (from parent)
RoboJoint::RoboJoint() : RoboPart() {
	// This is just to line them up for the starting scene -- change this for sure. 
	local_position = Vector3(0.0f, 0.0f, 0.0f);
}

RoboJoint::~RoboJoint() {
	// Add cleanup here, if you have any. I don't, typically. 
}

void RoboJoint::_enter_tree() {
	if (DEBUG) UtilityFunctions::print("Enter Tree - RoboJoint");

	// Setup Base Geometry using BoxMesh
	BoxMesh* robo_joint = memnew(BoxMesh);
	robo_joint->set_size(Vector3(1.0f, 1.5f, 0.5f));

	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(0.0, 0.0, 0.0, 1));
	robo_joint->surface_set_material(0, material);

	set_mesh(robo_joint);
}

void RoboJoint::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	set_global_transform(get_transformation_matrix());
}
