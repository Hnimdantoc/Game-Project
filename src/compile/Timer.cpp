#include "Timer.hpp"

Timer* Timer::static_Instance = nullptr;

Timer::Timer(){}

Timer::~Timer(){
    SDL_Log("Timer destroyed");
}