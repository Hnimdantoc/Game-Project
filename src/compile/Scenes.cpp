#include "Scenes.hpp"
/********************************************************************************/
Menu* Menu::static_instance = nullptr;
Menu::Menu() : ID(MENU_SCENE) {        
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;
    font = TextureManager::GetInstance()->LoadFont("res/Fonts/Freedom.ttf", 70);
    title = TextureManager::GetInstance()->LoadFont("res/Fonts/arcade.ttf", 100);

    Play = TextureManager::GetInstance()->CreateTextureFromText(font, "PLAY", {255, 255, 255});
    play_rect.x = 500;
    play_rect.y = 300;
    SDL_QueryTexture(Play, nullptr, nullptr, &play_rect.w, &play_rect.h);

    Title = TextureManager::GetInstance()->CreateTextureFromText(font, "T1 < DEFT", {0, 255, 0});
    title_rect.x = 500;
    title_rect.y = 0;
    SDL_QueryTexture(Title, nullptr, nullptr, &title_rect.w, &title_rect.h);

    Option = TextureManager::GetInstance()->CreateTextureFromText(font, "OPTION", {255, 255, 0});
    option_rect.x = 500;
    option_rect.y = 500;
    SDL_QueryTexture(Option, nullptr, nullptr, &option_rect.w, &option_rect.h);

    currentRect = &play_rect;
    vectorRect.push_back({&play_rect, &option_rect});
}
Menu::~Menu(){
    TTF_CloseFont(font);
    TTF_CloseFont(title);
    SDL_DestroyTexture(Play);
    SDL_DestroyTexture(Option);
    SDL_DestroyTexture(Title);
}
void Menu::Update(float& dt){
    GameObjectHandler::GetInstance()->Update(dt);
}
void Menu::Render(){
    TextureManager::GetInstance()->Render("background", 0, 0, WIDTH, HEIGHT);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Play, nullptr, &play_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Option, nullptr, &option_rect);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Title, nullptr, &title_rect);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), currentRect);
}

/********************************************************************************/
Select* Select::static_instance = nullptr;
Select::Select() : ID(SELECT_SCENE){
    SceneManager::GetInstance()->addScene(ID, this);
    static_instance = this;

    font = TextureManager::GetInstance()->LoadFont("res/Fonts/Freedom.ttf", 40);

    skin_has_been_selected = false;
    minute_per_sun = 30;
    fifteen = TextureManager::GetInstance()->CreateTextureFromText(font, "15", {0, 0, 0, 255});
    thirty = TextureManager::GetInstance()->CreateTextureFromText(font, "30", {0, 0, 0, 255});
    selected_minutes = thirty;
    forty_five = TextureManager::GetInstance()->CreateTextureFromText(font, "45", {0, 0, 0, 255});

    minute_box.x = 600;
    minute_box.y = 0;
    SDL_QueryTexture(thirty, nullptr, nullptr, &minute_box.w, &minute_box.h);

    vectorMinute.push_back(fifteen);
    vectorMinute.push_back(thirty);
    vectorMinute.push_back(forty_five);
    vectorSkins.push_back("player");
    vectorSkins.push_back("player1");
}
Select::~Select(){
    TTF_CloseFont(font);
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
    hours_texture = TextureManager::GetInstance()->CreateTextureFromText(freedom, _time.c_str(), {255, 0, 0, 150});
    SDL_Rect hours_rect = {391, 185, 0 ,0};
    SDL_QueryTexture(hours_texture, nullptr, nullptr, &hours_rect.w, &hours_rect.h);
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(),hours_texture, nullptr, &hours_rect);
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