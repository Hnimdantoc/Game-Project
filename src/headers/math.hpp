#pragma once

#include <iostream>

class Vector
{
public:
    Vector();
    Vector(float _x, float _y);
    ~Vector();

    Vector operator + (Vector one)  {
        return {this->x + one.x, this->y + one.y};
    }
    Vector operator - ( Vector one){
        return {this->x - one.x,this->y - one.y};
    }
    Vector operator * (Vector one)  {
        return {this->x * one.x, this->y * one.y};
    }
    Vector operator * (float one)  {
        return {this->x * one, this->y * one};
    }
    Vector operator / (Vector one)  {
        return {this->x / one.x, this->y / one.y};
    }
    Vector operator / (float one)  {
        return {this->x / one, this->y / one};
    }

    float x, y;
    void print();
private:
    
};

