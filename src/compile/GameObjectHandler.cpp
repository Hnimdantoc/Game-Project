#include "GameObjectHandler.hpp"
GameObjectHandler* GameObjectHandler::Static_Instance = nullptr;

GameObjectHandler::GameObjectHandler(){}

GameObjectHandler::~GameObjectHandler(){
    SDL_Log("GameObject Handler destroyed");
    CleanAllGameObjects();
}

void GameObjectHandler::Terminate(){
    if ((int)trash.size() > 0) {
        for (std::set<GameObject*>::iterator a = trash.begin(); a != trash.end(); a++){
            for (std::set<GameObject*, custom_set>::iterator i = GameObjectMap[PLAYSCENE].begin(); i != GameObjectMap[PLAYSCENE].end(); i++) {
                if (*i != *a) continue;
                (*i)->Clean();
                trash.erase(a);
                delete *i;
                GameObjectMap[PLAYSCENE].erase(i);
            }
        }
        trash.clear();
    }
}

void GameObjectHandler::Update(float& dt){
    for (GameObject* i : GameObjectMap[*ptr_current_scene]) {
        int prevScene = *ptr_current_scene;
        i->Update(dt);
        if (prevScene != *ptr_current_scene) break;
    }
    if (*ptr_current_scene == PLAYSCENE) Terminate();
}

void GameObjectHandler::Render(){
    for (GameObject* i : GameObjectMap[*ptr_current_scene]) i->Render();
}

void GameObjectHandler::Clean(int ID){
    for (std::set<GameObject*, custom_set>::iterator i = GameObjectMap[ID].begin(); i != GameObjectMap[ID].end(); i++) {
        (*i)->Clean();
        delete *i;
        GameObjectMap[ID].erase(i);
    }
    GameObjectMap[ID].clear();
}

void GameObjectHandler::CleanAllGameObjects(){
    for (std::map<int, std::set<GameObject*, custom_set>>::iterator i = GameObjectMap.begin(); i != GameObjectMap.end(); i++){
        for (GameObject* j : i->second) delete j;
        i->second.clear();
    }
    GameObjectMap.clear();
}