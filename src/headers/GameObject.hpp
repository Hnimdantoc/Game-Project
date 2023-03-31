#pragma once

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "RigidBody2D.hpp"
#include "Transform.hpp"
#include "Animation.hpp"
#include "Collider.hpp"


#define OFFSET 15

class Properties
{
public:
    Properties();
    Properties(const char* _ID, int _x, int _y, int _w, int _h, int _scene, int _layer = 0, int _spriteRow = 0, float _scale = 1.0f, int _frameCount = 0) : ID(_ID), x(_x), y(_y), w(_w), h(_h), layer(_layer), scene(_scene), scale(_scale), frameCount(_frameCount), spriteRow(_spriteRow) {}
    
public:
    const char* ID;
    float x, y, scale;
    int w, h, layer, scene, frameCount, spriteRow;
};


class GameObject
{
public:
    GameObject();
    GameObject(Properties* prop);
    ~GameObject();

    virtual void Render();
    virtual void Update(float& dt);
    virtual void Clean();

    virtual const char* GetID(){return ID;}
    virtual inline Transform* getTransform(){return _Transform;}
    virtual inline SDL_Texture* getTexture(){return texture;}
    virtual inline SDL_Rect* getRect(){return &_Rect;}
    virtual inline Collider& getCollider(){return _Collider;}
    virtual inline RigidBody2D* GetRigidBody(){return _RigidBody;}
    virtual inline Transform* SetTransform(){return _Transform;}
    virtual inline int GetLayer(){return layer;}
    virtual inline void UpdateCollider(){
        _Collider.GetBox().x = _Transform->x;
        _Collider.GetBox().y = _Transform->y;
    }

protected:
    const char* ID;
    int w, h, _scene, layer;
    float scale;

    RigidBody2D* _RigidBody;
    Transform* _Transform;
    SDL_Rect _Rect;
    SDL_Texture* texture;
    Animation* _Animation;
    Collider _Collider;
};