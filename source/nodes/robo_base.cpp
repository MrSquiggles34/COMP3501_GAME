#include "robo_base.h"

using namespace godot;

void RoboBase::_bind_methods() {
}

// You may not unset this class as top level (from parent)
RoboBase::RoboBase() : RoboPart() {
	// This is just to line them up for the starting scene -- change this for sure. 
	local_position = Vector3(-7.0f, 0.5f, -12.0f);
}

RoboBase::~RoboBase() {
	// Add cleanup here, if you have any. I don't, typically. 
}

void RoboBase::_enter_tree() {
	// Setup Base Geometry using CylinderMesh
	CylinderMesh* robo_base = memnew(CylinderMesh);
	robo_base->set_bottom_radius(3.0f);
	robo_base->set_top_radius(3.0f);
	robo_base->set_height(0.5f);

	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(1.0, 1.0, 0.4, 1));
	robo_base->surface_set_material(0, material);

	set_mesh(robo_base);
}

void RoboBase::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	set_global_transform(get_transformation_matrix());


}
