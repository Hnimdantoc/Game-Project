#include "Scenes.hpp"
#include <fstream>
/********************************************************************************/
Menu* Menu::static_instance = nullptr;
Menu::Menu() : ID(MENU_SCENE) {        
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;
    ChoosingMode = false;

    merchantIdle.SetProp("samurai_merchant", 1, 4, 150);

    font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 200);
    TextureManager::GetInstance()->CreateTextureFromText(&Play, font, "PLAY", {255, 255, 255});
    MakeRectFromTexture(&Play, &play_rect, 790, 150);
    TTF_CloseFont(font);

    font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 160);

    TextureManager::GetInstance()->CreateTextureFromText(&Option, font, "OPTION", {255, 255, 255});
    MakeRectFromTexture(&Option, &option_rect, 750, 460);

    TextureManager::GetInstance()->CreateTextureFromText(&Exit, font, "EXIT", {255, 255, 255});
    MakeRectFromTexture(&Exit, &exit_rect, 910, 565);
    TTF_CloseFont(font);

    font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 100);

    TextureManager::GetInstance()->CreateTextureFromText(&Mode_1, font, "Single", {255, 255, 255});
    MakeRectFromTexture(&Mode_1, &mode_1_rect, 858, 290);

    TextureManager::GetInstance()->CreateTextureFromText(&Mode_2, font, "Co op", {255, 255, 255});
    MakeRectFromTexture(&Mode_2, &mode_2_rect, 880, 384);
    currentRect = &play_rect;
    vectorRect.push_back({&play_rect, &option_rect, &exit_rect});
    vectorRect.push_back({&mode_1_rect, &mode_2_rect});
}
Menu::~Menu(){
    TTF_CloseFont(font);
    SDL_DestroyTexture(Play);
    SDL_DestroyTexture(Option);
    SDL_DestroyTexture(Exit);
    SDL_DestroyTexture(Mode_1);
    SDL_DestroyTexture(Mode_2);
}
void Menu::Update(float& dt){
    if ((!tutoring && mouse_x >= 206 && mouse_x <= 239 && mouse_y >= 543 && mouse_y <= 581)) tutoring = true;
    else if (tutoring && mouse_x<206 || mouse_x > 977 || mouse_y < 14 || mouse_y > 652) tutoring = false;
    merchantIdle.Update(dt);
    GameObjectHandler::GetInstance()->Update(dt);
}

void Menu::Render(){
    TextureManager::GetInstance()->Render("menu_background", 0, 0, WIDTH, HEIGHT);
    merchantIdle.Render(190, 531, 78, 50, 1);
    TTF_CloseFont(font);
    SDL_DestroyTexture(Play);
    SDL_DestroyTexture(Option);
    SDL_DestroyTexture(Exit);
    SDL_DestroyTexture(Mode_1);
    SDL_DestroyTexture(Mode_2);
    ////
    font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 200);
    TextureManager::GetInstance()->CreateTextureFromText(&Play, font, "PLAY", {79, 83, 86});
    TTF_CloseFont(font);

    font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 160);
    TextureManager::GetInstance()->CreateTextureFromText(&Option, font, "OPTION", {79, 83, 86});
    TextureManager::GetInstance()->CreateTextureFromText(&Exit, font, "EXIT", {79, 83, 86});
    TTF_CloseFont(font);
    font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 100);
    TextureManager::GetInstance()->CreateTextureFromText(&Mode_1, font, "Single", {79, 83, 86});
    
    TextureManager::GetInstance()->CreateTextureFromText(&Mode_2, font, "Co op", {79, 83, 86});
    TTF_CloseFont(font);
    if (currentRect == &play_rect){
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 200);
        SDL_DestroyTexture(Play);
        TextureManager::GetInstance()->CreateTextureFromText(&Play, font, "PLAY", {26, 72, 86});
    }
    else if (currentRect == &option_rect){
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 160);
        SDL_DestroyTexture(Option);
        TextureManager::GetInstance()->CreateTextureFromText(&Option, font, "Option", {26, 72, 86});
    }
    else if (currentRect == &exit_rect){
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 160);
        SDL_DestroyTexture(Exit);
        TextureManager::GetInstance()->CreateTextureFromText(&Exit, font, "Exit", {26, 72, 86});
    }
    else if (currentRect == &mode_1_rect){
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 100);
        SDL_DestroyTexture(Mode_1);
        TextureManager::GetInstance()->CreateTextureFromText(&Mode_1, font, "Single", {26, 72, 86});
    }
    else if (currentRect == &mode_2_rect){
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 100);
        SDL_DestroyTexture(Mode_2);
        TextureManager::GetInstance()->CreateTextureFromText(&Mode_2, font, "Co op", {26, 72, 86});
    }
    ///
    TextureManager::GetInstance()->Render("ball", currentRect->x-95, currentRect->y + 64/2, 64, 95);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Play, nullptr, &play_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Option, nullptr, &option_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Exit, nullptr, &exit_rect);
    if (ChoosingMode){
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Mode_1, nullptr, &mode_1_rect);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Mode_2, nullptr, &mode_2_rect);
    }
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), currentRect);
    if (tutoring) TextureManager::GetInstance()->Render("tutor", 0, 0, WIDTH, HEIGHT);
}

void Menu::KeyDown(SDL_Scancode scancode){
    if (tutoring) return;
    switch(scancode){
        case SDL_SCANCODE_DOWN:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            j++;
            if (j == vectorRect[i].size()) j = 0;
            currentRect = vectorRect[i][j];
            break;
        case SDL_SCANCODE_UP:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            j--;
            if (j < 0) j = vectorRect[i].size()-1;
            currentRect = vectorRect[i][j];
            break;
        case SDL_SCANCODE_RETURN:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            if (!ChoosingMode){
                if (currentRect == &play_rect) {
                    ChoosingMode = true;
                    i++;
                    currentRect = &mode_1_rect;
                }
                else if (Menu::GetInstance()->currentRect == &option_rect) SceneManager::GetInstance()->ChangeScene(OPTION_SCENE);
                else if (Menu::GetInstance()->currentRect == &exit_rect) Engine::GetInstance()->setGameState() = GAME_STATE::EXIT;
                return;
            }
            if (currentRect == &mode_1_rect) mode_2 = false;
            else mode_2 = true;
            SceneManager::GetInstance()->ChangeScene(SELECT_SCENE);
            break;
        case SDL_SCANCODE_ESCAPE:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            if (ChoosingMode) {
                ChoosingMode = false;
                i--;
                j = 0;
                currentRect = &play_rect;
            }
            break;
    }
}

void Menu::KeyUp(SDL_Scancode scancode){

}
/********************************************************************************/

Option* Option::static_instance = nullptr;
Option::Option() : ID(OPTION_SCENE) {
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;
}

Option::~Option(){}

void Option::Update(float& dt){}

void Option::Render(){
    TextureManager::GetInstance()->Render("option", 0, 0, WIDTH, HEIGHT);
    TextureManager::GetInstance()->Render("volume", setCoord[oldVolume-1][0], setCoord[oldVolume-1][1], 35, 35);
    if (currentVolume != oldVolume) TextureManager::GetInstance()->Render("volume1", setCoord[currentVolume-1][0], setCoord[currentVolume-1][1], 35, 35);
}

