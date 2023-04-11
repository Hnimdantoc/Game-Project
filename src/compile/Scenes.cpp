#include "Scenes.hpp"
/********************************************************************************/
Menu* Menu::static_instance = nullptr;
Menu::Menu() : ID(MENU_SCENE) {        
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;
    ChoosingMode = false;
    font = TextureManager::GetInstance()->LoadFont("res/Fonts/Freedom.ttf", 70);
    title = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 100);

    TextureManager::GetInstance()->CreateTextureFromText(&Title, font, "T1 < DEFT", {0, 255, 0});
    MakeRectFromTexture(&Title, &title_rect, 500, 0);
    
    TextureManager::GetInstance()->CreateTextureFromText(&Play, font, "PLAY", {255, 255, 255});
    MakeRectFromTexture(&Play, &play_rect, 500, 250);

    TextureManager::GetInstance()->CreateTextureFromText(&Option, font, "OPTION", {255, 255, 0});
    MakeRectFromTexture(&Option, &option_rect, 500, 350);

    TextureManager::GetInstance()->CreateTextureFromText(&Exit, font, "EXIT", {255, 255, 0});
    MakeRectFromTexture(&Exit, &exit_rect, 500, 500);

    TextureManager::GetInstance()->CreateTextureFromText(&Mode_1, font, "1", {255, 255, 0});
    MakeRectFromTexture(&Mode_1, &mode_1_rect, play_rect.x - 50, 250);

    TextureManager::GetInstance()->CreateTextureFromText(&Mode_2, font, "2", {255, 255, 0});
    MakeRectFromTexture(&Mode_2, &mode_2_rect, play_rect.x - 50, 300);

    currentRect = &play_rect;
    vectorRect.push_back({&play_rect, &option_rect, &exit_rect});
    vectorRect.push_back({&mode_1_rect, &mode_2_rect});
}
Menu::~Menu(){
    TTF_CloseFont(font);
    TTF_CloseFont(title);
    SDL_DestroyTexture(Title);
    SDL_DestroyTexture(Play);
    SDL_DestroyTexture(Option);
    SDL_DestroyTexture(Exit);
    SDL_DestroyTexture(Mode_1);
    SDL_DestroyTexture(Mode_2);
}
void Menu::Update(float& dt){
    GameObjectHandler::GetInstance()->Update(dt);
}
void Menu::Render(){
    TextureManager::GetInstance()->Render("background", 0, 0, WIDTH, HEIGHT);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Title, nullptr, &title_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Play, nullptr, &play_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Option, nullptr, &option_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Exit, nullptr, &exit_rect);
    if (ChoosingMode){
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Mode_1, nullptr, &mode_1_rect);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Mode_2, nullptr, &mode_2_rect);
    }
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), currentRect);
}

