#include "Hover_platform.hpp"
#include "GameObjectHandler.hpp"

Hover_platform::Hover_platform(){}

Hover_platform::Hover_platform(Properties* prop){
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
    _Collider = Collider({_Rect.x, _Rect.y, 150, 20});
}

Hover_platform::~Hover_platform(){}

void Hover_platform::Update(float& dt){
    if (_Transform->y >= 600) GO = -1;
    else if (_Transform->y <= 125) GO = 1;
    _Transform->translateY(1.0f * GO);
    UpdateCollider();
}

void Hover_platform::Render(){
    TextureManager::GetInstance()->Render(ID, _Transform->x, _Transform->y, w, h, 1.0f);
    _Collider.Render();
}

void Hover_platform::Clean(){
    delete _Transform;
}