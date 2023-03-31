#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "input.hpp"

#define WIDTH 1200
#define HEIGHT 675
#define GAME_TITLE "Holy War"

#define Ground_H 0 // Modifiable
#define Ground_X 0 // Const
#define Ground_Y HEIGHT-Ground_H // Const
#define Ground_W WIDTH // Const

#define PLAYER_SCALE 2
#define MENU_SCENE 0
#define PLAYSCENE 1

#define ICON_PATH "res/Icon/t1.png"
#define R 140
#define G 190
#define B 180

enum GAME_STATE {PLAYING, EXIT};

class Engine
{
public:
    static Engine* GetInstance(){return static_Instance = (static_Instance != nullptr) ? static_Instance : new Engine();}
    
    void init(const char* title, int x, int y, int w, int h, Uint32 flags);
    void Quit();

    inline GAME_STATE getGameState(){return _gameState;}
    inline GAME_STATE& setGameState(){return _gameState;}
    inline SDL_Renderer* GetRenderer(){return renderer;}
    inline SDL_Rect GetGround(){return _Ground;}

    void Events();
    void Update(float dt);
    void Render();    
private:
    Engine();
    ~Engine();

    static Engine* static_Instance;

    GAME_STATE _gameState = GAME_STATE::PLAYING;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* icon;
    
    SDL_Rect _Ground;
};


