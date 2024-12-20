#include "hud.h"
#include "create_and_add_as_child.h"
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

void HUD::_bind_methods() { }

HUD::HUD() : CanvasLayer() {}

HUD::~HUD() {}

void HUD::_enter_tree() {
    create_and_add_as_child<Label>(this, pause_label, "PauseLabel", true);
    
    create_and_add_as_child<ItemList>(this, inventory, "Inventory", true);
    create_and_add_as_child<ColorRect>(this, dataBox, "DataBox", true);
    create_and_add_as_child<Label>(this, data_label, "Data", true);

    create_and_add_as_child<ColorRect>(this, textBox, "TextBox", true);
    create_and_add_as_child<Label>(this, dialog_label, "Dialog", true);

    create_and_add_as_child<TextureRect>(this, title_screen, "TitleCard", true);
    create_and_add_as_child<ColorRect>(this, endScreen, "EndScreen", true);
    create_and_add_as_child<Label>(this, end_text, "End Text", true);

    is_intro = true;
    cur_dialog = 0;
    dialog_list.append("HQ: *BZZT* #255, come in. This is Agent *KRRSHH* from mission control speaking. #255, do you copy?");
    dialog_list.append("Y-yeah. I can hear you, but the connection isn't great. There seems to be a snowstorm going on.");
    dialog_list.append("HQ: That's unfortunate but there's no... we can do now. We'll have to ... on with the mission at hand.");
    dialog_list.append("HQ: I'm going ... run you through a quick diagnostic. Look around. Is there any... that you can pick up?");
    dialog_list.append("Uhhh, yes. There's a battery on the ground.");
    dialog_list.append("HQ: Perfect. Please walk over and retrieve it.");
    dialog_list.append("HQ: Excellent. Now press [I] to ... Analysis Mode and focus on the battery to test your scanner.");
    dialog_list.append("HQ: Everything appears ... in order. Now you are... explore Aurelia... careful...");
    dialog_list.append("Sorry, what was that? You're cutting out again. I'm having trouble understanding what you're saying?");
    dialog_list.append("HQ: ... Signal ... Can't ... Mission");
    dialog_list.append("I can't hear you! The storm is getting worse!");
    dialog_list.append("HQ: Remember ... Imperative that ... Wrong hands");
    dialog_list.append("*KRZZT*");
    dialog_list.append("Hello? Hello?");
    dialog_list.append("...");
    dialog_list.append("Well, I guess I'll just have to hope this storm blows over soon. In the meantime, I may as well get moving. I still have my initial directives after all. Analyze the current state of Aurelia and retrieve the White Panoply... I just wish they'd told me what exactly that is.");

}

void HUD::_ready() {

    Vector2 screen_size = get_viewport()->get_visible_rect().size;
    screen_size = screen_size / 2;

    // START SCREEN
    Ref<Texture2D> title_image = ResourceLoader::get_singleton()->load("res://textures/Title_Screen.png");
    title_screen->set_expand_mode(TextureRect::ExpandMode::EXPAND_IGNORE_SIZE);
    title_screen->set_size(get_viewport()->get_visible_rect().size);
    title_screen->set_texture(title_image);

    // PAUSE LABEL
    pause_label->set_text("PAUSE");
    pause_label->set("theme_override_colors/font_color", Color(1,1,1,1));
    pause_label->set("theme_override_constants/outline_size", 5);
    pause_label->set("theme_override_font_sizes/font_size", 50);
    pause_label->set("theme_override_colors/font_outline_color", Color(0,0,0,1));
    pause_label->set_position(screen_size - pause_label->get_minimum_size() / 2);
    pause_label->set_visible(false);

    // INVENTORY
    int width = get_viewport()->get_visible_rect().size.x/2;
    int height = get_viewport()->get_visible_rect().size.y;
    inventory->set_size(Vector2(width,height));
    inventory->set_max_columns(5);
    inventory->set_fixed_icon_size(Vector2i(100, 100));
    inventory->set_icon_mode(ItemList::IconMode::ICON_MODE_TOP);
    inventory->set_allow_reselect(true);
    inventory->set_visible(false);

    dataBox->set_size(Vector2(width, height));
    dataBox->set_position(Vector2(width,0));
    dataBox->set_color(Color(0,0,0,1));
    dataBox->set_visible(false);

    data_label->set_size(Vector2(width-8, height));
    data_label->set_autowrap_mode(TextServer::AutowrapMode::AUTOWRAP_WORD_SMART);
    data_label->set_text("ANALYZING...");
    data_label->set("theme_override_colors/font_color", Color(0,0.8,0.15,1));
    data_label->set("theme_override_font_sizes/font_size", 20);
    data_label->set_position(Vector2(width+10,10));
    data_label->set_visible(false);

    // DIALOG BOX
    width = get_viewport()->get_visible_rect().size.x-10;
    height = get_viewport()->get_visible_rect().size.y/3;
    textBox->set_size(Vector2(width, height));
    textBox->set_position(Vector2(5,height*2-5));
    textBox->set_color(Color(0,0,0,1));

    dialog_label->set_size(Vector2(width-8, height));
    dialog_label->set_autowrap_mode(TextServer::AutowrapMode::AUTOWRAP_WORD_SMART);
    dialog_label->set_text(dialog_list[0]);
    dialog_label->set("theme_override_colors/font_color", Color(1,1,1,1));
    dialog_label->set("theme_override_font_sizes/font_size", 25);
    dialog_label->set_position(Vector2(20,height*2+10));

    // END SCREEN
    endScreen->set_size(get_viewport()->get_visible_rect().size);
    endScreen->set_color(Color(0,0,0,1));
    endScreen->set_visible(false);

    width = get_viewport()->get_visible_rect().size.x-10;
    height = get_viewport()->get_visible_rect().size.y-10;
    end_text->set_size(Vector2(width, height));
    end_text->set_autowrap_mode(TextServer::AutowrapMode::AUTOWRAP_WORD_SMART);
    end_text->set("theme_override_colors/font_color", Color(1,1,1,1));
    end_text->set("theme_override_font_sizes/font_size", 20);
    end_text->set_position(Vector2(10,10));
    end_text->set_visible(false);

}

