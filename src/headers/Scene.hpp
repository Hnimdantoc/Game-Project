#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <map>

class Scene
{
public:
    Scene();
    ~Scene();
    virtual void Update(float& dt);
    virtual void Render();
    virtual void Clean();
    virtual void MakeRectFromTexture(SDL_Texture** texture, SDL_Rect* rect, int x, int y);
    virtual void KeyDown(SDL_Scancode scancode) = 0;
    virtual void KeyUp(SDL_Scancode scancode) = 0;
};