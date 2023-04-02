#include "Planet.hpp"
#include "GameObjectHandler.hpp"
#include "CollisionHandler.hpp"
#include <time.h>
#include <cstdlib>

Planet::Planet(){}

Planet::Planet(Properties* prop){
    ID = prop->ID;
    w = prop->w;
    h = prop->h;
    layer = prop->layer;
    _scene = prop->scene;
    scale = prop->scale;
    GameObjectHandler::GetInstance()->addObject(_scene, this);
    _Transform = new Transform(prop->x, prop->y);
    _Animation = new Animation();
    _Animation->SetProp(ID, prop->spriteRow, prop->frameCount, 100);
    srand(time(NULL));
    move = dir[rand() % dir.size()];
    _Rect.x = _Transform->x;
    _Rect.y = _Transform->y;
    _Rect.w = w * prop->scale;
    _Rect.h = h * prop->scale;
    _Collider = Collider(_Rect);
    delete prop;
}

Planet::~Planet(){}

void Planet::Update(float& dt){
    if (_Collider.GetBox().x <= 0 || _Collider.GetBox().x >= WIDTH - _Collider.GetBox().w) {
        move.x *= -1;
        if (_Collider.GetBox().x <= 0) _Transform->x = 0;
        else _Transform->x = WIDTH - _Collider.GetBox().w;
    }
    if (_Collider.GetBox().y <= 0 || _Collider.GetBox().y >= HEIGHT - _Collider.GetBox().h) {
        move.y *= -1;
        if (_Collider.GetBox().y <= 0) _Transform->y = 0;
        else _Transform->y = HEIGHT - _Collider.GetBox().h;
    }
    
    Collider left({0, 506, 370, 40});
    Collider right({830, 506, 370, 40});
    Collider hover_plat = GameObjectHandler::GetInstance()->GetGameObject(PLAYSCENE, "Hover_platform")->getCollider();

    if (CollisionHandler::GetInstance()->CheckCollision(_Collider, left)){
        if (_Collider.GetBox().y >= left.GetBox().y - _Collider.GetBox().h && _Collider.GetBox().y <= left.GetBox().y - _Collider.GetBox().h + speed*2){
            move.y *= -1;
        }
        else if (_Collider.GetBox().y <= left.GetBox().y+ left.GetBox().h && _Collider.GetBox().y >= left.GetBox().y+ left.GetBox().h - speed*2){
            move.y *= -1;
        }
        if (_Collider.GetBox().x <= left.GetBox().x+ left.GetBox().w && _Collider.GetBox().x >= left.GetBox().x+ left.GetBox().w - speed*2){
            move.x *= -1;
        }
    }
    else if (CollisionHandler::GetInstance()->CheckCollision(_Collider, right)){
        if (_Collider.GetBox().y >= right.GetBox().y - _Collider.GetBox().h && _Collider.GetBox().y <= right.GetBox().y - _Collider.GetBox().h + speed*2){
            move.y *= -1;
        }
        else if (_Collider.GetBox().y <= right.GetBox().y + right.GetBox().h && _Collider.GetBox().y >= right.GetBox().y + right.GetBox().h - speed*2){
            move.y *= -1;
        }
        if (_Collider.GetBox().x + _Collider.GetBox().w >= right.GetBox().x && _Collider.GetBox().x + _Collider.GetBox().w <= right.GetBox().x + speed*2){
            move.x *= -1;
        }
    }
    else if (CollisionHandler::GetInstance()->CheckCollision(_Collider, hover_plat)){
        
        if (_Collider.GetBox().y + _Collider.GetBox().h <= hover_plat.GetBox().y + 5){
            move.y *= -1;
            _Transform->y = hover_plat.GetBox().y - _Collider.GetBox().h - 2;
        }
        else if (_Collider.GetBox().y >= hover_plat.GetBox().y + hover_plat.GetBox().h - 5){
            move.y *= -1;
            _Transform->y = hover_plat.GetBox().y + hover_plat.GetBox().h + 2;
        }
        if (_Collider.GetBox().x + _Collider.GetBox().w <= hover_plat.GetBox().x + 5){
            move.x *= -1;
            _Transform->x = hover_plat.GetBox().x - _Collider.GetBox().w - 2;
        }
        else if (_Collider.GetBox().x >= hover_plat.GetBox().x + hover_plat.GetBox().w - 5){
            move.x *= -1;
            _Transform->x = hover_plat.GetBox().x + hover_plat.GetBox().w + 2;
        }
    }
    _Transform->translateVector(move);
    UpdateCollider();
    _Animation->Update(dt);
}

void Planet::Render(){
    _Animation->Render(_Transform->x, _Transform->y, w, h, scale);
    _Collider.Render();
}

void Planet::Clean(){
    delete _Transform;
    delete _Animation;
}