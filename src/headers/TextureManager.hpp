#pragma once

#include <map>
#include <string>
#include <vector>
#include "Engine.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class TextureManager
{
private:
    static TextureManager* static_Instance;
    std::vector<std::string> v_id, v_path;
    std::map <std::string, SDL_Texture*> TextureMap; 
public:
    static TextureManager* GetInstance(){return static_Instance = (static_Instance != nullptr) ? static_Instance : new TextureManager();}

    void Load(std::string ID, const char* filePath);
    void LoadFromFile(const char* filePath);
    void Render(const char* ID, int x, int y, int w, int h, float SCALE = 1.0f);
    void Transition(bool intro = false);
    void AnimationRender(const char* ID, int x, int y, int w, int h, int row, int frame, float SCALE = 1.0f, SDL_RendererFlip _flip = SDL_FLIP_NONE);

    TTF_Font* LoadFont(const char* fontPath, int fontSize);
    inline SDL_Texture* GetTextureFromMap(const char* ID){return TextureMap[ID];} 
    inline std::map<std::string, SDL_Texture*> GetTextureMap(){return TextureMap;} 
    SDL_Texture* CreateTextureFromText(TTF_Font* font, const char* text, const SDL_Color& color);

    ~TextureManager();
    void Remove(const char* ID);
    void Clean();
private:
    TextureManager();
};