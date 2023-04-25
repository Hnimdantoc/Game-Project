#pragma once
#include "GameObject.hpp"
#include "GameObjectHandler.hpp"
#include "TextureManager.hpp"

class Trail : public GameObject
{
private:
    int x, y, alpha = 255;
public:
    Trail(int x, int y, int w = 10, int h = 32);
    ~Trail();

    void Update(float& dt);
    void Render();
    void Clean();
};