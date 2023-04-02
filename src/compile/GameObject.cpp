#include "GameObject.hpp"
#include "GameObjectHandler.hpp"

GameObject::GameObject(){}
GameObject::~GameObject(){}

GameObject::GameObject(Properties* prop){
    ID = prop->ID;
    w = prop->w;
    h = prop->h;
    layer = prop->layer;
    _scene = prop->scene;

    GameObjectHandler::GetInstance()->addObject(_scene, this);
    _Transform = new Transform(prop->x, prop->y);

    _Rect.x = _Transform->x;
    _Rect.y = _Transform->y;
    _Rect.w = w;
    _Rect.h = h;
    _Collider = Collider(_Rect);
    delete prop;
}

void GameObject::Update(float& dt){
    UpdateCollider();
}

void GameObject::Render(){
    TextureManager::GetInstance()->Render(ID, _Transform->x, _Transform->y, w, h);
    _Collider.Render();
}

void GameObject::Clean(){
    delete _Transform;
}



