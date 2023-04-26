#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include "GameObjectHandler.hpp"
#include "TextureManager.hpp"

class Trail : public GameObject
{
private:
    int x, y, alpha = 80, frame, row;
    FACE face;
    SDL_RendererFlip flip;
public:
    Trail(const char* path, int frame, int row, int x, int y, int w, int h, FACE face);
    ~Trail();

    void Update(float& dt);
    void Render();
    void Clean();
};