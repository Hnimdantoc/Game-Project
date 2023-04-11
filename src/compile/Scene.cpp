#include "Scene.hpp"
#include "SceneManager.hpp"

Scene::Scene(){}

Scene::~Scene(){}

void Scene::MakeRectFromTexture(SDL_Texture** texture, SDL_Rect* rect, int x, int y){
    rect->x = x;
    rect->y = y;
    SDL_QueryTexture(*texture, nullptr, nullptr, &rect->w, &rect->h);
}

void Scene::Update(float& dt){
    GameObjectHandler::GetInstance()->Update(dt);
}
void Scene::Render(){
    GameObjectHandler::GetInstance()->Render();
}
void Scene::Clean(int ID){
    GameObjectHandler::GetInstance()->Clean(ID);
}
