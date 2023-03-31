#pragma once

#include "Scene.hpp"
#include "Player.hpp"
#include "SceneManager.hpp"
#include "Planet.hpp"
#include "Hover_platform.hpp"
#include <utility>
#include <vector>

class Scene_0 : public Scene
{
private:
    static Scene_0* static_instance;

    int samurai_x = 210, GO = 1;
    float spawnSun = 0;
    Animation samurai_merchant_idle;
    Animation Rockstand_merchant_idle;
    GameObject* Left_platform;
    GameObject* Right_platform;
    Player* player;
    Hover_platform* hover_platform;
    SDL_Texture* hours_texture;
public:
    TTF_Font* freedom;
    static Scene_0* GetInstance(){return static_instance;}
    int countSun, countMoon;
    int DAYS;
    std::pair <int, int> HOURS;
    std::string _time;
    int ID, max_sun = 1440 / 45; // Change the value, minute per sun

    Scene_0() : ID(PLAYSCENE) {
        SceneManager::GetInstance()->addScene(ID, this);
        static_instance = this;
        samurai_merchant_idle.SetProp("samurai_merchant", 0, 5, 100);
        Rockstand_merchant_idle.SetProp("Rockstand_merchant", 0, 40, 100);
        Left_platform = new GameObject(new Properties("Left_platform", 0, 506, 370, 40, ID, 1));
        Right_platform = new GameObject(new Properties("Right_platform", 830, 506, 370, 40, ID, 1));
        
        player = new Player(new Properties("player", 0, 0, 32, 32, ID, 1));
        hover_platform = new Hover_platform(new Properties("Hover_platform", 525, 437, 150, 74, ID, 1));

        Planet* moon = new Planet(new Properties("moon", 592, 2, 48, 48, ID, 1, 0, 1.0f, 8));
        countSun = 0;
        DAYS = 1;
        countMoon = DAYS;
        HOURS.first = 0;
        HOURS.second = 0;

        freedom = TextureManager::GetInstance()->LoadFont("res/Fonts/Freedom.ttf", 100);
    }
    void UpdateIdle(float dt){
        samurai_merchant_idle.Update(dt);
        Rockstand_merchant_idle.Update(dt);
    }

    void RenderSamuraiMerchant(){
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
    
    void Render(){
        TextureManager::GetInstance()->Render("background", 0, 0, WIDTH, HEIGHT);
        hours_texture = TextureManager::GetInstance()->CreateTextureFromText(freedom, _time.c_str(), {255, 0, 0, 150});
        SDL_Rect hours_rect = {391, 185, 0 ,0};
        SDL_QueryTexture(hours_texture, nullptr, nullptr, &hours_rect.w, &hours_rect.h);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(),hours_texture, nullptr, &hours_rect);
        RenderSamuraiMerchant();
        Rockstand_merchant_idle.Render(536, hover_platform->getCollider().GetBox().y-64, 128, 64);
        GameObjectHandler::GetInstance()->Render();
    }

    void Update(float& dt){
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
};

class Menu : Scene
{
public:
    static Menu* GetInstance(){return static_instance;}
    SDL_Rect* currentRect;
    int i = 0, j = 0;
    Menu() : ID(MENU_SCENE) {        
        SceneManager::GetInstance()->addScene(ID, this);
        static_instance = this;
        font = TextureManager::GetInstance()->LoadFont("res/Fonts/Freedom.ttf", 70);
    
        Play = TextureManager::GetInstance()->CreateTextureFromText(font, "PLAY", {255, 255, 255});
        play_rect.x = 500;
        play_rect.y = 0;
        SDL_QueryTexture(Play, nullptr, nullptr, &play_rect.w, &play_rect.h);

        Option = TextureManager::GetInstance()->CreateTextureFromText(font, "OPTION", {255, 255, 0});
        option_rect.x = 500;
        option_rect.y = 300;
        SDL_QueryTexture(Option, nullptr, nullptr, &option_rect.w, &option_rect.h);
        currentRect = &play_rect;
        vectorRect.push_back({&play_rect, &option_rect});
    }
    void Update(float& dt){

    }
    void Render(){
        TextureManager::GetInstance()->Render("background", 0, 0, WIDTH, HEIGHT);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Play, nullptr, &play_rect);
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), Option, nullptr, &option_rect);
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), currentRect);
    }

    inline std::vector<std::vector<SDL_Rect*>>& GetVectorRect(){return vectorRect;}
    SDL_Rect play_rect, option_rect;
private:
    static Menu* static_instance;
    TTF_Font* font;
    SDL_Texture* Play;
    SDL_Texture* Option;
    std::vector <std::vector<SDL_Rect*>> vectorRect;
    int ID;
};