void Menu::KeyDown(SDL_Scancode scancode){
    switch(scancode){
        case SDL_SCANCODE_DOWN:
            j++;
            if (j == vectorRect[i].size()) j = 0;
            currentRect = vectorRect[i][j];
            break;
        case SDL_SCANCODE_UP:
            j--;
            if (j < 0) j = vectorRect[i].size()-1;
            currentRect = vectorRect[i][j];
            break;
        case SDL_SCANCODE_RETURN:
            if (!ChoosingMode){
                if (currentRect == &play_rect) {
                    ChoosingMode = true;
                    i++;
                    currentRect = &mode_1_rect;
                }
                else if (Menu::GetInstance()->currentRect == &exit_rect) {
                    Engine::GetInstance()->setGameState() = GAME_STATE::EXIT;
                    return;
                }
            }
            else {
                if (currentRect == &mode_1_rect) mode_2 = false;
                else mode_2 = true;
                SceneManager::GetInstance()->ChangeScene(SELECT_SCENE);
            }
            break;
        case SDL_SCANCODE_ESCAPE:
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
Select* Select::static_instance = nullptr;
Select::Select() : ID(SELECT_SCENE){
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;

    font = TextureManager::GetInstance()->LoadFont("res/Fonts/Freedom.ttf", 40);
    if (Menu::GetInstance()->mode_2) mode = 2;
    else mode = 1;
    skin_has_been_selected = false;
    skin1_has_been_selected = false;
    minute_per_sun = 30;
    TextureManager::GetInstance()->CreateTextureFromText(&fifteen, font, "15", {0, 0, 0, 255});
    TextureManager::GetInstance()->CreateTextureFromText(&thirty, font, "30", {0, 0, 0, 255});
    selected_minutes = thirty;
    TextureManager::GetInstance()->CreateTextureFromText(&forty_five, font, "45", {0, 0, 0, 255});
    
    minute_box.x = 600;
    minute_box.y = 0;
    SDL_QueryTexture(thirty, nullptr, nullptr, &minute_box.w, &minute_box.h);

    name_box = {0, 300, 300, 100};

    vectorMinute.push_back(fifteen);
    vectorMinute.push_back(thirty);
    vectorMinute.push_back(forty_five);
    vectorSkins.push_back("player");
    vectorSkins.push_back("player1");
    vectorSkins.push_back("player2");
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
    if (n_player.length() > 0) TextureManager::GetInstance()->CreateTextureFromText(&player_name, font, n_player.c_str(), {150, 0, 255});
    if (mode == 2 && n_player1.length() > 0) TextureManager::GetInstance()->CreateTextureFromText(&player1_name, font, n_player1.c_str(), {150, 0, 255});
}
void Select::Render(){
    TextureManager::GetInstance()->Render("background", 0, 0, WIDTH, HEIGHT);
    TextureManager::GetInstance()->Render(selected_skin.c_str(), 0, 0, 32, 32, 4.0f);
    if (mode == 2) TextureManager::GetInstance()->Render(selected_skin1.c_str(), 0, 400, 32, 32, 4.0f);
    
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), selected_minutes, nullptr, &minute_box);

    SDL_Rect temp;
    if (n_player.length() > 0) MakeRectFromTexture(&player_name, &temp, 0, 300);
    if (n_player.length() > 0) SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player_name, nullptr, &temp);
    if (mode == 2 && n_player1.length() > 0) MakeRectFromTexture(&player1_name, &temp, 0, 600);
    if (mode == 2 && n_player1.length() > 0) SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player1_name, nullptr, &temp);
    if (n_player.length() > 0)SDL_DestroyTexture(player_name);
    if (mode == 2 && n_player1.length() > 0) SDL_DestroyTexture(player1_name);

    if ((mode == 1 && !name_entered) || (mode == 2 && !name1_entered)){
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &name_box);
    }
    
    if ((!skin_has_been_selected && name_entered && mode == 1) || (!skin_has_been_selected && name_entered && name1_entered && mode == 2)) {
        SDL_Rect a = {0, 0, 32*4, 32*4};
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &a);
    }
    if (!skin1_has_been_selected && mode == 2 && name1_entered && name_entered){
        SDL_Rect a = {0, 400, 32*4, 32*4};
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &a);
    }
    if (mode == 1 && skin_has_been_selected && name_entered) {
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &minute_box);
    }
    else if (mode == 2 && skin_has_been_selected && skin1_has_been_selected && name1_entered && name_entered) {
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &minute_box);
    }
}

void Select::KeyText(SDL_Event event){
    if (n_player.length() <= max_name_char && !name_entered){
        if (*event.text.text >= 'a' && *event.text.text <= 'z') n_player += *event.text.text;
        else if (*event.text.text >= 'A' && *event.text.text <= 'Z') n_player += *event.text.text;
        else if (*event.text.text >= '0' && *event.text.text <= '9') n_player += *event.text.text;
        if (*event.text.text == ' ') n_player += *event.text.text;
    }
    else if (n_player1.length() <= max_name_char && !name1_entered && mode == 2 && name_entered){
        if (*event.text.text >= 'a' && *event.text.text <= 'z') n_player1 += *event.text.text;
        else if (*event.text.text >= 'A' && *event.text.text <= 'Z') n_player1 += *event.text.text;
        else if (*event.text.text >= '0' && *event.text.text <= '9') n_player1 += *event.text.text;
        if (*event.text.text == ' ') n_player1 += *event.text.text;
    }
}

