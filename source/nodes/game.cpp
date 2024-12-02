
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
    state = PLAY;
    is_paused = false;
    global_time_passed = 0.0;
}

Game::~Game() { }

void Game::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - Game.");

    create_and_add_as_child<Player>(this, player, "Player", true); 
    create_and_add_as_child<HUD>(this, hud, "HUD", true);
    create_and_add_as_child<CustomScene3501>(this, main_scene, "MainScene", true);
}

void Game::_ready() {
    UtilityFunctions::print("Game is ready.");
}

void Game::_process(double delta) {
    if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

    Input* _input = Input::get_singleton();

    // PAUSE THE GAME BY PAUSING THE SCENE WHICH PAUSES ALL RELEVANT OBJECTS 
    // ESC to toggle pause
    if (_input->is_action_just_pressed("pause_game")) {
        is_paused = !is_paused;
        if (state == PLAY){
            main_scene->toggle_pause(is_paused);
            player->toggle_pause(is_paused);
	        hud->toggle_pause_HUD();
        }
    }

    if(!is_paused){
        if (state == PLAY){
            // E to interact
            // Might go better elsewhere cause needs to check what it's actually interacting w/
            // Probably should be in player?
            if (_input->is_action_just_pressed("interact")) {
                if(DEBUG) UtilityFunctions::print("ACTION");
            }
            // J to open journal
            // I to open inventory (may or may not need both)
            if (_input->is_action_just_pressed("journal")) {
                state = JOURNAL;
                main_scene->toggle_pause(true);
                if(DEBUG) UtilityFunctions::print("OPEN JOURNAL");
            }
            if (_input->is_action_just_pressed("inventory")) {
                state = INV;
                main_scene->toggle_pause(true);
                if(DEBUG) UtilityFunctions::print("OPEN INVENTORY");
                UtilityFunctions::print(player->printInventory());
            }
        } else if (state == JOURNAL){
            if (_input->is_action_just_pressed("journal")) {
                state = PLAY;
                main_scene->toggle_pause(false);
                if(DEBUG) UtilityFunctions::print("CLOSE JOURNAL");
            }
            if (_input->is_action_just_pressed("inventory")) {
                state = INV;
                main_scene->toggle_pause(true);
                if(DEBUG) UtilityFunctions::print("OPEN INVENTORY");
                UtilityFunctions::print(player->printInventory());
            }
        } else if (state == INV){
            if (_input->is_action_just_pressed("journal")) {
                state = JOURNAL;
                main_scene->toggle_pause(true);
                if(DEBUG) UtilityFunctions::print("OPEN JOURNAL");
            }
            if (_input->is_action_just_pressed("inventory")) {
                state = PLAY;
                main_scene->toggle_pause(false);
                if(DEBUG) UtilityFunctions::print("CLOSE INVENTORY");
            }
        }
    }
}
