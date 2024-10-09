#ifndef CREATE_AND_ADD_AS_CHILD_H
#define CREATE_AND_ADD_AS_CHILD_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

namespace godot {

    template <class T>
    bool create_and_add_as_child(Node* parent, T*& pointer, String name, bool search = false) {
        if (search == false) {
            pointer = memnew(T);
            pointer->set_name(name);
            parent->add_child(pointer);
            pointer->set_owner(parent->get_tree()->get_edited_scene_root());
            return true;
        }

        Node* child = parent->find_child(name);
        if (child == nullptr) {
            pointer = memnew(T);
            pointer->set_name(name);
            parent->add_child(pointer);
            pointer->set_owner(parent->get_tree()->get_edited_scene_root());
            return true;
        }
        else {
            pointer = dynamic_cast<T*>(child);
            return false;
        }
    }

}

#endif // CREATE_AND_ADD_AS_CHILD_H