void Option::KeyDown(SDL_Scancode scancode){
    switch(scancode){
        case SDL_SCANCODE_RIGHT:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            currentVolume++;
            if (currentVolume == 6) currentVolume = 1;
            break;
        case SDL_SCANCODE_LEFT:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            currentVolume--;
            if (currentVolume == 0) currentVolume = 5;
            break;
        case SDL_SCANCODE_RETURN:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            oldVolume = currentVolume;
            Mixer::GetInstance()->SetVolume((currentVolume-1)*25);
            break;
        case SDL_SCANCODE_ESCAPE:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
            break;        
    }
}

void Option::KeyUp(SDL_Scancode scancode){}

/********************************************************************************/
Select* Select::static_instance = nullptr;
Select::Select() : ID(SELECT_SCENE){
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;

    font = TextureManager::GetInstance()->LoadFont("res/Fonts/mono.ttf", 60);
    if (Menu::GetInstance()->mode_2) mode = 2;
    else mode = 1;
    skin_has_been_selected = false;
    skin1_has_been_selected = false;
    minute_per_sun = 30;
    TextureManager::GetInstance()->CreateTextureFromText(&fifteen, font, "hard", {0, 0, 0, 255});
    TextureManager::GetInstance()->CreateTextureFromText(&thirty, font, "medium", {0, 0, 0, 255});
    selected_minutes = thirty;
    TextureManager::GetInstance()->CreateTextureFromText(&forty_five, font, "easy", {0, 0, 0, 255});
    player_name = nullptr;
    player1_name = nullptr;
    player_idle.SetProp("player", 0, 4, 150);
    player1_idle.SetProp("player", 0, 4, 150);
    minute_box.x = 600;
    minute_box.y = 10;
    top_cursor.SetProp("top_cursor", 0, 9, 100);
    left_cursor.SetProp("left_cursor", 0, 1, 100);
    right_cursor.SetProp("right_cursor", 0, 1, 100);
    heart.SetProp("heart", 0, 1, 100);
    rotate_1.SetProp("rotate_1", 0, 1, 100);
    rotate_2.SetProp("rotate_2", 0, 1, 100);
    rotate_3.SetProp("rotate_3", 0, 1, 100);
    SDL_QueryTexture(thirty, nullptr, nullptr, &minute_box.w, &minute_box.h);
    bg = (mode == 1) ? "select_1" : "select_2";
    vectorMinute.push_back(fifteen);
    vectorMinute.push_back(thirty);
    vectorMinute.push_back(forty_five);
    vectorSkins.push_back("player");
    vectorSkins.push_back("player1");
    vectorSkins.push_back("player2");
    vectorSkins.push_back("player3");
    vectorSkins.push_back("player4");
    vectorSkins.push_back("player5");
}
Select::~Select(){
    TTF_CloseFont(font);
    SDL_DestroyTexture(selected_minutes);
    SDL_DestroyTexture(fifteen);
    SDL_DestroyTexture(thirty);
    SDL_DestroyTexture(forty_five);
    SDL_DestroyTexture(player_name);
    SDL_DestroyTexture(player1_name);
}
void Select::Update(float& dt){
    change+=delta;
    if (change >= 1.0f) {
        blink += 0x01;
        change = 0;
    }
    else if (change <= -1.0f) {
        blink -= 0x01;
        change = 0;
    }
    if (blink == 0x64 && delta > 0) delta *= -1;
    else if (blink == 0x10 && delta < 0) delta *= -1;
    SDL_Color temp = {0, 0, 0, blink};
    if (n_player.length() > 0) TextureManager::GetInstance()->CreateTextureFromText(&player_name, font, n_player.c_str(), {19, 71, 22});
    else if (n_player.length() == 0 && !name_entered) TextureManager::GetInstance()->CreateTextureFromText(&player_name, font, "enter name", temp);
    if (mode == 2 && n_player1.length() > 0 && skin_has_been_selected) TextureManager::GetInstance()->CreateTextureFromText(&player1_name, font, n_player1.c_str(), {19, 71, 22});
    else if (mode == 2 && n_player1.length() == 0 && !name1_entered) TextureManager::GetInstance()->CreateTextureFromText(&player1_name, font, "enter name", temp);
    player_idle.Update(dt);
    player1_idle.Update(dt);
    top_cursor.Update(dt);
    if (!(left_cursor.GetFrame() == 0 && left_cursor.GetPrevFrame() == 3)) left_cursor.Update(dt);
    if (!(right_cursor.GetFrame() == 0 && right_cursor.GetPrevFrame() == 3)) right_cursor.Update(dt);
    if (!(heart.GetFrame() == 20 && heart.GetPrevFrame() == 19)) heart.Update(dt);
    if (rotate == 1 && !(rotate_1.GetFrame() == 9 && rotate_1.GetPrevFrame() == 8)) rotate_1.Update(dt);
    else if (rotate == 2 && !(rotate_2.GetFrame() == 9 && rotate_2.GetPrevFrame() == 8)) rotate_2.Update(dt);
    else if (rotate == 3 && !(rotate_3.GetFrame() == 9 && rotate_3.GetPrevFrame() == 8)) rotate_3.Update(dt);
    else if (rotate == 0) rotate_1.Update(dt);
}
void Select::Render(){
    TextureManager::GetInstance()->Render(bg, 0, 0, WIDTH, HEIGHT);
    if (mode == 1) player_idle.Render(485, 220, 32, 32, 8);
    else if (mode == 2 && !skin_has_been_selected) player_idle.Render(485, 220, 32, 32, 8);
    if (mode == 2) {
        player_idle.Render(77, 70, 32, 32, 4);
        if (skin_has_been_selected) {
            player1_idle.Render(1015, 70, 32, 32, 4);
            player1_idle.Render(485, 220, 32, 32, 8);
        }
        
    }
    SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 254, 225, 184, 127);
    TextureManager::GetInstance()->Render(vectorSkins[((Skins_iterator == 0) ? vectorSkins.size() - 1 : Skins_iterator-1)].c_str(), 270, 328, 32, 32, 4.0f);
    TextureManager::GetInstance()->Render(vectorSkins[((Skins_iterator == vectorSkins.size() - 1) ?  0 : Skins_iterator+1)].c_str(), 820, 328, 32, 32, 4.0f);
    SDL_Rect temp = {270, 328, 32*4, 32*4};
    SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &temp);
    temp = {820, 328, 32*4, 32*4};
    SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &temp);

    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_QueryTexture(selected_minutes, nullptr, nullptr, &minute_box.w, &minute_box.h);
    minute_box.x = (WIDTH - minute_box.w) / 2;
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), selected_minutes, nullptr, &minute_box);

    top_cursor.Render(568, 208, 64, 42);
    left_cursor.Render(140, 330, 85, 132);
    right_cursor.Render(990, 330, 85, 132);
    heart.Render(565, 553, 75, 75);
    
    if (rotate == 1) rotate_1.Render(295, 400, 620, 197);
    else if (rotate == 2) rotate_2.Render(295, 400, 617, 199);
    else if (rotate == 3) rotate_3.Render(295, 400, 617, 199);
    else rotate_1.Render(295, 400, 620, 197);

    MakeRectFromTexture(&player_name, &temp, 0, 128);
    temp.x = (WIDTH - temp.w) / 2;
    if (mode == 1) {
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player_name, nullptr, &temp);
        SDL_DestroyTexture(player_name);
        player_name = nullptr;
    }
    if (mode == 2) {
        if (skin_has_been_selected){
            MakeRectFromTexture(&player1_name, &temp, 0, 128);
            temp.x = (WIDTH - temp.w) / 2;
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player1_name, nullptr, &temp);
            SDL_DestroyTexture(player1_name);
            player1_name = nullptr;
        }
        else {
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player_name, nullptr, &temp);
            SDL_DestroyTexture(player_name);
            player_name = nullptr;
        }
    }

    if (mode == 1) {
        if (!name_entered) {
            TTF_Font* _font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 29);
            SDL_Texture* message;
            TextureManager::GetInstance()->CreateTextureFromText(&message, _font, "Enter your name", {26, 72, 86, 255});
            MakeRectFromTexture(&message, &temp, 843, 629);
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), message, nullptr, &temp);
            TTF_CloseFont(_font);
            SDL_DestroyTexture(message);
        }
        else if (!skin_has_been_selected) {
            TTF_Font* _font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 29);
            SDL_Texture* message;
            TextureManager::GetInstance()->CreateTextureFromText(&message, _font, "Choose your skin", {26, 72, 86, 255});
            MakeRectFromTexture(&message, &temp, 843, 629);
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), message, nullptr, &temp);
            TTF_CloseFont(_font);
            SDL_DestroyTexture(message);
        }
        else {
            TTF_Font* _font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 29);
            SDL_Texture* message;
            TextureManager::GetInstance()->CreateTextureFromText(&message, _font, "Select difficulty", {26, 72, 86, 255});
            MakeRectFromTexture(&message, &temp, 843, 629);
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), message, nullptr, &temp);
            TTF_CloseFont(_font);
            SDL_DestroyTexture(message);
        }
    }
    else if (mode == 2) {
        if (!name_entered && !skin_has_been_selected) {
            TTF_Font* _font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 29);
            SDL_Texture* message;
            TextureManager::GetInstance()->CreateTextureFromText(&message, _font, "Enter your name", {26, 72, 86, 255});
            MakeRectFromTexture(&message, &temp, 843, 629);
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), message, nullptr, &temp);
            TTF_CloseFont(_font);
            SDL_DestroyTexture(message);
        }
        else if (!name1_entered && skin_has_been_selected) {
            TTF_Font* _font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 29);
            SDL_Texture* message;
            TextureManager::GetInstance()->CreateTextureFromText(&message, _font, "Enter your name", {26, 72, 86, 255});
            MakeRectFromTexture(&message, &temp, 843, 629);
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), message, nullptr, &temp);
            TTF_CloseFont(_font);
            SDL_DestroyTexture(message);
        }
        else if (!skin_has_been_selected) {
            TTF_Font* _font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 29);
            SDL_Texture* message;
            TextureManager::GetInstance()->CreateTextureFromText(&message, _font, "Choose your skin", {26, 72, 86, 255});
            MakeRectFromTexture(&message, &temp, 843, 629);
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), message, nullptr, &temp);
            TTF_CloseFont(_font);
            SDL_DestroyTexture(message);
        }
        else if (!skin1_has_been_selected && name1_entered) {
            TTF_Font* _font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 29);
            SDL_Texture* message;
            TextureManager::GetInstance()->CreateTextureFromText(&message, _font, "Choose your skin", {26, 72, 86, 255});
            MakeRectFromTexture(&message, &temp, 843, 629);
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), message, nullptr, &temp);
            TTF_CloseFont(_font);
            SDL_DestroyTexture(message);
        }
        else {
            TTF_Font* _font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 29);
            SDL_Texture* message;
            TextureManager::GetInstance()->CreateTextureFromText(&message, _font, "Select difficulty", {26, 72, 86, 255});
            MakeRectFromTexture(&message, &temp, 843, 629);
            SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), message, nullptr, &temp);
            TTF_CloseFont(_font);
            SDL_DestroyTexture(message);
        }
    }
}

