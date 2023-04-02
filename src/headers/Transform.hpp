#pragma once

#include "math.hpp"

class Transform
{
public:
    float x, y;
public:
    Transform();
    Transform(float _x, float _y);
    ~Transform();
    
    inline void translateX(float _x){x += _x;};
    inline void translateY(float _y){y += _y;};
    inline void translateVector(Vector vector){
        x += vector.x;
        y += vector.y;
    };
};