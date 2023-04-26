#include "SceneManager.hpp"
#include "Scenes.hpp"
#include "Mixer.hpp"

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

void SceneManager::MouseMotion(){
    SceneMap[currentScene]->MouseMotion();
}

void SceneManager::Update(float& dt){
    SceneMap[currentScene]->Update(dt);
}
void SceneManager::Render(){
    SceneMap[currentScene]->Render();
}

void SceneManager::ChangeScene(int ID, bool Create, bool transition, bool clean){
    prevScene = currentScene;
    if (Create){
        if (ID == MENU_SCENE) {
            if ((prevScene == PLAYSCENE || prevScene == SCORE_SCENE) && ID == MENU_SCENE){
                Mix_FadeOutMusic(500);
                Mixer::GetInstance()->Play(MENU_THEME, MUSIC, -1, true, 250);
            }
            Menu* menu = new Menu();
        }
        else if (ID == SELECT_SCENE) Select* select_scene = new Select();
        else if (ID == OPTION_SCENE) Option* Option_scene = new Option();
        else if (ID == PLAYSCENE) {
            Mix_FadeOutMusic(500);
            Mixer::GetInstance()->Play(PLAY_THEME, MUSIC, 0, true, 5000);
            Scene_0* play_scene = new Scene_0();
        }
        else if (ID == PAUSE_SCENE) Pause* pause_scene = new Pause();
        else if (ID == SCORE_SCENE) Score* score_scene = new Score();
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
    for (std::map <int, Scene*>::iterator i = SceneMap.begin(); i != SceneMap.end(); i++){
        delete i->second;
    }
    SceneMap.clear();
}