void Select::KeyText(SDL_Event event){
    if (n_player.length() <= max_name_char && !name_entered){
        if (*event.text.text >= 'a' && *event.text.text <= 'z') n_player += *event.text.text;
        else if (*event.text.text >= 'A' && *event.text.text <= 'Z') n_player += *event.text.text;
        else if (*event.text.text >= '0' && *event.text.text <= '9') n_player += *event.text.text;
        if (*event.text.text == ' ') n_player += *event.text.text;
        return;
    }
    if (mode == 2 && skin_has_been_selected && n_player1.length() <= max_name_char && !name1_entered && name_entered){
        if (*event.text.text >= 'a' && *event.text.text <= 'z') n_player1 += *event.text.text;
        else if (*event.text.text >= 'A' && *event.text.text <= 'Z') n_player1 += *event.text.text;
        else if (*event.text.text >= '0' && *event.text.text <= '9') n_player1 += *event.text.text;
        if (*event.text.text == ' ') n_player1 += *event.text.text;
    }
}

void Select::KeyDown(SDL_Scancode scancode){
    if (!name_entered || (mode == 2 && skin_has_been_selected && !name1_entered)) {
        switch(scancode){
            case SDL_SCANCODE_BACKSPACE:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                if (!name_entered && n_player.length() > 0) n_player.erase(n_player.end()-1, n_player.end());
                else if (!name1_entered && n_player1.length() > 0) n_player1.erase(n_player1.end()-1, n_player1.end());
                break;
            case SDL_SCANCODE_RETURN:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                if (!name_entered) name_entered = true;
                else if (!name1_entered) name1_entered = true;
                Skins_iterator = 0;
                break;
            case SDL_SCANCODE_ESCAPE:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
                return;
                break;
        }
        return;
    }
    if (!skin_has_been_selected){
        switch (scancode){
            case SDL_SCANCODE_LEFT:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                Skins_iterator++;
                if (Skins_iterator == vectorSkins.size()) Skins_iterator = 0;
                selected_skin = vectorSkins[Skins_iterator];
                player_idle.SetProp(selected_skin.c_str(), 0, 4, 150);
                left_cursor.SetProp("left_cursor", 0, 4, 50);
                heart.SetProp("heart", 0, 21, 50, SDL_FLIP_HORIZONTAL);
                if (!JustChangeRotate_right) rotate++;
                JustChangeRotate_left = true;
                JustChangeRotate_right = false;
                if (rotate == 4) rotate = 1;
                if (rotate == 1) rotate_1.SetProp("rotate_1", 0, 10, 20);
                else if (rotate == 2) rotate_2.SetProp("rotate_2", 0, 10, 20);
                else if (rotate == 3) rotate_3.SetProp("rotate_3", 0, 10, 20);
                break;
            case SDL_SCANCODE_RIGHT:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                Skins_iterator--;
                if (Skins_iterator < 0) Skins_iterator = vectorSkins.size()-1;
                selected_skin = vectorSkins[Skins_iterator];
                player_idle.SetProp(selected_skin.c_str(), 0, 4, 150);
                right_cursor.SetProp("right_cursor", 0, 4, 50);
                heart.SetProp("heart", 0, 21, 50);
                if (!JustChangeRotate_left) rotate--;
                JustChangeRotate_left = false;
                JustChangeRotate_right = true;
                if (rotate <= 0) rotate = 3;
                if (rotate == 1) rotate_1.SetProp("rotate_1", 0, 10, 20, SDL_FLIP_NONE, true);
                else if (rotate == 2) rotate_2.SetProp("rotate_2", 0, 10, 20, SDL_FLIP_NONE, true);
                else if (rotate == 3) rotate_3.SetProp("rotate_3", 0, 10, 20, SDL_FLIP_NONE, true);
                break;
            case SDL_SCANCODE_RETURN:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                skin_has_been_selected = true;
                if (mode == 2) Skins_iterator = 0;
                return;
                break;
            case SDL_SCANCODE_ESCAPE:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
                return;
                break;
        }
        return;
    }
    if (!skin1_has_been_selected && skin_has_been_selected && mode == 2 && name1_entered){
        switch (scancode){
            case SDL_SCANCODE_A:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                Skins_iterator++;
                if (Skins_iterator == vectorSkins.size()) Skins_iterator = 0;
                selected_skin1 = vectorSkins[Skins_iterator];
                player1_idle.SetProp(selected_skin1.c_str(), 0, 4, 150);
                left_cursor.SetProp("left_cursor", 0, 4, 60);
                heart.SetProp("heart", 0, 21, 50);
                if (!JustChangeRotate_right) rotate++;
                JustChangeRotate_left = true;
                JustChangeRotate_right = false;
                if (rotate == 4) rotate = 1;
                if (rotate == 1) rotate_1.SetProp("rotate_1", 0, 10, 20);
                else if (rotate == 2) rotate_2.SetProp("rotate_2", 0, 10, 20);
                else if (rotate == 3) rotate_3.SetProp("rotate_3", 0, 10, 20);
                break;
            case SDL_SCANCODE_D:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                Skins_iterator--;
                if (Skins_iterator < 0) Skins_iterator = vectorSkins.size()-1;
                selected_skin1 = vectorSkins[Skins_iterator];
                player1_idle.SetProp(selected_skin1.c_str(), 0, 4, 150);
                right_cursor.SetProp("right_cursor", 0, 4, 60);
                heart.SetProp("heart", 0, 21, 50, SDL_FLIP_HORIZONTAL);
                if (!JustChangeRotate_left) rotate--;
                JustChangeRotate_left = false;
                JustChangeRotate_right = true;
                if (rotate <= 0) rotate = 3;
                if (rotate == 1) rotate_1.SetProp("rotate_1", 0, 10, 20, SDL_FLIP_NONE, true);
                else if (rotate == 2) rotate_2.SetProp("rotate_2", 0, 10, 20, SDL_FLIP_NONE, true);
                else if (rotate == 3) rotate_3.SetProp("rotate_3", 0, 10, 20, SDL_FLIP_NONE, true);
                break;
            case SDL_SCANCODE_RETURN:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                skin1_has_been_selected = true;
                return;
                break;
            case SDL_SCANCODE_ESCAPE:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
                return;
                break;
        }
        return;
    }
    if ((skin_has_been_selected && mode == 1) || (mode == 2 && skin_has_been_selected && skin1_has_been_selected)) {
        switch (scancode){
            case SDL_SCANCODE_LEFT:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                Minute_iterator++;
                minute_per_sun += 15;
                if (Minute_iterator == vectorMinute.size()) Minute_iterator = 0;
                if (minute_per_sun == 60) minute_per_sun = 15;
                selected_minutes = vectorMinute[Minute_iterator];
                break;
            case SDL_SCANCODE_RIGHT:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                Minute_iterator--;
                minute_per_sun-=15;
                if (Minute_iterator < 0) Minute_iterator = vectorMinute.size()-1;
                if (minute_per_sun == 0) minute_per_sun = 45;
                selected_minutes = vectorMinute[Minute_iterator];
                break;
            case SDL_SCANCODE_RETURN:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                SceneManager::GetInstance()->ChangeScene(PLAYSCENE);
                return;
                break;
            case SDL_SCANCODE_ESCAPE:
                Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
                return;
                break;
        }
    }
}

