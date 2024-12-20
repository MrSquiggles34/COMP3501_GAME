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
	base_color = Vector3(); 

	shader_material = nullptr;

 }

CustomMesh::~CustomMesh() {
	// Add your cleanup here (if any is needed)
}

void CustomMesh::_enter_tree ( ){

}

void CustomMesh::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - ", get_name()); 


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

