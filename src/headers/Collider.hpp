#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Collider
{
private:
    int x, y, w, h;
    SDL_Rect box;
public:
    Collider();
    Collider(SDL_Rect _Rect){box = _Rect;}
    ~Collider();

    void Render();
    inline void UpdateBox(SDL_Rect& _Rect){box = _Rect;};
    inline SDL_Rect& GetBox(){return box;};
};