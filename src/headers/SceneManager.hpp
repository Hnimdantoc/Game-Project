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
    
    void ChangeScene(int ID);
    inline int GetCurrentSceneID(){return currentScene;}
    inline void addScene(int ID, Scene* _scene){SceneMap[ID] = _scene;}

    void Update(float& dt);
    void Render();
    void Clean();

    void CleanAllScene();
private:
    SceneManager();
};