void Select::KeyUp(SDL_Scancode scancode){

}
/********************************************************************************/
Scene_0* Scene_0::static_instance = nullptr;
Scene_0::Scene_0() : ID(PLAYSCENE) {
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;
    samurai_merchant_idle.SetProp("samurai_merchant", 0, 5, 100);
    Rockstand_merchant_idle.SetProp("Rockstand_merchant", 0, 40, 100);
    Left_platform = new GameObject(new Properties("Left_platform", 0, 506, 370, 40, ID, 1));
    Right_platform = new GameObject(new Properties("Right_platform", 830, 506, 370, 40, ID, 1));
    TTF_Font* font = TextureManager::GetInstance()->LoadFont("res/Fonts/mono.ttf", 20);
    player1_name = nullptr;
    name = Select::GetInstance()->n_player;
    if (Select::GetInstance()->mode == 2) name1 = Select::GetInstance()->n_player1;
    player_name = nullptr;
    if (name == "" && Select::GetInstance()->mode == 1) name = "player";
    else if (name == "" && Select::GetInstance()->mode == 2) name = "player 1";
    if (name1 == "" && Select::GetInstance()->mode == 2) name1 = "player 2";
    if (Select::GetInstance()->mode == 2) TextureManager::GetInstance()->CreateTextureFromText(&player1_name, font, name1.c_str(), {224, 142, 94});
    if (Select::GetInstance()->mode == 2) TextureManager::GetInstance()->CreateTextureFromText(&player1_name_cool_down, font, (name1 + " dash cool down").c_str(), {0, 0, 0, 100});
    TextureManager::GetInstance()->CreateTextureFromText(&player_name, font, name.c_str(), {47, 148, 147});
    TextureManager::GetInstance()->CreateTextureFromText(&player_name_cool_down, font, (name+" dash cool down").c_str(), {0, 0, 0, 100});
    TTF_CloseFont(font);

    player = new Player(new Properties(Select::GetInstance()->selected_skin.c_str(), 0, 0, 32, 32, ID, 1, 4, 2.0f, 6));
    if (Select::GetInstance()->mode == 2) player1 = new Player1(new Properties(Select::GetInstance()->selected_skin1.c_str(), 1200-32*2, 0, 32, 32, ID, 1, 4, 2.0f, 6));
    hover_platform = new Hover_platform(new Properties("Hover_platform", 525, 437, 150, 74, ID, 1));

    Planet* moon = 
    new Planet(new Properties("moon", 592, 2, 48, 48, ID, 1, 0, 1.0f, 8));
    countSun = 0;
    max_sun = 1440 / Select::GetInstance()->minute_per_sun;
    DAYS = 1;
    countMoon = DAYS;
    HOURS.first = 0;
    HOURS.second = 0;
    
    freedom = TextureManager::GetInstance()->LoadFont("res/Fonts/Freedom.ttf", 100);
}
Scene_0::~Scene_0(){
    TTF_CloseFont(freedom);
    SDL_DestroyTexture(hours_texture);
    SDL_DestroyTexture(days_texture);
    SDL_DestroyTexture(player_name);
    SDL_DestroyTexture(player1_name);
}
void Scene_0::Update(float& dt){
    spawnSun += dt;
    if (Mix_PlayingMusic() == 0) {
        song++;
        if (song == playlist.size()) song = 0;
        Mixer::GetInstance()->Play(playlist[song],MUSIC);
    }
    UpdateIdle(dt);
    if (spawnSun >= 1 && countSun < max_sun){
        Planet* sun = new Planet(new Properties("sun", 592, 2, 48, 48, ID, 1, 0, 1/3.0f, 9));
        spawnSun = 0;
        countSun++;
    }
    if (HOURS.first == 24) {
        DAYS++;
        countMoon = DAYS;
        HOURS = {0, 0};
        countSun = 0;
        Mixer::GetInstance()->Play("res/Sounds/next_level.wav", SFX, 0);
        Planet* moon = new Planet(new Properties("moon", 592, 2, 48, 48, ID, 1, 0, 1.0f, 8));
    }
    {
        std::string front = std::to_string(HOURS.first), end = std::to_string(HOURS.second);
        if (HOURS.first < 10) front = "0" + std::to_string(HOURS.first);
        if (HOURS.second == 0) end = "00";
        _time = front + ":" + end;
    }
    GameObjectHandler::GetInstance()->Update(dt);
}

