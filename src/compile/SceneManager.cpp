#include "SceneManager.hpp"
#include "Scenes.hpp"

SceneManager* SceneManager::static_instance = nullptr;

SceneManager::SceneManager(){
    currentScene = 0;
    GameObjectHandler::GetInstance()->ptr_current_scene = &currentScene;
}

SceneManager::~SceneManager(){}

void SceneManager::Update(float& dt){
    std::cout << "Scene: " << 1 << "Objects: " << (*GameObjectHandler::GetInstance()->GetGameObjectMap())[1].size() << std::endl; 
    SceneMap[currentScene]->Update(dt);
}
void SceneManager::Render(){
    SceneMap[currentScene]->Render();
}

void SceneManager::ChangeScene(int ID){
    Clean();
    if (ID == MENU_SCENE) Menu* menu = new Menu();
    else if (ID == PLAYSCENE) Scene_0* play_scene = new Scene_0();
    currentScene = ID;
}

void SceneManager::Clean(){
    SceneMap[currentScene]->Clean();
    delete SceneMap[currentScene];
}

void SceneManager::CleanAllScene(){
    GameObjectHandler::GetInstance()->~GameObjectHandler();
    for (std::map <int, Scene*>::iterator i = SceneMap.begin(); i != SceneMap.end(); i++){
        delete i->second;
    }
    SceneMap.clear();
}