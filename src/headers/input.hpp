#pragma once

#include <iostream>
#include "SDL2/SDL.h"

class Input
{
private:
    const Uint8* KeyState;
    static Input* static_Instance;
    SDL_Event event;
public:
    static Input* GetInstance(){return static_Instance = (static_Instance != nullptr) ? static_Instance : new Input();}
    inline const Uint8* GetKeyState(){return KeyState;}
    
    void Listen();
    void ClearKeyboard(){SDL_PumpEvents();
                         SDL_FlushEvent(SDL_KEYDOWN);
                         SDL_FlushEvent(SDL_KEYUP);}
    bool GetKeyDown(SDL_Scancode key_scan_code);
    ~Input();
private:
    Input();
    void KeyUp();
    void KeyDown();
};