#include "TextureManager.hpp"
#include <fstream>

TextureManager::TextureManager(){}

TextureManager* TextureManager::static_Instance = nullptr;

void TextureManager::Load(std::string ID, const char* filePath){
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(Engine::GetInstance()->GetRenderer(), filePath);
    if (texture == NULL) std::cout << "Failed to create texture from surface. Error: " << SDL_GetError() << std::endl;
    TextureMap[ID] = texture;
}

void TextureManager::LoadFromFile(const char* filePath){
    // Open file and get data
    std::ifstream file;
    file.open(filePath);
    if (file){
        while(!file.eof()){
            std::string id, path;
            file >> id >> path;
            if (file){
                const char* FILE_PATH = path.c_str();
                Load(id, FILE_PATH);
            }
            else break;
        }
    }
    else std::cout << "Cannot load file. Path: " << filePath << std::endl;
    file.close();
}

void TextureManager::Render(const char* ID, int x, int y, int w, int h, float SCALE){
    SDL_Rect src = {0, 0, w, h};
    SDL_Rect dst = {x, y, (int)(w * SCALE), (int)(h * SCALE)};
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), TextureMap[ID], &src, &dst);
}

void TextureManager::AnimationRender(const char* ID, int x, int y, int w, int h, int row, int frame, float SCALE, SDL_RendererFlip flip){
    SDL_Rect src = {frame * w, row * h, w, h};
    SDL_Rect dst = {x, y, (int)(w * SCALE), (int)(h * SCALE)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), TextureMap[ID], &src, &dst, 0, nullptr, flip);
}

TTF_Font* TextureManager::LoadFont(const char* fontPath, int fontSize){
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (font == nullptr) std::cout << "Cannot load font. Path: " << fontPath << ". Error: " << TTF_GetError() << std::endl;
    return font;
}

SDL_Texture* TextureManager::CreateTextureFromText(TTF_Font* font, const char* text, const SDL_Color& color){
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, color);
    if (text_surface == nullptr) std::cout << "Failed to create surface from font." << SDL_GetError() << std::endl;
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), text_surface);
    if (text_texture == NULL) std::cout << "Failed to create texture from surface. " << SDL_GetError() << std::endl;
    SDL_FreeSurface(text_surface);
    return text_texture;
}

void TextureManager::Remove(const char* ID){
    SDL_DestroyTexture(TextureMap[ID]);
    TextureMap.erase(ID);
}

void TextureManager::Clean(){
    SDL_Log("Texture cleaned");
    std::map <std::string, SDL_Texture*>::iterator i;
    for (i = TextureMap.begin(); i != TextureMap.end(); i++){
        SDL_DestroyTexture(i->second);
    }
    TextureMap.clear();
}