void Scene_0::SaveScore(){
    if (player1_name == nullptr){
        std::fstream mode_1_best;
        mode_1_best.open("res/Score/mode_1_best.txt", std::ios::in);
        if (mode_1_best.is_open()){
            std::string trash;
            mode_1_best >> trash >> trash;
            int d, h, m;
            mode_1_best >> d >> h >> m;
            if (DAYS > d || (DAYS == d && HOURS.first > h) || (DAYS == d && HOURS.first == h && HOURS.second > m)) {
                mode_1_best.close();
                mode_1_best.open("res/Score/mode_1_best.txt", std::ios::out);
                mode_1_best << name << std::endl << player->GetID() << std::endl << DAYS << std::endl << HOURS.first << std::endl << HOURS.second;
                mode_1_best.close();
            }
        }
        else std::cout << "Error. Cannot open file: res/Score/mode_1_best.txt" << std::endl;

        std::ofstream mode_1_current("res/Score/mode_1 _current.txt");
        if (mode_1_current){
            mode_1_current << name << std::endl << player->GetID() << std::endl << DAYS << std::endl << HOURS.first << std::endl << HOURS.second;
            mode_1_current.close();
        }
        else std::cout << "Error. Cannot open file: res/Score/mode_1_current.txt" << std::endl;

    }
    else {
        std::fstream mode_2_best;
        mode_2_best.open("res/Score/mode_2_best.txt", std::ios::in);
        if (mode_2_best.is_open()){
            std::string trash;
            mode_2_best >> trash >> trash >> trash >> trash;
            int d, h, m;
            mode_2_best >> d >> h >> m;
            if (DAYS > d || (DAYS == d && HOURS.first > h) || (DAYS == d && HOURS.first == h && HOURS.second > m)) {
                mode_2_best.close();
                mode_2_best.open("res/Score/mode_2_best.txt", std::ios::out);
                mode_2_best << name << std::endl << player->GetID() << std::endl << name1 << std::endl << player1->GetID() << std::endl << DAYS << std::endl << HOURS.first << std::endl << HOURS.second;
                mode_2_best.close();
            }
        }
        
        std::ofstream mode_2_current("res/Score/mode_2_current.txt");
        if (mode_2_current){
            mode_2_current << name << std::endl << player->GetID() << std::endl << name1 << std::endl << player1->GetID() << std::endl << DAYS << std::endl << HOURS.first << std::endl << HOURS.second;
            mode_2_current.close();
        }
        else std::cout << "Error. Cannot open file: res/Score/mode_1_currentmode_2_current.txt" << std::endl;
    }
}

void Scene_0::Render(){
    if (HOURS.first >= 6 && HOURS.first <= 12) {
        r = 208;
        g = 214;
        b = 228;
    }
    else if (HOURS.first >= 12 && HOURS.first <= 16) {
        r = 228;
        g = 226;
        b = 208;
    }
    else if (HOURS.first >= 16 && HOURS.first <= 18) {
        r = 228;
        g = 218;
        b = 208;
    }
    else if (HOURS.first >= 18 || HOURS.first <= 5) {
        r = 211;
        g = 228;
        b = 208;
    }
    _r += (_r > r) ? -0.1f : ((_r < r) ? 0.1f : 0);
    _g += (_g > g) ? -0.1f : ((_g < g) ? 0.1f : 0);
    _b += (_b > b) ? -0.1f : ((_b < b) ? 0.1f : 0);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), _r, _g, _b, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    TextureManager::GetInstance()->Render("background_transparent", 0, 0, WIDTH, HEIGHT);
    /*---------------Draw days and hours-----------------------------------*/
    TextureManager::GetInstance()->CreateTextureFromText(&hours_texture, freedom, _time.c_str(), {255, 0, 0, 150});
    std::string days = "Day:";
    TextureManager::GetInstance()->CreateTextureFromText(&days_texture, freedom, days.c_str(), {255, 150, 0, 150});
    SDL_Rect hours_rect = {391, 185, 0 ,0};
    SDL_Rect days_rect = {391, 0, 0 ,0};
    SDL_QueryTexture(hours_texture, nullptr, nullptr, &hours_rect.w, &hours_rect.h);
    SDL_QueryTexture(days_texture, nullptr, nullptr, &days_rect.w, &days_rect.h);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(),hours_texture, nullptr, &hours_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(),days_texture, nullptr, &days_rect);
    SDL_DestroyTexture(days_texture);
    days = std::to_string(DAYS);
    days_rect.x = days_rect.w + days_rect.x + 30;
    TextureManager::GetInstance()->CreateTextureFromText(&days_texture, freedom, days.c_str(), {255, 150, 0, 150});
    SDL_QueryTexture(days_texture, nullptr, nullptr, &days_rect.w, &days_rect.h);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(),days_texture, nullptr, &days_rect);
    SDL_DestroyTexture(days_texture);
    SDL_DestroyTexture(hours_texture);
    /*-------------------------------------------------------------*/
    RenderSamuraiMerchant();
    Rockstand_merchant_idle.Render(536, hover_platform->getCollider().GetBox().y-64, 128, 64);
    GameObjectHandler::GetInstance()->Render();

    dash_cool_down.first = 0 - (SDL_GetTicks() - Player::GetInstance()->GetLastDash()) / (float)DASH_COOL_DOWN * 370;
    if (dash_cool_down.first < -370) dash_cool_down.first = -370;
    TextureManager::GetInstance()->Render("dash_bar", dash_cool_down.first, dash_cool_down.second, 370, 40);
    if (Player1::GetInstance() != nullptr){
        dash_cool_down_1.first = 0 - (SDL_GetTicks() - Player1::GetInstance()->GetLastDash()) / (float)DASH_COOL_DOWN * 370;
        if (dash_cool_down_1.first > WIDTH+370) dash_cool_down_1.first = -370;
        TextureManager::GetInstance()->Render("dash_bar", dash_cool_down_1.first, dash_cool_down_1.second, 370, 40);
    }

    MakeRectFromTexture(&player_name, &p_rect, Player::GetInstance()->getTransform()->x + 32 - p_rect.w/2, Player::GetInstance()->getTransform()->y-20);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player_name, nullptr, &p_rect);
    MakeRectFromTexture(&player_name_cool_down, &p_rect, 0, 0);
    p_rect.x = (370-p_rect.w)/2;
    p_rect.y = 506+10;
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player_name_cool_down, nullptr, &p_rect);
    MakeRectFromTexture(&player_name, &p_rect, Player::GetInstance()->getTransform()->x + 32 - p_rect.w/2, Player::GetInstance()->getTransform()->y-20);
    
    if (Player1::GetInstance() != nullptr) {
        MakeRectFromTexture(&player1_name, &p1_rect, Player1::GetInstance()->getTransform()->x + 32 - p1_rect.w/2, Player1::GetInstance()->getTransform()->y-20);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player1_name, nullptr, &p1_rect);
        MakeRectFromTexture(&player1_name_cool_down, &p1_rect, 0, 0);
        p1_rect.x = (370-p1_rect.w)/2+830;
        p1_rect.y = 506+10;
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player1_name_cool_down, nullptr, &p1_rect);
        MakeRectFromTexture(&player1_name, &p1_rect, Player1::GetInstance()->getTransform()->x + 32 - p1_rect.w/2, Player1::GetInstance()->getTransform()->y-20);
    }
}

