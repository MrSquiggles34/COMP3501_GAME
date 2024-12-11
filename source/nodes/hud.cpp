#include "hud.h"
#include "create_and_add_as_child.h"
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

void HUD::_bind_methods() { }

HUD::HUD() : CanvasLayer() {}

HUD::~HUD() {}

void HUD::_enter_tree() {
    if (DEBUG) UtilityFunctions::print("Enter Tree - HUD.");
    create_and_add_as_child<Label>(this, pause_label, "PauseLabel", true);
    create_and_add_as_child<ItemList>(this, inventory, "Inventory", true);
    create_and_add_as_child<ColorRect>(this, textBox, "TextBox", true);
    create_and_add_as_child<Label>(this, dialog_label, "Dialog", true);
    create_and_add_as_child<TextureRect>(this, title_screen, "TitleCard", true);

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
    inventory->set_size(get_viewport()->get_visible_rect().size);
    inventory->set_max_columns(10);
    inventory->set_fixed_icon_size(Vector2i(100, 100));
    inventory->set_icon_mode(ItemList::IconMode::ICON_MODE_TOP);
    inventory->set_visible(false);

    // DIALOG BOX
    int width = get_viewport()->get_visible_rect().size.x-10;
    int height = get_viewport()->get_visible_rect().size.y/3;
    textBox->set_size(Vector2(width, height));
    textBox->set_position(Vector2(5,height*2-5));
    textBox->set_color(Color(0,0,0,1));

    dialog_label->set_size(Vector2(width-8, height));
    dialog_label->set_autowrap_mode(TextServer::AutowrapMode::AUTOWRAP_WORD_SMART);
    dialog_label->set_text(dialog_list[0]);
    dialog_label->set("theme_override_colors/font_color", Color(1,1,1,1));
    dialog_label->set("theme_override_font_sizes/font_size", 25);
    dialog_label->set_position(Vector2(20,height*2+10));
    //dialog_label->set_visible(false);

}

void HUD::toggle_pause_HUD() {
    if (pause_label) {
        bool is_visible = pause_label->is_visible();
        pause_label->set_visible(!is_visible);
    }
}

void HUD::toggle_inventory(bool is_inv, Player* player) {
    inventory->clear();
    Vector<CollectableItemAbstract*> player_inv = player->get_inventory();
    for (int i=0; i<player_inv.size(); i++){
        int index = inventory->add_item(player_inv[i]->get_name(), player_inv[i]->get_icon());
        UtilityFunctions::print(player_inv[i]->get_name());
        inventory->set_item_tooltip(index, player_inv[i]->get_lore());
    }
    inventory->set_visible(is_inv);
}

void HUD::start_game(){
    title_screen->set_visible(false);
}

void HUD::toggle_dialog(bool is_vis){
    textBox->set_visible(is_vis);
    dialog_label->set_visible(is_vis);
}

int HUD::nextDialog(){
    cur_dialog += 1;
    if (cur_dialog == 0 || cur_dialog == 2 || cur_dialog == 3 || cur_dialog == 5 || cur_dialog == 6 || cur_dialog == 7 || cur_dialog == 9 || cur_dialog == 11 || cur_dialog == 12){
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
