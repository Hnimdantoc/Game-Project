#pragma once

#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "input.hpp"
#include <utility>
#include "Player.hpp"

#define PLAYER1_GO_LEFT_SCANCODE SDL_SCANCODE_A
#define PLAYER1_GO_RIGHT_SCANCODE SDL_SCANCODE_D
#define PLAYER1_JUMP_SCANCODE SDL_SCANCODE_W
#define PLAYER1_DASH_SCANCODE SDL_SCANCODE_J

class Player1 : public GameObject
{
public:
    int j1_x, j1_y, j2_x, j2_y;
    Uint32 lastJump;
    Animation JumpDust1, JumpDust2;
private:
    static Player1* Static_Instance;
    int frameCount, jumps;
    float dashTime, dashLength;
    bool inAir, dashing, canDash;
    bool enableSmoothMovement, _NeedChangeState, allowInput;
    std::string _id;
    Uint32 lastDash;
    std::pair <STATE, FACE> player1Action, prevAction;
public:
    static Player1* GetInstance(){return Static_Instance;}

    Player1();
    Player1(Properties* prop);
    ~Player1();

    
    inline std::pair <STATE, FACE>& GetState(){return player1Action;}
    inline std::pair <STATE, FACE>& GetPrevState(){return prevAction;}
    inline void SetState(STATE state, FACE face){player1Action.first = state;
                                                 player1Action.second = face;}
    inline void SetPrevState(){prevAction = player1Action;}
    inline bool& NeedChangeState(){return _NeedChangeState;};
    inline bool& GetInAir(){return inAir;}
    inline bool& SetInAir(){return inAir;}
    inline bool GetAllowInput(){return allowInput;}
    inline bool& SetAllowInput(){
        //std::cout << "SET HERE " << _RigidBody->getVelocity().y << std::endl;
        return allowInput;}
    inline bool& GetSmoothMovement(){return enableSmoothMovement;}
    inline bool& SetSmoothMovement(){return enableSmoothMovement;}
    inline void UpdateCollider(){
        _Collider.GetBox().x = _Transform->x + OFFSET;
        _Collider.GetBox().y = _Transform->y;
    }
    inline int GetRemainJumps(){return jumps;}
    inline void ReduceJumps(){jumps--;}
    inline void ResetJumps(){jumps = 2;}
    inline bool& CanDash(){return canDash;}
    inline bool& Dashing(){return dashing;}
    inline float& DashTime(){return dashTime;}
    inline float& DashLength(){return dashLength;}
    inline Uint32& GetLastDash(){return lastDash;}

    void Render();
    void Update(float& dt);
    void Clean();
};