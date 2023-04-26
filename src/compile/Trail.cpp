#include "Trail.hpp"

Trail::Trail(const char* path, int _frame, int _row, int _x, int _y, int _w, int _h, FACE _face) : x(_x), y(_y), frame(_frame), row(_row), face(_face){
    w = _w;
    h = _h;
    GameObjectHandler::GetInstance()->addObject(PLAYSCENE, this);
    layer = 1;
    ID = "trail";
    flip = (face == FACE::RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    /*
    switch (dir)
    {
    case 0:
        texture = IMG_LoadTexture(Engine::GetInstance()->GetRenderer(), "res/Assests/rainbow_dash_face_left.png");
        break;
    case 1:
        texture = IMG_LoadTexture(Engine::GetInstance()->GetRenderer(), "res/Assests/rainbow_dash_face_right.png");
        break;
    case 2:
        texture = IMG_LoadTexture(Engine::GetInstance()->GetRenderer(), "res/Assests/rainbow_dash_inAir.png");
        break;
    }*/
    const char* file = ("res/Assests/"+(std::string)path + ".png").c_str();
    texture = IMG_LoadTexture(Engine::GetInstance()->GetRenderer(), file);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}
Trail::~Trail(){}

void Trail::Update(float& dt){
    alpha -= 10;
    if (alpha <= 0) GameObjectHandler::GetInstance()->AddToTrash(this);
}

void Trail::Render(){
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_Rect src = {frame*32, row*32, 32, 32};
    SDL_Rect dst = {x, y, 64, 64};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), texture, &src, &dst, 0, nullptr, flip);
}

void Trail::Clean(){
    SDL_DestroyTexture(texture);
}