#pragma once

#include <iostream>
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL.h"
#include <map>
#include <fstream>


#define MUSIC 0
#define SFX 1


class Mixer 
{
private:
    static Mixer* static_instance;
    int volume;
    std::map<std::string, Mix_Music*> musicMap;
    std::map<std::string, Mix_Chunk*> sfxMap;
public:
    static Mixer* GetInstance(){return static_instance = (static_instance != nullptr) ? static_instance : new Mixer();}
    ~Mixer();

    void Init();
    void Load(const char* filePathMusic, const char* filePathSFX);
    void Play(const char* sound, int music_or_sfx, int loops = 1, bool FadeIn = false, int ms = 0);
    void Toggle();
    inline void SetVolume(int _volume){volume = (MIX_MAX_VOLUME * _volume) / 100;}
private:
    Mixer();
};