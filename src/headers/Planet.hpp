#pragma once

#include "GameObject.hpp"
#include <math.h>

class Planet : public GameObject
{
private:
    float speed = 2.0f;
    Vector move;
public:
    Planet();
    Planet(Properties* prop);
    ~Planet();
    inline void UpdateCollider(){
        if (strcmp(ID, "moon") == 0) {
            _Collider.GetBox().x = _Transform->x + 5;
            _Collider.GetBox().y = _Transform->y + 5;
        }else {
            _Collider.GetBox().x = _Transform->x;
            _Collider.GetBox().y = _Transform->y;
        }
    }
    void SunCollision();
    void MoonCollision();

    void Render();
    void Update(float& dt);
    void Clean();
    
    std::vector<Vector> dir = 
    {

        {-1 * speed, (float)sqrt(3) * speed},
        {1 * speed, (float)sqrt(3) * speed},
        {(float)-sqrt(3) * speed, 1 * speed},
        {(float)sqrt(3) * speed, 1 * speed},
        {(float)-sqrt(2) * speed, (float)sqrt(2) * speed},
        {(float)sqrt(2) * speed, (float)sqrt(2)  * speed}
    };
};