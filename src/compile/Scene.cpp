#include "Scene.hpp"
#include "SceneManager.hpp"

Scene::Scene(){}

Scene::~Scene(){}

void Scene::Update(float& dt){
    GameObjectHandler::GetInstance()->Update(dt);
}
void Scene::Render(){
    GameObjectHandler::GetInstance()->Render();
}
void Scene::Clean(){
    GameObjectHandler::GetInstance()->Clean();
}

