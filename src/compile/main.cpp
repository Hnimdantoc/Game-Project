#include "Engine.hpp"
#include "Timer.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    Engine::GetInstance()->init(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    while(Engine::GetInstance()->getGameState() == GAME_STATE::PLAYING){
        Timer::getIntance()->Ticks();
    
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update(Timer::getIntance()->getDeltaTime());
        Engine::GetInstance()->Render();
        
        Timer::getIntance()->Tocks();
        
        if (Timer::getIntance()->NeedDelay()) SDL_Delay(Timer::getIntance()->GetDelay());
    }
    
    Engine::GetInstance()->Quit();
    delete Engine::GetInstance();

    return 0;
}