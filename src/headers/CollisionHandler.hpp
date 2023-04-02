#pragma once

#include "SDL2/SDL.h"
#include "Collider.hpp"
class CollisionHandler
{
private:
    static CollisionHandler* StaticInstance;
public:
    inline static CollisionHandler* GetInstance(){return StaticInstance = (StaticInstance != nullptr) ? StaticInstance : new CollisionHandler();}
    ~CollisionHandler();

    bool CheckCollision(Collider& _rectA, Collider& _rectB);
    bool GroundCollision(Collider& _rect);
    void PlayerCollisions(Collider& _PlayerRect);
private:
    CollisionHandler();
};