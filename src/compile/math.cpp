#include "math.hpp"

Vector::Vector() : x(0.0f), y(0.0f) {}

Vector::Vector(float _x, float _y) : x(_x), y(_y){
    
}

Vector::~Vector(){}

void Vector::print(){
    std::cout << "x: " << x << " | " << "y: " << y << std::endl;
}

