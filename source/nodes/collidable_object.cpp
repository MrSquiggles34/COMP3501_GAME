#include "defs.h"
#include "collidable_object.h"
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void CollidableObject::_bind_methods() {}

CollidableObject::CollidableObject() : StaticBody3D() {}

CollidableObject::~CollidableObject() {}

void CollidableObject::_enter_tree() {
    if(DEBUG) UtilityFunctions::print("Enter Tree - Collidable Object."); 

    // The player has a child CylinderMesh
    create_and_add_as_child<Node3D>(this, model, "Model", true);

    // The player has a child CollisionShape3D
    create_and_add_as_child<CollisionShape3D>(this, collision_shape, "CollisionShape", true);    

    // Set the Model
    set_model("res://models/sci-fi_building.glb");

    // Set the Collision Shape
    set_collision_shape("capsule");
}

void CollidableObject::_ready() {
    if(DEBUG) UtilityFunctions::print("Ready - Collidable Object."); 
}

void CollidableObject::set_collision_shape(String shape) {
    if (shape == "capsule") {
        Ref<CapsuleShape3D> capsule_shape = memnew(CapsuleShape3D);
        capsule_shape->set_radius(0.5f);
        capsule_shape->set_height(2.0f);
        collision_shape->set_shape(capsule_shape);
    } else if (shape == "cylinder") {
        Ref<CylinderShape3D> cylinder_shape = memnew(CylinderShape3D);
        cylinder_shape->set_radius(0.5f);
        cylinder_shape->set_height(1.0f);
        collision_shape->set_shape(cylinder_shape);
    } else if (shape == "box") {
        Ref<BoxShape3D> box_shape = memnew(BoxShape3D);
        box_shape->set_size(Vector3(0.5, 0.5, 0.5));
        collision_shape->set_shape(box_shape);
    }
    else {
        if(DEBUG) UtilityFunctions::print("Invalid shape for CollidableObject.");
    } 
}

void CollidableObject::set_model(String model_path) {
    // Load the scene resource from the given path
    Ref<PackedScene> scene = ResourceLoader::get_singleton()->load(model_path);

    // Check if the resource was successfully loaded
    if (!scene.is_valid()) {
        if (DEBUG) UtilityFunctions::print("Failed to load model at: ", model_path);
        return;
    }

    // Instance the scene as a Node3D
    Node3D *model_instance = Object::cast_to<Node3D>(scene->instantiate());
    if (!model_instance) {
        if (DEBUG) UtilityFunctions::print("Failed to cast loaded scene to Node3D.");
        return;
    }

    // Remove the existing child model if any
    if (model && model->get_parent() == this) {
        remove_child(model);
        model->queue_free();
    }

    // Set the new model
    model = model_instance;
    add_child(model);
}

Node3D* CollidableObject::get_model() {
    return model;
}

CollisionShape3D* CollidableObject::get_collision_shape() {
    return collision_shape;
}