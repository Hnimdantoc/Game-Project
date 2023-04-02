#include "SceneManager.hpp"
#include "Scenes.hpp"

SceneManager* SceneManager::static_instance = nullptr;

SceneManager::SceneManager(){
    currentScene = 0;
    GameObjectHandler::GetInstance()->ptr_current_scene = &currentScene;
}

SceneManager::~SceneManager(){
    CleanAllScene();
    SDL_Log("Scene Manager destroyed");
}

void SceneManager::Update(float& dt){
    SceneMap[currentScene]->Update(dt);
}
void SceneManager::Render(){
    SceneMap[currentScene]->Render();
}

void SceneManager::ChangeScene(int ID){
    if (ID == MENU_SCENE) Menu* menu = new Menu();
    else if (ID == PLAYSCENE) Scene_0* play_scene = new Scene_0();
    else if (ID == SELECT_SCENE) Select* selec_scene = new Select();
    TextureManager::GetInstance()->Transition();
    Clean();
    currentScene = ID;
    TextureManager::GetInstance()->Transition(true);
}

void SceneManager::Clean(){
    SceneMap[currentScene]->Clean();
    delete SceneMap[currentScene];
    SceneMap.erase(currentScene);
}

void SceneManager::CleanAllScene(){
    GameObjectHandler::GetInstance()->~GameObjectHandler();
    for (std::map <int, Scene*>::iterator i = SceneMap.begin(); i != SceneMap.end(); i++){
        delete i->second;
    }
    SceneMap.clear();
}