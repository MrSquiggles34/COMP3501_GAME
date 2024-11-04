
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>

#include "game.h"

#include "defs.h"
#include "create_and_add_as_child.h"

using namespace godot;

void Game::_bind_methods() {

}

Game::Game() : Node() {

    // Used for pausing and game loop.
    is_paused = false;
    global_time_passed = 0.0;
}

Game::~Game() { }

void Game::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - Game.");

    create_and_add_as_child<CustomScene3501>(this, main_scene, "MainScene", true);
}

void Game::_ready() {
    UtilityFunctions::print("Game is ready.");

    main_scene->_ready();
}

void Game::_process(double delta) {
    if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

    // PAUSE THE GAME BY PAUSING THE SCENE WHICH PAUSES ALL RELEVANT OBJECTS 
    Input* _input = Input::get_singleton();
    // Pause toggle with ESC key
    if (_input->is_action_just_pressed("pause_game")) {
        main_scene->toggle_pause();
    }
    
    // E to interact
    // J to open journal
    // I to open inventory (may or may not need both)
    if (_input->is_action_just_pressed("interact")) {
        if(DEBUG) UtilityFunctions::print("ACTION");
    }
    if (_input->is_action_just_pressed("journal")) {
        main_scene->toggle_pause();
        // Temporarily using pause, should eventually be its own check
        // ie. If game is not paused and journal is closed, pause and open journal
        // If game is paused and journal is closed, open journal
        // If game is paused and journal is open, unpause and close journal
        // Same for inventory (or whichever one we end up keeping)
        if(DEBUG) UtilityFunctions::print("OPEN JOURNAL");
    }
    if (_input->is_action_just_pressed("inventory")) {
        main_scene->toggle_pause();
        if(DEBUG) UtilityFunctions::print("OPEN INVENTORY");
    }

}


void Game::_pause() {
    is_paused = !is_paused;
}

bool Game::get_is_paused() const {
    return is_paused;
}

