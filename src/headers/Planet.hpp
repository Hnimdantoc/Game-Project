#pragma once

#include "GameObject.hpp"
#include <math.h>

class Planet : public GameObject
{
public:
    Planet();
    Planet(Properties* prop);
    ~Planet();

    void Render();
    void Update(float& dt);
    void Clean();
    float speed = 2.0f;
    Vector move;
    std::vector<Vector> dir = 
    {
        {(float)-sqrt(2) * speed, (float)sqrt(2) * speed},
        {(float)sqrt(2) * speed, (float)sqrt(2)  * speed},
        {(float)-sqrt(3) * speed, 1* speed},
        {(float)sqrt(3) * speed, 1 * speed},
        {-1 * speed, (float)sqrt(3) * speed},
        {1 * speed, (float)sqrt(3) * speed}
    };
};