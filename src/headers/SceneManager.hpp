#pragma once

#include <map>
#include "Scene.hpp"
#include "GameObjectHandler.hpp"

class SceneManager
{
public:
    ~SceneManager();

    static SceneManager* GetInstance(){return static_instance = (static_instance != nullptr) ? static_instance : new SceneManager();}
    
    inline int GetCurrentSceneID(){return currentScene;}
    void ChangeScene(int ID);
    inline void addScene(int ID, Scene* _scene){SceneMap[ID] = _scene;}

    void Update(float& dt);
    void Render();
    void Clean();

    void CleanAllScene();
private:
    SceneManager();

    static SceneManager* static_instance;
    std::map<int, Scene*> SceneMap;
    int currentScene;
};