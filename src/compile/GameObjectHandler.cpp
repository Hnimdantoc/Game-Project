#include "GameObjectHandler.hpp"

GameObjectHandler* GameObjectHandler::Static_Instance = nullptr;

GameObjectHandler::GameObjectHandler(){}

GameObjectHandler::~GameObjectHandler(){
    CleanAllGameObjects();
}

void GameObjectHandler::Update(float& dt){
    for (GameObject* i : GameObjectMap[*ptr_current_scene]) i->Update(dt);
}

void GameObjectHandler::Render(){
    for (GameObject* i : GameObjectMap[*ptr_current_scene]) i->Render();
}

void GameObjectHandler::Clean(){
    for (GameObject* i : GameObjectMap[*ptr_current_scene]) {
        i->Clean();
        delete i;
    }
}

void GameObjectHandler::CleanAllGameObjects(){
    for (std::map<int, std::set<GameObject*, custom_set>>::iterator i = GameObjectMap.begin(); i != GameObjectMap.end(); i++){
        for (GameObject* j : i->second) delete j;
        i->second.clear();
    }
    GameObjectMap.clear();
}