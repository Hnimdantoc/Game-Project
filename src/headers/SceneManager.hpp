#pragma once

#include <map>
#include "Scene.hpp"
#include "GameObjectHandler.hpp"

class SceneManager
{
private:
    static SceneManager* static_instance;
    int currentScene;
    std::map<int, Scene*> SceneMap;
public:
    static SceneManager* GetInstance(){return static_instance = (static_instance != nullptr) ? static_instance : new SceneManager();}
    ~SceneManager();
    
    void ChangeScene(int ID, bool Create = true , bool Transition = true, bool Clean = true);
    inline int GetCurrentSceneID(){return currentScene;}
    inline void addScene(int ID, Scene* _scene){SceneMap[ID] = _scene;}

    void KeyDown(SDL_Scancode scancode);
    void KeyUp(SDL_Scancode scancode);

    void Update(float& dt);
    void Render();
    void Clean(int ID = *GameObjectHandler::GetInstance()->ptr_current_scene);

    void CleanAllScene();
private:
    SceneManager();
};