void Scene_0::UpdateIdle(float dt){
    samurai_merchant_idle.Update(dt);
    Rockstand_merchant_idle.Update(dt);
}

void Scene_0::RenderSamuraiMerchant(){
    srand(time(NULL));
    int random_stop = (rand() % 3 + 5) * 100;
    if (samurai_x == 1095) {
        if (GO == 1){
            GO = -1;
            samurai_x += random_stop;
            samurai_merchant_idle.SetProp("samurai_merchant", 1, 4, 100);
        }
        else samurai_merchant_idle.SetProp("samurai_merchant", 0, 5, 100, SDL_FLIP_HORIZONTAL);
    }
    else if (samurai_x == 210){
        if (GO == -1){
            GO = 1;
            samurai_x -= random_stop;
            samurai_merchant_idle.SetProp("samurai_merchant", 1, 4, 100, SDL_FLIP_HORIZONTAL);
        }
        else samurai_merchant_idle.SetProp("samurai_merchant", 0, 5, 100);
    }
    samurai_x += GO;
    if (samurai_x <= 1095 && samurai_x >= 210) samurai_merchant_idle.Render(samurai_x, 625, 78, 50);
    else if (samurai_x > 1095) samurai_merchant_idle.Render(1095, 625, 78, 50);
    else if (samurai_x < 210) samurai_merchant_idle.Render(210, 625, 78, 50);
}

void Scene_0::KeyDown(SDL_Scancode scancode){
    if (scancode == SDL_SCANCODE_P) Mix_HaltMusic();
    if (scancode == PLAYER_JUMP_SCANCODE && ((Player::GetInstance()->GetRemainJumps() == 2 && (SDL_GetTicks() - Player::GetInstance()->lastJump >= 0)) || Player::GetInstance()->GetRemainJumps() == 1)/* && Player::GetInstance()->GetAllowInput() == true*/){
        Mixer::GetInstance()->Play("res/Sounds/sfx_jump.wav", SFX, 0);
        if (Player::GetInstance()->GetRemainJumps() == 2) {
            Player::GetInstance()->JumpDust1.SetProp("Jump_Dust", 0, 5, 80);
            Player::GetInstance()->lastJump = SDL_GetTicks();
            Player::GetInstance()->j1_x = Player::GetInstance()->getTransform()->x+5;
            Player::GetInstance()->j1_y = Player::GetInstance()->getTransform()->y + Player::GetInstance()->getCollider().GetBox().h + OFFSET - 5;
        }
        else {
            Player::GetInstance()->JumpDust2.SetProp("Jump_Dust", 0, 5, 80);
            Player::GetInstance()->j2_x = Player::GetInstance()->getTransform()->x+5;
            Player::GetInstance()->j2_y = Player::GetInstance()->getTransform()->y + Player::GetInstance()->getCollider().GetBox().h + OFFSET - 5;
        }
        //Planet* sun = new Planet(new Properties("sun", 592, 2, 48, 48, ID, 1, 0, 1/3.0f, 9));
        //Planet* moon = new Planet(new Properties("moon", 592, 2, 48, 48, ID, 1, 0, 1.0f, 8));
        Player::GetInstance()->ReduceJumps();
        Player::GetInstance()->SetInAir() = true;
        Player::GetInstance()->SetAllowInput() = false;
        Player::GetInstance()->SetPrevState();
        Player::GetInstance()->SetState(STATE::JUMPING, Player::GetInstance()->GetState().second);
        Player::GetInstance()->GetRigidBody()->applyVelocityY(JUMP_VELOCITY * UPWARD);
    }
    if (scancode == PLAYER_DASH_SCANCODE && Player::GetInstance()->CanDash() && SDL_GetTicks() - Player::GetInstance()->GetLastDash() >= DASH_COOL_DOWN){
        Player::GetInstance()->Dashing() = true;
        Player::GetInstance()->CanDash() = false;
        Player::GetInstance()->DashLength() = 150;
        Player::GetInstance()->DashTime() = 0;
        Player::GetInstance()->getTransform()->translateY(-1.0f);
        Player::GetInstance()->GetLastDash() = SDL_GetTicks();
        Player::GetInstance()->GetRigidBody()->resetAccelerationX();
        Player::GetInstance()->GetRigidBody()->resetVelocity();
        Player::GetInstance()->GetRigidBody()->resetPosition();
        Player::GetInstance()->SetAllowInput() = false;
        if (Player::GetInstance()->GetState().second == FACE::RIGHT) Player::GetInstance()->GetRigidBody()->applyVelocityX(DASH_VELLOCITY * FORWARD);
        else if (Player::GetInstance()->GetState().second == FACE::LEFT) Player::GetInstance()->GetRigidBody()->applyVelocityX(DASH_VELLOCITY * BACKWARD);
    }
    if (scancode == SDL_SCANCODE_ESCAPE) {
        Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
        Player::GetInstance()->SetPrevState();
        Player::GetInstance()->NeedChangeState() = true;
        if (Player::GetInstance()->GetState().first == RUNNING && Player::GetInstance()->GetState().second == LEFT){
            Player::GetInstance()->GetRigidBody()->applyAccelerationX(FORWARD * DECCELERATE_TO_ZERO);
            Player::GetInstance()->SetState(STATE::STANDING, FACE::LEFT);
        }
        else if (Player::GetInstance()->GetState().first == RUNNING && Player::GetInstance()->GetState().second == RIGHT){
            Player::GetInstance()->GetRigidBody()->applyAccelerationX(BACKWARD * DECCELERATE_TO_ZERO);
            Player::GetInstance()->SetState(STATE::STANDING, FACE::RIGHT);
        }
        if (Player1::GetInstance() != nullptr){
            Player1::GetInstance()->SetPrevState();
            Player1::GetInstance()->NeedChangeState() = true;
            if (Player1::GetInstance()->GetState().first == RUNNING && Player1::GetInstance()->GetState().second == RIGHT){
                Player1::GetInstance()->GetRigidBody()->applyAccelerationX(BACKWARD * DECCELERATE_TO_ZERO);
                Player1::GetInstance()->SetState(STATE::STANDING, FACE::RIGHT);
            }
            else if (Player1::GetInstance()->GetState().first == RUNNING && Player1::GetInstance()->GetState().second == LEFT){
                Player1::GetInstance()->GetRigidBody()->applyAccelerationX(FORWARD * DECCELERATE_TO_ZERO);
                Player1::GetInstance()->SetState(STATE::STANDING, FACE::LEFT);
            }
        }
        SceneManager::GetInstance()->ChangeScene(PAUSE_SCENE, true, false, false);
        return;
    }
    if (Input::GetInstance()->GetKeyState()[PLAYER_GO_RIGHT_SCANCODE] && scancode == PLAYER_GO_LEFT_SCANCODE) Player::GetInstance()->SetSmoothMovement() = true;
    if (Input::GetInstance()->GetKeyState()[PLAYER_GO_LEFT_SCANCODE] && scancode == PLAYER_GO_RIGHT_SCANCODE) Player::GetInstance()->SetSmoothMovement() = false;
    //////////////////////////////////////////
    if (Player1::GetInstance() != nullptr){
        if (scancode == PLAYER1_JUMP_SCANCODE && ((Player1::GetInstance()->GetRemainJumps() == 2 && (SDL_GetTicks() - Player1::GetInstance()->lastJump >= 0)) || Player1::GetInstance()->GetRemainJumps() == 1)/* && Player1::GetInstance()->GetAllowInput() == true*/){
        Mixer::GetInstance()->Play("res/Sounds/sfx_jump.wav", SFX, 0);    
        if (Player1::GetInstance()->GetRemainJumps() == 2) {
            Player1::GetInstance()->JumpDust1.SetProp("Jump_Dust", 0, 5, 80);
            Player1::GetInstance()->lastJump = SDL_GetTicks();
            Player1::GetInstance()->j1_x = Player1::GetInstance()->getTransform()->x+5;
            Player1::GetInstance()->j1_y = Player1::GetInstance()->getTransform()->y + Player1::GetInstance()->getCollider().GetBox().h-6;
        }
        else {
            Player1::GetInstance()->JumpDust2.SetProp("Jump_Dust", 0, 5, 80);
            Player1::GetInstance()->j2_x = Player1::GetInstance()->getTransform()->x+5;
            Player1::GetInstance()->j2_y = Player1::GetInstance()->getTransform()->y + Player1::GetInstance()->getCollider().GetBox().h-6;
        }
        Player1::GetInstance()->ReduceJumps();
        Player1::GetInstance()->SetInAir() = true;
        Player1::GetInstance()->SetAllowInput() = false;
        Player1::GetInstance()->SetPrevState();
        Player1::GetInstance()->SetState(STATE::JUMPING, Player1::GetInstance()->GetState().second);
        Player1::GetInstance()->GetRigidBody()->applyVelocityY(JUMP_VELOCITY * UPWARD);
    }
        if (scancode == PLAYER1_DASH_SCANCODE && Player1::GetInstance()->CanDash() && SDL_GetTicks() - Player1::GetInstance()->GetLastDash() >= DASH_COOL_DOWN){
            Player1::GetInstance()->Dashing() = true;
            Player1::GetInstance()->CanDash() = false;
            Player1::GetInstance()->DashLength() = 150;
            Player1::GetInstance()->DashTime() = 0;
            Player1::GetInstance()->getTransform()->translateY(-1.0f);
            Player1::GetInstance()->GetLastDash() = SDL_GetTicks();
            Player1::GetInstance()->GetRigidBody()->resetAccelerationX();
            Player1::GetInstance()->GetRigidBody()->resetVelocity();
            Player1::GetInstance()->GetRigidBody()->resetPosition();
            Player1::GetInstance()->SetAllowInput() = false;
            if (Player1::GetInstance()->GetState().second == FACE::RIGHT) Player1::GetInstance()->GetRigidBody()->applyVelocityX(DASH_VELLOCITY * FORWARD);
            else if (Player1::GetInstance()->GetState().second == FACE::LEFT) Player1::GetInstance()->GetRigidBody()->applyVelocityX(DASH_VELLOCITY * BACKWARD);
        }
        if (scancode == SDL_SCANCODE_ESCAPE) {
            SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
            return;
        }
        if (Input::GetInstance()->GetKeyState()[PLAYER1_GO_RIGHT_SCANCODE] && scancode == PLAYER1_GO_LEFT_SCANCODE) Player1::GetInstance()->SetSmoothMovement() = true;
        if (Input::GetInstance()->GetKeyState()[PLAYER1_GO_LEFT_SCANCODE] && scancode == PLAYER1_GO_RIGHT_SCANCODE) Player1::GetInstance()->SetSmoothMovement() = false;
    }
}

