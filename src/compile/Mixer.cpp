#include "Mixer.hpp"

Mixer* Mixer::static_instance = nullptr;

Mixer::Mixer(){}

Mixer::~Mixer(){
    for (auto i : musicMap) Mix_FreeMusic(i.second);
    for (auto i : sfxMap) Mix_FreeChunk(i.second);
    SDL_Log("Mixer destroyed");
}


void Mixer::Init(){
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) std::cout << "SDL_mixer cannot initialize. " << Mix_GetError() << std::endl;
    SetVolume(100);
}

void Mixer::Play(const char* sound, int music_or_sfx, int loops, bool FadeIn, int ms){
    if (music_or_sfx == MUSIC) {
        Mix_VolumeMusic(volume);
        if (FadeIn) Mix_FadeInMusic(musicMap[sound], loops, ms) == -1;
        else Mix_PlayMusic(musicMap[sound], loops);
    }
    else if (music_or_sfx == SFX) {
        Mix_Volume(-1, volume);
        Mix_PlayChannel(-1, sfxMap[sound], loops);
    }
}

void Mixer::Toggle(){
    Mix_VolumeMusic(volume);
    if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
    else Mix_PauseMusic();
}

void Mixer::Load(const char* filePathMusic, const char* filePathSFX){
    std::ifstream file;
    file.open(filePathMusic);
    if (file){
        while(!file.eof()){
            std::string name;
            file >> name;
            if (file){
                musicMap[name] = Mix_LoadMUS(name.c_str());
            }
            else break;
        }
    }
    else std::cout << "Cannot load file. Path: " << filePathMusic << std::endl;
    file.close();

    file.open(filePathSFX);
    if (file){
        while(!file.eof()){
            std::string name;
            file >> name;
            if (file){
                sfxMap[name] = Mix_LoadWAV(name.c_str());
            }
            else break;
        }
    }
    else std::cout << "Cannot load file. Path: " << filePathSFX << std::endl;
    file.close();
}