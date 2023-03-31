#pragma once

#include "GameObject.hpp"

class Hover_platform : public GameObject
{
public:
    Hover_platform();
    Hover_platform(Properties* prop);
    ~Hover_platform();

    void Render();
    void Update(float& dt);
    void Clean();

    inline void UpdateCollider(){
        _Collider.GetBox().x = _Transform->x;
        _Collider.GetBox().y = _Transform->y + 13;
    }

    int GO = 1;
};