#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include "GameObjectHandler.hpp"
#include "TextureManager.hpp"

class Trail : public GameObject
{
private:
    int x, y, alpha = 255;
public:
    Trail(int x, int y, int w, int h, int dir);
    ~Trail();

    void Update(float& dt);
    void Render();
    void Clean();
};