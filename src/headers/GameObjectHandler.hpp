#pragma once

#include <iostream>
#include <map>
#include <set>
#include "GameObject.hpp"

struct custom_set
{
    bool operator()(GameObject* a, GameObject* b) const {
        return (a->GetLayer() <= b->GetLayer());
    }
};

class GameObjectHandler
{
public:
    static GameObjectHandler* GetInstance(){return Static_Instance = (Static_Instance != nullptr) ? Static_Instance : new GameObjectHandler();}
    ~GameObjectHandler();
    
    inline std::map<int, std::set<GameObject*, custom_set>>* GetGameObjectMap(){return &GameObjectMap;}
    inline void addObject(int scene, GameObject* _obj){GameObjectMap[scene].insert(_obj);}
    int* ptr_current_scene;
    inline GameObject* GetGameObject(int _scene, const char* ID){
        for (GameObject* i : GameObjectMap[_scene]) if (strcmp(i->GetID(), ID) == 0) return i;
        return nullptr;
    }

    void Update(float& dt);
    void Render();
    void Clean();

    void CleanAllGameObjects();
private:
    GameObjectHandler();
    static GameObjectHandler* Static_Instance;
    
    std::map<int, std::set<GameObject*, custom_set>> GameObjectMap;
};