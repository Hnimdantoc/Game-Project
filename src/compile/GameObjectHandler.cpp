#include "GameObjectHandler.hpp"

GameObjectHandler* GameObjectHandler::Static_Instance = nullptr;

GameObjectHandler::GameObjectHandler(){}

GameObjectHandler::~GameObjectHandler(){
    SDL_Log("GameObject Handler destroyed");
    CleanAllGameObjects();
}

void GameObjectHandler::Update(float& dt){
    for (GameObject* i : GameObjectMap[*ptr_current_scene]) i->Update(dt);
}

void GameObjectHandler::Render(){
    for (GameObject* i : GameObjectMap[*ptr_current_scene]) i->Render();
}

void GameObjectHandler::Clean(){
    for (std::set<GameObject*, custom_set>::iterator i = GameObjectMap[*ptr_current_scene].begin(); i != GameObjectMap[*ptr_current_scene].end(); i++) {
        (*i)->Clean();
        GameObjectMap[*ptr_current_scene].erase(i);
        delete *i;
    }
    GameObjectMap[*ptr_current_scene].clear();
}

void GameObjectHandler::CleanAllGameObjects(){
    for (std::map<int, std::set<GameObject*, custom_set>>::iterator i = GameObjectMap.begin(); i != GameObjectMap.end(); i++){
        for (GameObject* j : i->second) delete j;
        i->second.clear();
    }
    GameObjectMap.clear();
}