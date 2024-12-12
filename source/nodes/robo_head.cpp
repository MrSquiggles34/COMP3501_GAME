#include "robo_head.h"

using namespace godot;

void RoboHead::_bind_methods() {
}

// You may not unset this class as top level (from parent)
RoboHead::RoboHead() : RoboPart() {
	// This is just to line them up for the starting scene -- change this for sure. 
	local_position = Vector3(0.0f, 0.0f, 0.0f);
}

RoboHead::~RoboHead() {
	// Add cleanup here, if you have any. I don't, typically. 
}

void RoboHead::_enter_tree() {
	// Setup Head Geometry using CylinderMesh
	SphereMesh* head = memnew(SphereMesh);
	head->set_radius(1.0f);

	ShaderMaterial* material = memnew(ShaderMaterial());
	head->surface_set_material(0, material);

	Ref<Shader> shader = ResourceLoader::get_singleton()->load(vformat("%s%s.gdshader", "shaders/", "lighting"), "Shader");
	material->set_shader(shader);
	head->surface_set_material(0, material);

	set_mesh(head);
	material->set_shader_parameter("color_in", Color(0.0, 0.0, 0.0, 1));
	material->set_shader_parameter("light_position", Vector3(0.0f, 100.0f, -140.0f));
	material->set_shader_parameter("specular_power", 50.0f);
}

void RoboHead::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

}
