
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

    page_1.append("Hmm. It seems that the rest of the data in this entry is corrupted.");
    page_1.append("This tabloid... It seems to be an excerpt from a scientist's journal.");
    page_1.append("Or rather a personal diary, judging from the informal grammar. Though I cannot ignore the possibility of him recording some of his research within these entries...");
    page_1.append("Perhaps I shouldn't be so quick to judge its importance. If only I could procure a few more...");
    
    second_page.append("Oh. Another tabloid. I was about to get bored.");
    second_page.append("... Perhaps boredom is too strong a word for this emotion. I am on a mission, after all.");
    second_page.append("Regardless, to find it in such an odd location... I wonder how it ended up here.");
    second_page.append("Corrupted again.");
    second_page.append("The data within these entries must be barely operational.");
    second_page.append("Not to mention, they seem to be totally out of order.");
    second_page.append("I wonder how much time has passed between the last one and this one.");
    second_page.append("... I am also beginning to wonder if there is any practical purpose for finding new tabloids.");
    second_page.append("I should focus on the mission. Though... I think I would not mind if I were to stumble across another tabloid.");
    
    page_4.append("This man seems to be experiencing the emotion called 'Grief' and 'Bloodlust'.");
    page_4.append("Although I have never processed such emotions before, these tabloids might provide me with an insight from someone who does.");
    page_4.append("From a more practical perspective... I do not see any use for storing such trivial information within my memory banks...");
    
    page_5.append("From what I know, it was extremely difficult to reach Aurelia. The information I have gathered only proves my initial assumption.");
    page_5.append("This made it impossible for the continent to govern Aurelia, which led it to becoming a self-governed state.");
    page_5.append("I always knew that there had to be a reason Aurelia was able to progress so much faster than the rest of the continent, but...");
    page_5.append("I should focus on the mission.");

    page_6.append("ERROR: MEMORY CONFLICT");
    page_6.append("Ow!");
    page_6.append("Huh?");
    page_6.append("What just happened?");
    page_6.append("Osiris... Why does that name sound familiar?");

    page_7.append("This project... It couldn’t be...");
    page_7.append("The White Panoply... Was there a reason I wasn’t told what was contained within it...?");
    page_7.append("ERROR: MEMORY CONFLICT");
    page_7.append("Gah!");
    page_7.append("And then there's these weird errors... This city is more than it appears to be.");
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
                } else if (progress_check == 3 && dialogNum == 3){
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
            } else if (progress_check == 3 && player->get_inventory_size() == 3){
                progress_check += 1;
                state = TEXT;
                player->toggle_pause(true);
                hud->toggle_dialog(true, second_page);
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
                } else if (progress_check == 2 && player->inInventory("Page0")){
                    read_pages.append(1);
                    progress_check += 1;
                    state = TEXT;
                    player->toggle_pause(true);
                    hud->toggle_dialog(true, page_1);
                } else if (progress_check == 4){
                    progress_check += 1;
                    state = TEXT;
                    player->toggle_pause(true);
                    hud->toggle_dialog(true);
                } else if (read_pages.find(4) && player->inInventory("Page3")){
                    state = TEXT;
                    read_pages.append(4);
                    player->toggle_pause(true);
                    hud->toggle_dialog(true, page_4);
                }
            }
        }
    }
}