void HUD::_process(double delta){
    int num_selected = inventory->get_selected_items().size() - 1;
    if(num_selected >= 0){
        int cur_selected = inventory->get_selected_items()[num_selected];
        data_label->set_text(inventory_data[cur_selected]);
    }
}

void HUD::toggle_pause_HUD() {
    if (pause_label) {
        bool is_visible = pause_label->is_visible();
        pause_label->set_visible(!is_visible);
    }
}

void HUD::toggle_inventory(bool is_inv, Player* player) {
    inventory_data.clear();
    inventory->clear();
    Vector<CollectableItemAbstract*> player_inv = player->get_inventory();
    for (int i=0; i<player_inv.size(); i++){
        int index = inventory->add_item(player_inv[i]->get_name(), player_inv[i]->get_icon());
        UtilityFunctions::print(player_inv[i]->get_name());
        inventory_data.append(player_inv[i]->get_lore());
    }
    inventory->set_visible(is_inv);
    dataBox->set_visible(is_inv);
    data_label->set_visible(is_inv);

    if (is_inv){
        data_label->set_text("ANALYZING...");
    }
}

void HUD::start_game(){
    title_screen->set_visible(false);
}

void HUD::end_game(bool completed){
    endScreen->set_visible(true);
    if(completed){
        end_text->set_text("#255 Retrieves the Panoply from the tower, its surface glowing a faint white hue\nUpon making contact with their hand, the walls of the device falls open, and #255's head is filled with information.\nHowever, nothing concrete takes shape, their mind overwhelmed with the surge of new information, #255 chooses to ignore it and follow the instructions he had received prior to arriving at Aurelia\nThey leave the island, and their comms spring back to life, receiving a signal from his leader requesting an update.\nWith no reason to linger in the dilate land of Aurelia, #255 complies with all of the orders he is given.\nAs a transport vehicle arrives to escort #255 away, the island vanishes beneath the clouds, its secrets lost to time forevermore.\nThe Panoply rests in #255's hands, its mysteries left unknown as the city is left behind…\nYou have escaped Aurelia… But some truths remain lost. Perhaps try collecting all 10 of the tabloids next time.");
    } else {
        end_text->set_text("#255 retrieves the Panoply from the tower, its surface glowing a faint white hue.\nTheir hands tremble as they touch the device, watching its walls fall open.\n#255's head is filled with information, their mind flooded with memories- no, truths.\nThe scientist's voice echoes in their mind, the information from all the tabloid entries are starting to make so much sense.\nYou are Osiris, my greatest creation! [Italics if possible]\n#255 now understands why the name Osiris sounded so familiar, and why Aurelia seemed like such a familiar place to them.\nThe Panoply contains much information: The destruction of Aurelia was not an accident, the rest of the continent had feared the implications of #255's existence, as well as the potential of Aurelia weaponizing the technology used to create him.\n#255's creator, consumed by grief and thirst to repay blood with blood, had ensured that #255 alone would survive- even if it was at the cost of the rest of Aurelia.\n#255 leaves the island, and their comms spring back to life, receiving a signal from his leader requesting an update.\nA choice now looms before them: What will they do with the truth? ");
    }
    end_text->set_visible(true);
}

void HUD::toggle_dialog(bool is_vis){
    textBox->set_visible(is_vis);
    dialog_label->set_visible(is_vis);
}

void HUD::toggle_dialog(bool is_vis, Vector<String> dialog){
    dialog_list = dialog;
    cur_dialog = 0;
    is_intro = false;
    dialog_label->set_text(dialog_list[cur_dialog]);
    textBox->set_visible(is_vis);
    dialog_label->set_visible(is_vis);
}

int HUD::nextDialog(){
    cur_dialog += 1;
    if(is_intro){
        if (cur_dialog == 0 || cur_dialog == 2 || cur_dialog == 3 || cur_dialog == 5 || cur_dialog == 6 || cur_dialog == 7 || cur_dialog == 9 || cur_dialog == 11 || cur_dialog == 12){
            textBox->set_color(Color(0,0,0,1));
            dialog_label->set("theme_override_colors/font_color", Color(1,1,1,1));
        } else {
            textBox->set_color(Color(0.5,0.8,1,1));
            dialog_label->set("theme_override_colors/font_color", Color(0,0,0,1));
        }
    } else if (dialog_list[cur_dialog] == "ERROR: MEMORY CONFLICT") {
        textBox->set_color(Color(0,0,0,1));
        dialog_label->set("theme_override_colors/font_color", Color(1,1,1,1));
    } else {
        textBox->set_color(Color(0.5,0.8,1,1));
        dialog_label->set("theme_override_colors/font_color", Color(0,0,0,1));
    }

    if (cur_dialog < dialog_list.size()){
        dialog_label->set_text(dialog_list[cur_dialog]);
        return cur_dialog;
    } else {
        return -1;
    }
}
