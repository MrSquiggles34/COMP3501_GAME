
#include "game.h"

#include "defs.h"
#include "create_and_add_as_child.h"

using namespace godot;

void Game::_bind_methods() {

}

Game::Game() : Node() {

    // Used for pausing and game loop.
    state = START;
    is_paused = false;
    global_time_passed = 0.0;
    progress_check = 0;
    picked_up_first_item = false;
    checked_first_item = false;
}

Game::~Game() { }

void Game::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - Game.");

    create_and_add_as_child<Player>(this, player, "Player", true); 
    create_and_add_as_child<HUD>(this, hud, "HUD", true);
    create_and_add_as_child<CustomScene3501>(this, main_scene, "MainScene", true);
    main_scene->addPlayer(player);
}

void Game::_ready() {
    UtilityFunctions::print("Game is ready.");
    player->toggle_pause(true);
}

void Game::_input(const Ref<InputEvent>& event) {
	if (state == START) {
        Ref<InputEventMouseButton> mouse_event = event;
        if (mouse_event.is_valid()) {
            if (mouse_event->get_button_index() == MouseButton::MOUSE_BUTTON_LEFT) {
                float mouse_x = mouse_event->get_position().x;
                float mouse_y = mouse_event->get_position().y;

                Vector2 screen_size = get_viewport()->get_visible_rect().size;
                float x_lim = screen_size.x / 5;
                float y_lim = screen_size.y / 5;

                if(mouse_x > x_lim*2 && x_lim*3 > mouse_x && mouse_y > y_lim*3 && y_lim*4 > mouse_y){
                    state = TEXT;
                    hud->start_game();
                }
            }
        }
    }
}

void Game::_process(double delta) {
    if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

    Input* _input = Input::get_singleton();

    // PAUSE THE GAME BY PAUSING THE SCENE WHICH PAUSES ALL RELEVANT OBJECTS 
    // ESC to toggle pause
    if (state != START && state != END){
        if (_input->is_action_just_pressed("pause_game")) {
            is_paused = !is_paused;
            if (state == PLAY){
                main_scene->toggle_pause(is_paused);
                player->toggle_pause(is_paused);
                hud->toggle_pause_HUD();
            } else if (state == TEXT){
                hud->toggle_pause_HUD();
                hud->toggle_dialog(!is_paused);
            }
        }
    }

    if(!is_paused){
        if (state == TEXT){
            if (_input->is_action_just_pressed("advance_dialog")) {
                int dialogNum = hud->nextDialog();
                if(dialogNum == -1 || dialogNum == 6 || dialogNum == 7){
                    hud->toggle_dialog(false);
                    player->toggle_pause(false);
                    state = PLAY;
                }
            }
        } else if (state == PLAY){
            if(progress_check == 0){
                if (player->inInventory("Battery")){
                    progress_check += 1;
                    state = TEXT;
                    player->toggle_pause(true);
                    hud->toggle_dialog(true);
                }
            }
            // I to open inventory
            if (_input->is_action_just_pressed("inventory")) {
                state = INV;
                player->toggle_pause(true);
                hud->toggle_inventory(true, player);
                if(DEBUG) UtilityFunctions::print("OPEN INVENTORY");
            }
        } else if (state == INV){
            if (_input->is_action_just_pressed("inventory")) {
                state = PLAY;
                hud->toggle_inventory(false, player);
                player->toggle_pause(false);
                if(DEBUG) UtilityFunctions::print("CLOSE INVENTORY");
                if(progress_check == 1){
                    progress_check += 1;
                    state = TEXT;
                    player->toggle_pause(true);
                    hud->toggle_dialog(true);
                }
            }
        }
    }
}
