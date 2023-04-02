#include "Animation.hpp"

Animation::Animation(){}
Animation::~Animation(){}

void Animation::Update(float& dt){
    // Math to find the frame to draw
    frame = ( frameTime / animateSpeed ) % frameCount;
    // Frame time
    frameTime += (int)(dt*1000);
    if (abs(frame - prevFrame) >= 2 && (frame - 1 >= 0)) prevFrame = frame-1;
    else if (abs(frame - prevFrame) >= 2 && (frame - 1 < 0)) prevFrame = frameCount-1;
}

void Animation::Render(float x, float y, int w, int h, float SCALE){
    TextureManager::GetInstance()->AnimationRender(ID, x, y, w, h, spriteRow, frame, SCALE, flip);
}

void Animation::SetProp(const char* _ID, int _spriteRow, int _frameCount, int _animateSpeed, SDL_RendererFlip _flip){
    ID = _ID;
    spriteRow = _spriteRow;
    frameCount = _frameCount;
    animateSpeed = _animateSpeed;
    flip = _flip;
    frameTime = 0;
    prevFrame = 0;
}