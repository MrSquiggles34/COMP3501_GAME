#include "custom_mesh.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/core/object.hpp> // for memnew

using namespace godot;

void CustomMesh::_bind_methods() {
}

CustomMesh::CustomMesh() : MeshInstance3D() {
	time_passed = 0.0;

	// default values
	shader_name = "simple.gdshader";
	base_color = Vector3(); // black

	shader_material = nullptr;
 }

CustomMesh::~CustomMesh() {
	// Add your cleanup here (if any is needed)
}

void CustomMesh::_enter_tree ( ){
	if(DEBUG) UtilityFunctions::print("Enter Tree - ", get_name()); 

}

// Note: This section runs every time we open the game again. For a small game like what we will make for this assignment, it will be fine. If you want to refactor to make it load from saved data instead, you can, but it likely won't be a good use of your time. 
void CustomMesh::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - ", get_name()); 

	// NOTE: this section needs to run after the parent node's _enter_tree (consistently) and before the parent's _ready; making this the perfect place to put it.

	// They don't HAVE to be tori; they don't all HAVE to be the same. You can change the geometry as much as you want -- it is just a canvas to display your shaders for the purposes of this assignment.
	// That being said, your shaders should work regardless of the shape.
	TorusMesh* mesh = memnew(TorusMesh()); 
	shader_material = memnew(ShaderMaterial());
	Ref<Shader> shader = ResourceLoader::get_singleton()->load(shader_name, "Shader");
	shader_material->set_shader(shader);
	mesh->surface_set_material(0, shader_material);
	set_mesh(mesh);
	// This line sends the uniform to the shader material.
	shader_material->set_shader_parameter("color_in", base_color);
}

// called every frame (as often as possible)
void CustomMesh::_process(double delta) {
	time_passed += delta;
}

void CustomMesh::set_texture(String name){
	ResourceLoader* resource_loader = ResourceLoader::get_singleton();
	Ref<Texture> _texture = resource_loader->load(name);

	if(shader_material != nullptr) shader_material->set_shader_parameter("texture_1", _texture);
}

void CustomMesh::set_texture_from_data(PackedFloat32Array* data_array){
	Ref<Image> image = Image::create_from_data(NOISE_WIDTH, NOISE_HEIGHT, false, Image::FORMAT_RGBAF, data_array->to_byte_array());
	Ref<ImageTexture> _texture = ImageTexture::create_from_image(image);
	
	if(shader_material != nullptr) shader_material->set_shader_parameter("texture_1", _texture);
}

void CustomMesh::set_base_color(Vector3 color){
	base_color = color;
	if(shader_material != nullptr) shader_material->set_shader_parameter("color_in", base_color);
}

