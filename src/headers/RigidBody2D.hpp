#pragma once

#include "math.hpp"
#include "Timer.hpp"

#define MAX_JUMP_HEIGHT 32 * 3
#define JUMP_TIME 36 // jump time = 32 frame

#define MASS 1.0f
#define GRAVITY 2.0f * MAX_JUMP_HEIGHT / ((JUMP_TIME/2.0f * SECONDS_PER_FRAME) * (JUMP_TIME/2.0f * SECONDS_PER_FRAME))

#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1

#define MAX_VELOCITTY 330.0f
#define JUMP_VELOCITY 2 * MAX_JUMP_HEIGHT / (JUMP_TIME/2.0f * SECONDS_PER_FRAME)
#define ACCELERATE_TO_MAX_VELOCITY (MAX_VELOCITTY / (6 * SECONDS_PER_FRAME))
#define DECCELERATE_TO_ZERO (MAX_VELOCITTY / (3 * SECONDS_PER_FRAME))

#define MAX_POS_Y JUMP_VELOCITY * SECONDS_PER_FRAME + 0.5f * SECONDS_PER_FRAME * SECONDS_PER_FRAME * GRAVITY + 1.0f

class RigidBody2D
{
public:
    RigidBody2D();
    ~RigidBody2D();
    inline void setMass(float mass){_mass = mass;}
    inline void setGravity(float gravity){_gravity = gravity;}
    inline Vector& setPosition(){return _position;}

    inline void applyForce(Vector force){_force = force;}
    inline void applyForceX(float _fX){_force.x = _fX;}
    inline void applyForceY(float _fY){_force.y = _fY;}
    inline void applyVelocityX(float _vX){_velocity.x = _vX;}
    inline void applyVelocityY(float _vY){_velocity.y = _vY;}
    inline void applyAccelerationX(float _aX){_acceleration.x = _aX;}
    inline void applyFriction(Vector friction){_friction = friction;}

    inline void resetForce(){_force = {0.0f, 0.0f};}
    inline void resetPosition(){_position = {0.0f, 0.0f};}
    inline void resetPositionY(){_position.y = 0.0f;}
    inline void resetForceX(){_force.x = 0.0f;}
    inline void resetFriction(){_friction = {0.0f, 0.0f};}
    inline void resetVelocity(){_velocity = {0.0f, 0.0f};}
    inline void resetVelocityX(){_velocity.x = 0.0f;}
    inline void resetAccelerationX(){_acceleration.x = 0.0f;}
    inline void resetVelocityY(){_velocity.y = 0.0f;}
    
    inline float getMass(){return _mass;};
    inline Vector getPosition(){return _position;};
    inline Vector getVelocity(){return _velocity;};
    inline Vector getAcceleration(){return _acceleration;};

    void Update(float dt);

private:
    float _mass, _gravity;

    Vector _force;
    Vector _friction;
    Vector _position;
    Vector _velocity;
    Vector _acceleration;
};