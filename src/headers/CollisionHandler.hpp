#pragma once

#include "SDL2/SDL.h"
#include "Collider.hpp"
class CollisionHandler
{
public:
    bool CheckCollision(Collider& _rectA, Collider& _rectB);
    bool GroundCollision(Collider& _rect);

    inline static CollisionHandler* GetInstance(){return StaticInstance = (StaticInstance != nullptr) ? StaticInstance : new CollisionHandler();}

    void PlayerCollisions(Collider& _PlayerRect);
    ~CollisionHandler();
private:
    CollisionHandler();
    
    static CollisionHandler* StaticInstance;
};