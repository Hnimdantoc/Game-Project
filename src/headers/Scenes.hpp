#pragma once

#include "Scene.hpp"
#include "Player.hpp"
#include "Player1.hpp"
#include "SceneManager.hpp"
#include "Planet.hpp"
#include "Hover_platform.hpp"
#include <utility>
#include <vector>


class Menu : public Scene
{
public:
    static Menu* GetInstance(){return static_instance;}
    int i = 0, j = 0;
    bool mode_2;
    SDL_Rect* currentRect;
    inline std::vector<std::vector<SDL_Rect*>> GetVectorRect(){return vectorRect;}
private:
    static Menu* static_instance;
    int ID;
    bool ChoosingMode;
    TTF_Font* font;
    TTF_Font* title;
    SDL_Texture* Play;
    SDL_Texture* Title;
    SDL_Texture* Option;
    SDL_Texture* Exit;
    SDL_Texture* Mode_1;
    SDL_Texture* Mode_2;
    SDL_Rect play_rect, option_rect, title_rect, exit_rect, mode_1_rect, mode_2_rect;
    std::vector <std::vector<SDL_Rect*>> vectorRect;
public:
    Menu();
    ~Menu();
    void Update(float& dt);
    void Render();
    void KeyDown(SDL_Scancode scancode);
    void KeyUp(SDL_Scancode scancode);
};

class Select : public Scene
{
public: 
    static Select* GetInstance(){return static_instance;}
    int minute_per_sun, mode;
    bool skin_has_been_selected, skin1_has_been_selected;
    int Skins_iterator = 0, Skins1_iterator = 0, Minute_iterator = 1;
    SDL_Texture* selected_minutes;
    std::string selected_skin = "player";
    std::string selected_skin1 = "player";
    std::vector <std::string> vectorSkins;
    std::vector <SDL_Texture*> vectorMinute;
private:
    static Select* static_instance;
    int ID;
    TTF_Font* font;
    SDL_Rect minute_box;
    SDL_Texture* fifteen;
    SDL_Texture* thirty;
    SDL_Texture* forty_five;
public:
    Select();
    ~Select();
    void Update(float& dt);
    void Render();
    void KeyDown(SDL_Scancode scancode);
    void KeyUp(SDL_Scancode scancode);
};

class Scene_0 : public Scene
{
public:
    static Scene_0* GetInstance(){return static_instance;}
    int DAYS;
    int max_sun;
    std::string _time;
    std::pair <int, int> HOURS;
private:
    static Scene_0* static_instance;
    int ID;
    float spawnSun = 0;
    int countSun, countMoon;
    int samurai_x = 210, GO = 1;
    TTF_Font* freedom;
    Player1* player1;
    Player* player;
    GameObject* Left_platform;
    GameObject* Right_platform;
    SDL_Texture* hours_texture;  
    SDL_Texture* days_texture;  
    Hover_platform* hover_platform;
    Animation samurai_merchant_idle;
    Animation Rockstand_merchant_idle;
public:
    Scene_0();
    ~Scene_0();
    void Update(float& dt);
    void Render();
    void KeyDown(SDL_Scancode scancode);
    void KeyUp(SDL_Scancode scancode);
    void UpdateIdle(float dt);
    void RenderSamuraiMerchant();
};

class Pause : public Scene {
public:
    static Pause* GetInstance(){return static_instance;}
    int i = 0;
    std::vector<SDL_Rect*> vectorRect;
private:
    static Pause* static_instance;
    int ID;
    TTF_Font* font;
    SDL_Texture* Resume;
    SDL_Texture* Menu;
    SDL_Texture* background;
    SDL_Rect* currentRect;
    SDL_Rect resume_rect, menu_rect;
public:
    Pause();
    ~Pause();
    void KeyDown(SDL_Scancode scancode);
    void KeyUp(SDL_Scancode scancode);
    void Update(float& dt);
    void Render();
};