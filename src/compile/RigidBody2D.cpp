#include "RigidBody2D.hpp"
#include "SDL2/SDL.h"
#include "Player.hpp"
#include "Player1.hpp"


RigidBody2D::RigidBody2D(){
    // Set mass and gravity value
    _mass = MASS;
    _gravity = GRAVITY;
}

RigidBody2D::~RigidBody2D(){}

void RigidBody2D::Update(float dt){
    // Use this to push objects
    _acceleration.x = (_force.x + _friction.x) / _mass + _acceleration.x;
    
    // Movement in air
    // Gravitational acceleration
    _acceleration.y = _gravity + _force.y / _mass;
    /*----------------------------------Movemen in y axis----------------------------------*/
    _velocity.y = _acceleration.y * dt + _velocity.y;
    if (_velocity.y <= JUMP_VELOCITY*UPWARD) _velocity.y = JUMP_VELOCITY*UPWARD;
    else if (_velocity.y >= JUMP_VELOCITY) _velocity.y = JUMP_VELOCITY;

    _position.y = _velocity.y * dt + 0.5f * _acceleration.y * dt * dt;
    // Allow player's input after certain velocity threshold
    if (Player::GetInstance()->GetRigidBody()->getVelocity().y >= -0.25f*JUMP_VELOCITY && Player::GetInstance()->GetInAir()) Player::GetInstance()->SetAllowInput() = true;
    if (Player1::GetInstance() != nullptr) if (Player1::GetInstance()->GetRigidBody()->getVelocity().y >= -0.25f*JUMP_VELOCITY && Player1::GetInstance()->GetInAir()) Player1::GetInstance()->SetAllowInput() = true;
    /*----------------------------------Movemen in x axis----------------------------------*/
    // Deccelerator
    if (_acceleration.x == DECCELERATE_TO_ZERO * BACKWARD && _velocity.x <= 0) resetAccelerationX();
    else if (_acceleration.x == DECCELERATE_TO_ZERO * FORWARD && _velocity.x >= 0) resetAccelerationX();
    // Velocity limiter
    // Apply velocity to get position and update velocity
    _velocity.x = _acceleration.x * dt + _velocity.x;
    _position.x = _velocity.x * dt;
    if (_velocity.x >= MAX_VELOCITTY) _velocity.x = MAX_VELOCITTY;
    else if (_velocity.x <= -MAX_VELOCITTY) _velocity.x = -MAX_VELOCITTY;
    _acceleration.x -= (_force.x + _friction.x) / _mass;
    // Stop movement after acceleration equal 0
    if (abs(_acceleration.x) <= 0){
        resetForceX();
        resetVelocityX();
        resetFriction();
    }
}