void Select::KeyDown(SDL_Scancode scancode){
    if ((!name_entered && mode == 1) || (!name1_entered && mode == 2)) {
        switch(scancode){
            case SDL_SCANCODE_BACKSPACE:
                if (!name_entered && n_player.length() > 0) n_player.erase(n_player.end()-1, n_player.end());
                else if (!name1_entered && n_player1.length() > 0) n_player1.erase(n_player1.end()-1, n_player1.end());
                break;
            case SDL_SCANCODE_RETURN:
                if (!name_entered) name_entered = true;
                else if (!name1_entered) name1_entered = true;
                name_box.y = 600;
                break;
            case SDL_SCANCODE_ESCAPE:
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
                return;
                break;
        }
        return;
    }
    if (skin_has_been_selected == false){
        switch (scancode){
            case SDL_SCANCODE_LEFT:
                Skins_iterator--;
                if (Skins_iterator < 0) Skins_iterator = vectorSkins.size()-1;
                selected_skin = vectorSkins[Skins_iterator];
                break;
            case SDL_SCANCODE_RIGHT:
                Skins_iterator++;
                if (Skins_iterator == vectorSkins.size()) Skins_iterator = 0;
                selected_skin = vectorSkins[Skins_iterator];
                break;
            case SDL_SCANCODE_RETURN:
                skin_has_been_selected = true;
                return;
                break;
            case SDL_SCANCODE_ESCAPE:
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
                return;
                break;
        }
    }
    if (!skin1_has_been_selected && mode == 2){
        switch (scancode){
            case SDL_SCANCODE_A:
                Skins1_iterator--;
                if (Skins1_iterator < 0) Skins1_iterator = vectorSkins.size()-1;
                selected_skin1 = vectorSkins[Skins1_iterator];
                break;
            case SDL_SCANCODE_D:
                Skins1_iterator++;
                if (Skins1_iterator == vectorSkins.size()) Skins1_iterator = 0;
                selected_skin1 = vectorSkins[Skins1_iterator];
                break;
            case SDL_SCANCODE_RETURN:
                skin1_has_been_selected = true;
                return;
                break;
            case SDL_SCANCODE_ESCAPE:
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
                return;
                break;
        }
    }
    if ((skin_has_been_selected && mode == 1) || (mode == 2 && skin_has_been_selected && skin1_has_been_selected)) {
        switch (scancode){
            case SDL_SCANCODE_LEFT:
                Select::GetInstance()->Minute_iterator--;
                Select::GetInstance()->minute_per_sun-=15;
                if (Select::GetInstance()->Minute_iterator < 0) Select::GetInstance()->Minute_iterator = Select::GetInstance()->vectorMinute.size()-1;
                if (Select::GetInstance()->minute_per_sun == 0) Select::GetInstance()->minute_per_sun = 45;
                Select::GetInstance()->selected_minutes = Select::GetInstance()->vectorMinute[Select::GetInstance()->Minute_iterator];
                break;
            case SDL_SCANCODE_RIGHT:
                Select::GetInstance()->Minute_iterator++;
                Select::GetInstance()->minute_per_sun += 15;
                if (Select::GetInstance()->Minute_iterator == Select::GetInstance()->vectorMinute.size()) Select::GetInstance()->Minute_iterator = 0;
                if (Select::GetInstance()->minute_per_sun == 60) Select::GetInstance()->minute_per_sun = 0;
                Select::GetInstance()->selected_minutes = Select::GetInstance()->vectorMinute[Select::GetInstance()->Minute_iterator];
                break;
            case SDL_SCANCODE_RETURN:
                SceneManager::GetInstance()->ChangeScene(PLAYSCENE);
                return;
                break;
            case SDL_SCANCODE_ESCAPE:
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
    TTF_Font* font = TextureManager::GetInstance()->LoadFont("res/Fonts/Freedom.ttf", 20);
    name = Select::GetInstance()->n_player;
    if (Select::GetInstance()->mode == 2) name1 = Select::GetInstance()->n_player1;
    TextureManager::GetInstance()->CreateTextureFromText(&player_name, font, name.c_str(), {255, 255, 0});
    if (Select::GetInstance()->mode == 2) TextureManager::GetInstance()->CreateTextureFromText(&player1_name, font, name1.c_str(), {255, 255, 0});
    TTF_CloseFont(font);
    player = new Player(new Properties(Select::GetInstance()->selected_skin.c_str(), 0, 0, 32, 32, ID, 1, 0, 2.0f, 6));
    if (Select::GetInstance()->mode == 2) player1 = new Player1(new Properties(Select::GetInstance()->selected_skin1.c_str(), 0, 0, 32, 32, ID, 1, 0, 2.0f, 6));
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
    SDL_DestroyTexture(player_name);
    SDL_DestroyTexture(player1_name);
}
void Scene_0::Update(float& dt){
    spawnSun += dt;
    UpdateIdle(dt);
    if (spawnSun >= 1 && countSun < max_sun){
        Planet* sun = new Planet(new Properties("sun", 592, 2, 48, 48, ID, 1, 0, 1/3.0f, 9));
        spawnSun = 0;
        countSun++;
    }
    GameObjectHandler::GetInstance()->Update(dt);
    if (HOURS.first == 24) {
        DAYS++;
        countMoon = DAYS;
        HOURS = {0, 0};
        countSun = 0;
        Planet* moon = new Planet(new Properties("moon", 592, 2, 48, 48, ID, 1, 0, 1.0f, 8));
    }
    {
        std::string front = std::to_string(HOURS.first), end = std::to_string(HOURS.second);
        if (HOURS.first < 10) front = "0" + std::to_string(HOURS.first);
        if (HOURS.second == 0) end = "00";
        _time = front + ":" + end;
    }
}

void Scene_0::Render(){
    TextureManager::GetInstance()->Render("background", 0, 0, WIDTH, HEIGHT);
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
    MakeRectFromTexture(&player_name, &p_rect, Player::GetInstance()->getTransform()->x, Player::GetInstance()->getTransform()->y-20);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player_name, nullptr, &p_rect);
    if (Player1::GetInstance() != nullptr) MakeRectFromTexture(&player1_name, &p1_rect, Player1::GetInstance()->getTransform()->x, Player1::GetInstance()->getTransform()->y-20);
    if (Player1::GetInstance() != nullptr) SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), player1_name, nullptr, &p1_rect);
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
    if (scancode == PLAYER_JUMP_SCANCODE && ((Player::GetInstance()->GetRemainJumps() == 2 && (SDL_GetTicks() - Player::GetInstance()->lastJump >= 0)) || Player::GetInstance()->GetRemainJumps() == 1)/* && Player::GetInstance()->GetAllowInput() == true*/){
        if (Player::GetInstance()->GetRemainJumps() == 2) {
            Player::GetInstance()->JumpDust1.SetProp("Jump_Dust", 0, 5, 80);
            Player::GetInstance()->lastJump = SDL_GetTicks();
            Player::GetInstance()->j1_x = Player::GetInstance()->getTransform()->x+5;
            Player::GetInstance()->j1_y = Player::GetInstance()->getTransform()->y + Player::GetInstance()->getCollider().GetBox().h-6;
        }
        else {
            Player::GetInstance()->JumpDust2.SetProp("Jump_Dust", 0, 5, 80);
            Player::GetInstance()->j2_x = Player::GetInstance()->getTransform()->x+5;
            Player::GetInstance()->j2_y = Player::GetInstance()->getTransform()->y + Player::GetInstance()->getCollider().GetBox().h-6;
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
        Player::GetInstance()->SetPrevState();
        Player::GetInstance()->NeedChangeState() = true;
        if (Player::GetInstance()->GetState().second == RIGHT){
            Player::GetInstance()->GetRigidBody()->applyAccelerationX(BACKWARD * DECCELERATE_TO_ZERO);
            Player::GetInstance()->SetState(STATE::STANDING, FACE::RIGHT);
        }
        else if (Player::GetInstance()->GetState().second == LEFT){
            Player::GetInstance()->GetRigidBody()->applyAccelerationX(FORWARD * DECCELERATE_TO_ZERO);
            Player::GetInstance()->SetState(STATE::STANDING, FACE::LEFT);
        }
        if (Player::GetInstance()->GetState().first == RUNNING && Player::GetInstance()->GetState().second == RIGHT){
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

    font = TextureManager::GetInstance()->LoadFont("res/Fonts/Freedom.ttf", 70);

    TextureManager::GetInstance()->CreateTextureFromText(&Resume, font, "Resume", {0, 255, 200});
    MakeRectFromTexture(&Resume, &resume_rect, 0, 0);
    TextureManager::GetInstance()->CreateTextureFromText(&Menu, font, "Menu", {100, 255, 200});
    MakeRectFromTexture(&Menu, &menu_rect, 500, 0);

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

    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Resume, nullptr, &resume_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Menu, nullptr, &menu_rect);

    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), currentRect);
}

void Pause::KeyDown(SDL_Scancode scancode){
    switch (scancode)
    {
    case SDL_SCANCODE_LEFT:
        i--;
        if (i < 0) i = vectorRect.size() - 1;
        currentRect = vectorRect[i];
        break;
    case SDL_SCANCODE_RIGHT:
        i++;
        if (i == vectorRect.size()) i = 0;
        currentRect = vectorRect[i];
        break;
    case SDL_SCANCODE_RETURN:
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