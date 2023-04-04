#include "Scenes.hpp"
/********************************************************************************/
Menu* Menu::static_instance = nullptr;
Menu::Menu() : ID(MENU_SCENE) {        
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;
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

    currentRect = &play_rect;
    vectorRect.push_back({&play_rect, &option_rect, &exit_rect});
}
Menu::~Menu(){
    TTF_CloseFont(font);
    TTF_CloseFont(title);
    SDL_DestroyTexture(Title);
    SDL_DestroyTexture(Play);
    SDL_DestroyTexture(Option);
    SDL_DestroyTexture(Exit);
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
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), currentRect);
}

void Menu::KeyDown(SDL_Scancode scancode){
    switch(scancode){
        case SDL_SCANCODE_DOWN:
            Menu::GetInstance()->j++;
            if (Menu::GetInstance()->j == Menu::GetInstance()->GetVectorRect()[Menu::GetInstance()->i].size()) Menu::GetInstance()->j = 0;
            Menu::GetInstance()->currentRect = Menu::GetInstance()->GetVectorRect()[Menu::GetInstance()->i][Menu::GetInstance()->j];
            break;
        case SDL_SCANCODE_UP:
            Menu::GetInstance()->j--;
            if (Menu::GetInstance()->j < 0) Menu::GetInstance()->j = Menu::GetInstance()->GetVectorRect()[Menu::GetInstance()->i].size()-1;
            Menu::GetInstance()->currentRect = Menu::GetInstance()->GetVectorRect()[Menu::GetInstance()->i][Menu::GetInstance()->j];
            break;
        case SDL_SCANCODE_RETURN:
            if (Menu::GetInstance()->currentRect == &play_rect) SceneManager::GetInstance()->ChangeScene(SELECT_SCENE);
            else if (Menu::GetInstance()->currentRect == &exit_rect) {
                Engine::GetInstance()->setGameState() = GAME_STATE::EXIT;
                return;
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

    skin_has_been_selected = false;
    minute_per_sun = 30;
    TextureManager::GetInstance()->CreateTextureFromText(&fifteen, font, "15", {0, 0, 0, 255});
    TextureManager::GetInstance()->CreateTextureFromText(&thirty, font, "30", {0, 0, 0, 255});
    selected_minutes = thirty;
    TextureManager::GetInstance()->CreateTextureFromText(&forty_five, font, "45", {0, 0, 0, 255});

    minute_box.x = 600;
    minute_box.y = 0;
    SDL_QueryTexture(thirty, nullptr, nullptr, &minute_box.w, &minute_box.h);

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
}
void Select::Update(float& dt){
    
}
void Select::Render(){
        TextureManager::GetInstance()->Render("background", 0, 0, WIDTH, HEIGHT);
        TextureManager::GetInstance()->Render(selected_skin.c_str(), 0, 0, 32, 32, 4.0f);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), selected_minutes, nullptr, &minute_box);

        if (!skin_has_been_selected) {
            SDL_Rect a = {0, 0, 32*4, 32*4};
            SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &a);
        }
        else {
            SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &minute_box);
        }
    }

void Select::KeyDown(SDL_Scancode scancode){
    if (Select::GetInstance()->skin_has_been_selected == false){
        switch (scancode){
            case SDL_SCANCODE_LEFT:
                Select::GetInstance()->Skins_iterator--;
                if (Select::GetInstance()->Skins_iterator < 0) Select::GetInstance()->Skins_iterator = Select::GetInstance()->vectorSkins.size()-1;
                Select::GetInstance()->selected_skin = Select::GetInstance()->vectorSkins[Select::GetInstance()->Skins_iterator];
                break;
            case SDL_SCANCODE_RIGHT:
                Select::GetInstance()->Skins_iterator++;
                if (Select::GetInstance()->Skins_iterator == Select::GetInstance()->vectorSkins.size()) Select::GetInstance()->Skins_iterator = 0;
                Select::GetInstance()->selected_skin = Select::GetInstance()->vectorSkins[Select::GetInstance()->Skins_iterator];
                break;
            case SDL_SCANCODE_RETURN:
                Select::GetInstance()->skin_has_been_selected = true;
                break;
            case SDL_SCANCODE_ESCAPE:
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
                return;
                break;
        }
    }
    else {
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

    player = new Player(new Properties(Select::GetInstance()->selected_skin.c_str(), 0, 0, 32, 32, ID, 1, 0, 2.0f, 6));
    player1 = new Player1(new Properties(Select::GetInstance()->selected_skin.c_str(), 0, 0, 32, 32, ID, 1, 0, 2.0f, 6));
    hover_platform = new Hover_platform(new Properties("Hover_platform", 525, 437, 150, 74, ID, 1));

    Planet* moon = new Planet(new Properties("moon", 592, 2, 48, 48, ID, 1, 0, 1.0f, 8));
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
        SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
        return;
    }
    if (Input::GetInstance()->GetKeyState()[PLAYER_GO_RIGHT_SCANCODE] && scancode == PLAYER_GO_LEFT_SCANCODE) Player::GetInstance()->SetSmoothMovement() = true;
    if (Input::GetInstance()->GetKeyState()[PLAYER_GO_LEFT_SCANCODE] && scancode == PLAYER_GO_RIGHT_SCANCODE) Player::GetInstance()->SetSmoothMovement() = false;
    //////////////////////////////////////////
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