void Scene_0::KeyUp(SDL_Scancode scancode){
    switch (scancode){
        case PLAYER_GO_RIGHT_SCANCODE:
            Player::GetInstance()->SetPrevState();
            Player::GetInstance()->NeedChangeState() = true;
            Player::GetInstance()->GetRigidBody()->applyAccelerationX(BACKWARD * DECCELERATE_TO_ZERO);
            Player::GetInstance()->SetState(STATE::STANDING, FACE::RIGHT);
            break;
        case PLAYER_GO_LEFT_SCANCODE:
            Player::GetInstance()->SetPrevState();
            Player::GetInstance()->NeedChangeState() = true;
            Player::GetInstance()->GetRigidBody()->applyAccelerationX(FORWARD * DECCELERATE_TO_ZERO);
            Player::GetInstance()->SetState(STATE::STANDING, FACE::LEFT);
            break;
        case PLAYER_JUMP_SCANCODE:
            Player::GetInstance()->SetPrevState();
            Player::GetInstance()->NeedChangeState() = true;
            break;
    }
    if (Player1::GetInstance() != nullptr) {
        switch(scancode){    
            case PLAYER1_GO_RIGHT_SCANCODE:
                Player1::GetInstance()->SetPrevState();
                Player1::GetInstance()->NeedChangeState() = true;
                Player1::GetInstance()->GetRigidBody()->applyAccelerationX(BACKWARD * DECCELERATE_TO_ZERO);
                Player1::GetInstance()->SetState(STATE::STANDING, FACE::RIGHT);
                break;
            case PLAYER1_GO_LEFT_SCANCODE:
                Player1::GetInstance()->SetPrevState();
                Player1::GetInstance()->NeedChangeState() = true;
                Player1::GetInstance()->GetRigidBody()->applyAccelerationX(FORWARD * DECCELERATE_TO_ZERO);
                Player1::GetInstance()->SetState(STATE::STANDING, FACE::LEFT);
                break;
            case PLAYER1_JUMP_SCANCODE:
                Player1::GetInstance()->SetPrevState();
                Player1::GetInstance()->NeedChangeState() = true;
                break;
        }
    }
}

/********************************************************************************/

Pause* Pause::static_instance = nullptr;
Pause::Pause() : ID(PAUSE_SCENE){
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;
    const Uint32 format = SDL_PIXELFORMAT_ABGR8888;
    SDL_Surface* snap = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, format);
    SDL_RenderReadPixels(Engine::GetInstance()->GetRenderer(), nullptr, format, snap->pixels, snap->pitch);
    background = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), snap);
    SDL_FreeSurface(snap);

    font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 24);

    TextureManager::GetInstance()->CreateTextureFromText(&Resume, font, "Resume", {0, 0, 0});
    MakeRectFromTexture(&Resume, &resume_rect, 414, 321);
    TextureManager::GetInstance()->CreateTextureFromText(&Menu, font, "Menu", {0, 0, 0});
    MakeRectFromTexture(&Menu, &menu_rect, 695, 321);

    currentRect = &resume_rect;
    vectorRect.push_back(&resume_rect);
    vectorRect.push_back(&menu_rect);
}
Pause::~Pause(){
    SDL_DestroyTexture(Resume);
    SDL_DestroyTexture(Menu);
    SDL_DestroyTexture(background);
    TTF_CloseFont(font);
}

