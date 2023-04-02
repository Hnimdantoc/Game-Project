#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "TextureManager.hpp"

class Animation
{
private:
    const char* ID;
    bool changeAnimation;
    int frameTime, prevFrame;
    int spriteRow, frameCount, animateSpeed, frame;
    SDL_RendererFlip flip;
public:
    Animation();
    ~Animation();
    
    void Update(float& dt);
    void Render(float x, float y, int w, int h, float SCALE = 1.0f);
    void SetProp(const char* _ID, int _spriteRow, int _frameCount, int _animateSpeed, SDL_RendererFlip _flip = SDL_FLIP_NONE);

    inline void ChangeAnimationState(bool _state){changeAnimation = _state;}
    inline bool GetAnimationChangeState(){return changeAnimation;}
    inline int GetPrevFrame(){return prevFrame;}
    inline int GetFrame(){return frame;}
};