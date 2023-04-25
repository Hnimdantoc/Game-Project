#include "input.hpp"
#include "Player.hpp"
#include "Planet.hpp"
#include "SceneManager.hpp"
#include "Scenes.hpp"

Input* Input::static_Instance = nullptr;

Input::Input(){
    KeyState = SDL_GetKeyboardState(NULL);
}   

Input::~Input(){
    SDL_Log("Input Handler destroyed");
}

void Input::Listen(){    
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                Engine::GetInstance()->setGameState() = GAME_STATE::EXIT;
                break;
            case SDL_TEXTINPUT:
                if (SceneManager::GetInstance()->GetCurrentSceneID() == SELECT_SCENE) Select::GetInstance()->KeyText(event);
                break;
            case SDL_MOUSEMOTION:
                SceneManager::GetInstance()->MouseMotion();
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_KEYUP:
                KeyUp();
                break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key_scan_code){
    return KeyState[key_scan_code] == 1;
}

void Input::KeyUp(){
    KeyState = SDL_GetKeyboardState(NULL);
    SceneManager::GetInstance()->KeyUp(event.key.keysym.scancode);
}

void Input::KeyDown(){
    KeyState = SDL_GetKeyboardState(NULL);
    SceneManager::GetInstance()->KeyDown(event.key.keysym.scancode);
}