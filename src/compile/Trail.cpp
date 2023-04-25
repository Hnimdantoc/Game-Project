#include "Trail.hpp"

Trail::Trail(int _x, int _y, int _w, int _h) : x(_x), y(_y){
    w = _w;
    h = _h;
    GameObjectHandler::GetInstance()->addObject(PLAYSCENE, this);
    layer = 1;
    ID = "trail";
    texture = IMG_LoadTexture(Engine::GetInstance()->GetRenderer(), "res/Assests/rainbow_dash.png");
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

Trail::~Trail(){}

void Trail::Update(float& dt){
    alpha -= 10;
    if (alpha <= 0) GameObjectHandler::GetInstance()->AddToTrash(this);
}

void Trail::Render(){
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_Rect src = {0, 0, w, h};
    SDL_Rect dst = {x, y, w, h};
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), texture, &src, &dst);
}

void Trail::Clean(){
    SDL_DestroyTexture(texture);
}