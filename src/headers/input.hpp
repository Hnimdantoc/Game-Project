#pragma once

#include <iostream>
#include "SDL2/SDL.h"

class Input
{
public:
    static Input* GetInstance(){return static_Instance = (static_Instance != nullptr) ? static_Instance : new Input();}
    inline const Uint8* GetKeyState(){return KeyState;}
    void Listen();
    bool GetKeyDown(SDL_Scancode key_scan_code);
    ~Input();
private:
    Input();
    void KeyUp();
    void KeyDown();
    const Uint8* KeyState;
    static Input* static_Instance;
    SDL_Event event;
};