void Pause::Update(float& dt){

}

void Pause::Render(){
    SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 100);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), background, nullptr, nullptr);
    SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), nullptr);

    TextureManager::GetInstance()->Render("pause_background", 0, 0, WIDTH, HEIGHT);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Resume, nullptr, &resume_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Menu, nullptr, &menu_rect);
    SDL_Rect temp = {406, 310, 128, 56};
    SDL_Rect temp1 = {666, 310, 128, 56};
    if (currentRect ==  &menu_rect) SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(),  &temp);
    else if (currentRect ==  &resume_rect) SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(),  &temp1);

    //SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), currentRect);
}

void Pause::KeyDown(SDL_Scancode scancode){
    switch (scancode){
        case SDL_SCANCODE_LEFT:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            i--;
            if (i < 0) i = vectorRect.size() - 1;
            currentRect = vectorRect[i];
            break;
        case SDL_SCANCODE_RIGHT:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            i++;
            if (i == vectorRect.size()) i = 0;
            currentRect = vectorRect[i];
            break;
        case SDL_SCANCODE_RETURN:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            if (currentRect == &resume_rect) SceneManager::GetInstance()->ChangeScene(PLAYSCENE, false, false, true);
            else if (currentRect == &menu_rect) {
                SceneManager::GetInstance()->Clean(PLAYSCENE);
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
            }
            return;
            break;
    }
}

void Pause::KeyUp(SDL_Scancode scancode){

}

/********************************************************************************/

Score* Score::static_instance = nullptr;

Score::Score() : ID(SCORE_SCENE) {
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;
    name = Scene_0::GetInstance()->name;
    if (Scene_0::GetInstance()->name1 != "") name1 = Scene_0::GetInstance()->name1;
    currDays = Scene_0::GetInstance()->DAYS;
    currHours = Scene_0::GetInstance()->HOURS.first;
    currMinutes = Scene_0::GetInstance()->HOURS.second;

    if (name1 == ""){
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 35);
        std::ifstream mode_1_best("res/Score/mode_1_best.txt");
        if (mode_1_best){
            mode_1_best >> best_name >> best_skin >> BestDays >> BestHours >> BestMinutes;
            mode_1_best.close();
        }
        else std::cout << "Error. Cannot open file: res/Score/mode_1_best.txt" << std::endl;
        curr_skin = Player::GetInstance()->GetID();
        curr_Idle.SetProp(curr_skin.c_str(), 0, 4, 100);
        best_Idle.SetProp(best_skin.c_str(), 0, 4, 100);
    }
    else {
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 25);
        std::ifstream mode_2_best("res/Score/mode_2_best.txt");
        if (mode_2_best){
            mode_2_best >> best_name >> best_skin >> best_name1 >> best_skin1 >> BestDays >> BestHours >> BestMinutes;
            mode_2_best.close();
        }
        else std::cout << "Error. Cannot open file: res/Score/mode_2_best.txt" << std::endl;
        curr_skin = Player::GetInstance()->GetID();
        curr_Idle.SetProp(curr_skin.c_str(), 0, 4, 100);
        best_Idle.SetProp(best_skin.c_str(), 0, 4, 100);

        curr_skin1 = Player1::GetInstance()->GetID();
        curr1_Idle.SetProp(curr_skin1.c_str(), 0, 4, 100);
        best1_Idle.SetProp(best_skin1.c_str(), 0, 4, 100);
    }
}

Score::~Score(){
    TTF_CloseFont(font);
}

void Score::Update(float& dt){
    curr_Idle.Update(dt);
    best_Idle.Update(dt);
    if (name1 != "") {
        curr1_Idle.Update(dt);
        best1_Idle.Update(dt);
    }
}

void Score::Render(){
    TextureManager::GetInstance()->Render("score_background", 0, 0, WIDTH, HEIGHT);
    if (name1 == "") {
        SDL_Texture* temp;
        SDL_Rect temp_rect;
        TTF_CloseFont(font);
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/mono.ttf", 35);
        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, name.c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 0, 300-27);
        temp_rect.x = 796+32*4-temp_rect.w/2;
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, best_name.c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 0, 300-27);
        temp_rect.x = 148+32*4-temp_rect.w/2;
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);
        TTF_CloseFont(font);

        font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 32);
        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (BestDays < 10 ? "0"+std::to_string(BestDays):std::to_string(BestDays)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 126, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (BestHours < 10 ? "0"+std::to_string(BestHours) : std::to_string(BestHours)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 260, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (std::to_string(BestMinutes) == "0" ? "00" : std::to_string(BestMinutes)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 410, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (currDays < 10 ? "0"+std::to_string(currDays):std::to_string(currDays)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 728, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (currHours < 10 ? "0"+std::to_string(currHours) : std::to_string(currHours)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 862, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (std::to_string(currMinutes) == "0" ? "00" : std::to_string(currMinutes) ).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 1012, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);
        TTF_CloseFont(font);
        font = nullptr;

        curr_Idle.Render(796, 300, 32, 32, 8);
        best_Idle.Render(148, 300, 32, 32, 8);
    }
    else {
        SDL_Texture* temp;
        SDL_Rect temp_rect;
        TTF_CloseFont(font);
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/mono.ttf", 35);
        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, name.c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 0, 300-27);
        temp_rect.x = 671+32*4-temp_rect.w/2-50;
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, best_name.c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 0, 300-27);
        temp_rect.x = 68+32*4-temp_rect.w/2-50;
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, best_name1.c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 0, 300-27);
        temp_rect.x = 392+32*4-temp_rect.w/2-50;
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);
        
        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, name1.c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 0, 300-27);
        temp_rect.x = 995+32*4-temp_rect.w/2-50;
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TTF_CloseFont(font);

        font = TextureManager::GetInstance()->LoadFont("res/Fonts/arial.ttf", 32);
        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (BestDays < 10 ? "0"+std::to_string(BestDays):std::to_string(BestDays)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 126, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (std::to_string(BestHours) == "0" ? "00" : std::to_string(BestHours)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 260, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (std::to_string(BestMinutes) == "0" ? "00" : std::to_string(BestMinutes)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 410, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (currDays < 10 ? "0"+std::to_string(currDays):std::to_string(currDays)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 728, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (std::to_string(currHours) == "0" ? "00" : std::to_string(currHours)).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 862, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);

        TextureManager::GetInstance()->CreateTextureFromText(&temp, font, (std::to_string(currMinutes) == "0" ? "00" : std::to_string(currMinutes) ).c_str(), {26, 72, 86, 255});
        MakeRectFromTexture(&temp, &temp_rect, 1012, 90);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), temp, nullptr, &temp_rect);
        SDL_DestroyTexture(temp);
        TTF_CloseFont(font);
        font = nullptr;

        curr_Idle.Render(671-50, 300, 32, 32, 8);
        best_Idle.Render(68-50, 300, 32, 32, 8);
        curr1_Idle.Render(995-50, 300, 32, 32, 8);
        best1_Idle.Render(392-50, 300, 32, 32, 8);
    }

}

void Score::KeyDown(SDL_Scancode scancode){
    switch (scancode){
        case SDL_SCANCODE_RETURN:
            Mixer::GetInstance()->Play("res/Sounds/beep.wav", SFX);
            SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
            return;
            break;
    }
}

void Score::KeyUp(SDL_Scancode scancode){
}