#include "game.h"


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

    if (is_paused) return;
}







void Game::_pause() {
    is_paused = !is_paused;
}

bool Game::get_is_paused() const {
    return is_paused;
}

