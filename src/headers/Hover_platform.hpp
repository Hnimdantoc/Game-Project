#pragma once

#include "GameObject.hpp"

class Hover_platform : public GameObject
{
public:
    int GO = 1;
public:
    Hover_platform();
    Hover_platform(Properties* prop);
    ~Hover_platform();
    
    inline void UpdateCollider(){
        _Collider.GetBox().x = _Transform->x;
        _Collider.GetBox().y = _Transform->y + 13;
    }

    void Render();
    void Update(float& dt);
    void Clean();

};