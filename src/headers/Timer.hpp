#pragma once

#include "SDL2/SDL.h"

#define FPS 100.0f
#define MILLISECONDS_PER_FRAME 1000.0f / FPS
#define SECONDS_PER_FRAME 1.0f / FPS

class Timer
{
public:
    static Timer* getIntance(){return static_Instance = (static_Instance != nullptr ? static_Instance : new Timer());}
    inline float getDeltaTime(){return SECONDS_PER_FRAME;}
    inline void Ticks(){frameStart = SDL_GetTicks();}
    inline void Tocks(){frameTime = SDL_GetTicks() - frameStart;}
    inline bool NeedDelay(){return frameTime < MILLISECONDS_PER_FRAME ? true:false;};
    inline int GetDelay(){return (int)MILLISECONDS_PER_FRAME - frameTime;}
    inline int getFrameTime(){return frameTime;}

    ~Timer(){}
private:
    Timer();
    static Timer* static_Instance;
    Uint32 frameStart;
    int frameTime;
};