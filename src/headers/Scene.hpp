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
};