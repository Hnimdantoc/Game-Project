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

void SceneManager::KeyDown(SDL_Scancode scancode){
    SceneMap[currentScene]->KeyDown(scancode);
}

void SceneManager::KeyUp(SDL_Scancode scancode){
    SceneMap[currentScene]->KeyUp(scancode);
}

void SceneManager::Update(float& dt){
    SceneMap[currentScene]->Update(dt);
}
void SceneManager::Render(){
    SceneMap[currentScene]->Render();
}

void SceneManager::ChangeScene(int ID, bool Create, bool transition, bool clean){
    if (Create){
        if (ID == MENU_SCENE) Menu* menu = new Menu();
        else if (ID == SELECT_SCENE) Select* selec_scene = new Select();
        else if (ID == PLAYSCENE) Scene_0* play_scene = new Scene_0();
        else if (ID == PAUSE_SCENE) Pause* pause_scene = new Pause();
    }
    if (transition) TextureManager::GetInstance()->Transition();
    if (clean) Clean();
    currentScene = ID;
    if (transition) TextureManager::GetInstance()->Transition(true);
}

void SceneManager::Clean(int ID){
    SceneMap[ID]->Clean(ID);
    delete SceneMap[ID];
    SceneMap.erase(ID);
}

void SceneManager::CleanAllScene(){
    GameObjectHandler::GetInstance()->~GameObjectHandler();
    for (std::map <int, Scene*>::iterator i = SceneMap.begin(); i != SceneMap.end(); i++){
        delete i->second;
    }
    SceneMap.clear();
}