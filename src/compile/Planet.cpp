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
    _RigidBody = new RigidBody2D();
    _Animation = new Animation();
    _Animation->SetProp(ID, prop->spriteRow, prop->frameCount, 100);
    _RigidBody->setGravity(0.0f);
    srand(time(NULL));
    move = dir[rand() % dir.size()];
    if (strcmp(ID, "moon") == 0) {
        _RigidBody->setMass(2.0f);
        move = {move.x * 0.75f, move.y * 0.75f};
    }
    _Rect.x = _Transform->x;
    _Rect.y = _Transform->y;
    _Rect.w = w * prop->scale;
    _Rect.h = h * prop->scale;
    _Collider = Collider(_Rect);
    delete prop;
}

Planet::~Planet(){}

void Planet::Update(float& dt){
    _Transform->translateVector(move);
    if (strcmp(ID, "sun") == 0) {
        _RigidBody->setMass(1.0f);
        SunCollision();
    }
    else if (strcmp(ID, "moon") == 0) MoonCollision();
    
    _RigidBody->Update(dt);
    UpdateCollider();
    _Animation->Update(dt);
}

void Planet::SunCollision(){
    if (_Collider.GetBox().x <= 0 || _Collider.GetBox().x >= WIDTH - _Collider.GetBox().w) {
        move.x *= -1;
        _RigidBody->setMass(3);
        if (_Collider.GetBox().x <= 0) _Transform->x = 1;
        else _Transform->x = WIDTH - _Collider.GetBox().w - 1;
    }
    if (_Collider.GetBox().y <= 0 || _Collider.GetBox().y >= HEIGHT - _Collider.GetBox().h) {
        move.y *= -1;
        _RigidBody->setMass(3);
        if (_Collider.GetBox().y <= 0) _Transform->y = 1;
        else _Transform->y = HEIGHT - _Collider.GetBox().h - 1;
    }
    UpdateCollider();
    for (std::set<GameObject*, custom_set>::iterator i = ((*GameObjectHandler::GetInstance()->GetGameObjectMap())[*GameObjectHandler::GetInstance()->ptr_current_scene]).begin(); i != ((*GameObjectHandler::GetInstance()->GetGameObjectMap())[*GameObjectHandler::GetInstance()->ptr_current_scene]).end(); i++){
        if (strcmp((*i)->GetID(), "sun") == 0) continue;
        if (CollisionHandler::GetInstance()->CheckCollision(_Collider, (*i)->getCollider())){
            if (strcmp((*i)->GetID(), "Left_platform") == 0){
                if (_Collider.GetBox().y <= (*i)->getCollider().GetBox().y - _Collider.GetBox().h + speed*2){
                    move.y *= -1;
                    _RigidBody->setMass(3);
                    _Transform->y = (*i)->getCollider().GetBox().y - _Collider.GetBox().h - 1;
                }
                else if (_Collider.GetBox().y >= (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h - speed*2){
                    move.y *= -1;
                    _RigidBody->setMass(3);
                    _Transform->y = (*i)->getCollider().GetBox().y+ (*i)->getCollider().GetBox().h + 1;
                }
                if (_Collider.GetBox().x >= (*i)->getCollider().GetBox().x+ (*i)->getCollider().GetBox().w - speed*2){
                    move.x *= -1;
                    _RigidBody->setMass(3);
                    _Transform->x = (*i)->getCollider().GetBox().x+ (*i)->getCollider().GetBox().w + 1;
                }
            }
            if (strcmp((*i)->GetID(), "Right_platform") == 0){
                if (_Collider.GetBox().y <= (*i)->getCollider().GetBox().y - _Collider.GetBox().h + speed*2){
                    move.y *= -1;
                    _RigidBody->setMass(3);
                    _Transform->y = (*i)->getCollider().GetBox().y - _Collider.GetBox().h - 1;
                }
                else if (_Collider.GetBox().y >= (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h - speed*2){
                    move.y *= -1;
                    _RigidBody->setMass(3);
                    _Transform->y = (*i)->getCollider().GetBox().y+ (*i)->getCollider().GetBox().h + 1;
                }
                if (_Collider.GetBox().x + _Collider.GetBox().w <= (*i)->getCollider().GetBox().x + speed*2){
                    move.x *= -1;
                    _RigidBody->setMass(3);
                    _Transform->x = (*i)->getCollider().GetBox().x - _Collider.GetBox().w - 1;
                }
            }
            else if (strcmp((*i)->GetID(), "Hover_platform") == 0){
                if (_Collider.GetBox().y + _Collider.GetBox().h <= (*i)->getCollider().GetBox().y + speed*2){
                    move.y *= -1;
                    _RigidBody->setMass(3);
                    _Transform->y = (*i)->getCollider().GetBox().y - _Collider.GetBox().h - 1;
                }
                else if (_Collider.GetBox().y >= (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h - speed*2){
                    move.y *= -1;
                    _RigidBody->setMass(3);
                    _Transform->y = (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h + 1;
                }
                if (_Collider.GetBox().x + _Collider.GetBox().w <= (*i)->getCollider().GetBox().x + speed*2){
                    move.x *= -1;
                    _RigidBody->setMass(3);
                    _Transform->x = (*i)->getCollider().GetBox().x - _Collider.GetBox().w - 1;
                }
                else if (_Collider.GetBox().x >= (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w - speed*2){
                    move.x *= -1;
                    _RigidBody->setMass(3);
                    _Transform->x = (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w + 1;
                }
            }
 
            else if (strcmp((*i)->GetID(), "moon") == 0 && _RigidBody->getMass() == 1.0f){
                if (_Collider.GetBox().y + _Collider.GetBox().h <= (*i)->getCollider().GetBox().y + speed*3){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y - _Collider.GetBox().h - 1;
                }
                else if (_Collider.GetBox().y >= (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h - speed*3){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h + 1;
                }
                if (_Collider.GetBox().x + _Collider.GetBox().w <= (*i)->getCollider().GetBox().x + speed*3){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x - _Collider.GetBox().w - 1;
                }
                else if (_Collider.GetBox().x >= (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w - speed*3){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w + 1;
                }
            }
        } 
    UpdateCollider();
    }
}

void Planet::MoonCollision(){
    if (_Collider.GetBox().x <= 0 || _Collider.GetBox().x >= WIDTH - _Collider.GetBox().w) {
        move.x *= -1;
        if (_Collider.GetBox().x <= 0) _Transform->x = 1;
        else _Transform->x = WIDTH - _Collider.GetBox().w - 1;
    }
    UpdateCollider();
    if (_Collider.GetBox().y <= 0 || _Collider.GetBox().y >= HEIGHT - _Collider.GetBox().h) {
        move.y *= -1;
        if (_Collider.GetBox().y <= 0) _Transform->y = 1;
        else _Transform->y = HEIGHT - _Collider.GetBox().h - 1;
    }
    for (std::set<GameObject*, custom_set>::iterator i = ((*GameObjectHandler::GetInstance()->GetGameObjectMap())[*GameObjectHandler::GetInstance()->ptr_current_scene]).begin(); i != ((*GameObjectHandler::GetInstance()->GetGameObjectMap())[*GameObjectHandler::GetInstance()->ptr_current_scene]).end(); i++){
        if (*i == this) continue;
        if (CollisionHandler::GetInstance()->CheckCollision(_Collider, (*i)->getCollider())){
            if (strcmp((*i)->GetID(), "Left_platform") == 0){
                if (_Collider.GetBox().y <= (*i)->getCollider().GetBox().y - _Collider.GetBox().h + speed*2){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y - _Collider.GetBox().h - 1;
                }
                else if (_Collider.GetBox().y >= (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h - speed*2){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y+ (*i)->getCollider().GetBox().h + 1;
                }
                if (_Collider.GetBox().x >= (*i)->getCollider().GetBox().x+ (*i)->getCollider().GetBox().w - speed*2){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x+ (*i)->getCollider().GetBox().w + 1;
                }
            }
            else if (strcmp((*i)->GetID(), "Right_platform") == 0){
                if (_Collider.GetBox().y <= (*i)->getCollider().GetBox().y - _Collider.GetBox().h + speed*2){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y - _Collider.GetBox().h - 1;
                }
                else if (_Collider.GetBox().y >= (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h - speed*2){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y+ (*i)->getCollider().GetBox().h + 1;
                }
                if (_Collider.GetBox().x + _Collider.GetBox().w <= (*i)->getCollider().GetBox().x + speed*2){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x - _Collider.GetBox().w - 1;
                }
            }
            else if (strcmp((*i)->GetID(), "Hover_platform") == 0){
                if (_Collider.GetBox().y + _Collider.GetBox().h <= (*i)->getCollider().GetBox().y + speed*2){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y - _Collider.GetBox().h - 1;
                }
                else if (_Collider.GetBox().y >= (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h - speed*2){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h + 1;
                }
                if (_Collider.GetBox().x + _Collider.GetBox().w <= (*i)->getCollider().GetBox().x + speed*2){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x - _Collider.GetBox().w - 1;
                }
                else if (_Collider.GetBox().x >= (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w - speed*2){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w + 1;
                }
            }
            else if (strcmp((*i)->GetID(), "sun") == 0 && (*i)->GetRigidBody()->getMass() == 3.0f){
                if (_Collider.GetBox().y + _Collider.GetBox().h <= (*i)->getCollider().GetBox().y + speed*3){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y - _Collider.GetBox().h - speed*2;
                }
                else if (_Collider.GetBox().y >= (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h - speed*3){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h + speed*2;
                }
                if (_Collider.GetBox().x + _Collider.GetBox().w <= (*i)->getCollider().GetBox().x + speed*3){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x - _Collider.GetBox().w - speed*2;
                }
                else if (_Collider.GetBox().x >= (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w - speed*3){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w + speed*2;
                }
            }
            else if (strcmp((*i)->GetID(), "moon") == 0) {
                if (_Collider.GetBox().y + _Collider.GetBox().h <= (*i)->getCollider().GetBox().y + speed*4){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y - _Collider.GetBox().h - 1;
                }
                else if (_Collider.GetBox().y >= (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h - speed*4){
                    move.y *= -1;
                    _Transform->y = (*i)->getCollider().GetBox().y + (*i)->getCollider().GetBox().h + 1;
                }
                if (_Collider.GetBox().x + _Collider.GetBox().w <= (*i)->getCollider().GetBox().x + speed*3){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x - _Collider.GetBox().w - 1;
                }
                else if (_Collider.GetBox().x >= (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w - speed*3){
                    move.x *= -1;
                    _Transform->x = (*i)->getCollider().GetBox().x + (*i)->getCollider().GetBox().w + 1;
                }
            }
        } 
        UpdateCollider();
    }
}

void Planet::Render(){
    _Animation->Render(_Transform->x, _Transform->y, w, h, scale);
    //_Collider.Render();
}

void Planet::Clean(){
    delete _Transform;
    delete _Animation;
    delete _RigidBody;
}