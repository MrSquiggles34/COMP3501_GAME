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
	// Setup Base Geometry using BoxMesh
	BoxMesh* robo_joint = memnew(BoxMesh);
	robo_joint->set_size(Vector3(1.0f, 1.5f, 0.5f));

	ShaderMaterial* material = memnew(ShaderMaterial());
	robo_joint->surface_set_material(0, material);

	Ref<Shader> shader = ResourceLoader::get_singleton()->load(vformat("%s%s.gdshader", "shaders/", "lighting"), "Shader");
	material->set_shader(shader);
	robo_joint->surface_set_material(0, material);

	set_mesh(robo_joint);
	material->set_shader_parameter("color_in", Color(0.0, 0.0, 0.0, 1));
	material->set_shader_parameter("light_position", Vector3(0.0f, 100.0f, -140.0f));
	material->set_shader_parameter("specular_power", 50.0f);
}

void RoboJoint::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	set_global_transform(get_transformation_matrix());
}
