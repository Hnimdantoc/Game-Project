#pragma once

#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "input.hpp"

#define DASH_VELLOCITY 2000
#define DASH_COOL_DOWN 4000
#define PLAYER_GO_LEFT_SCANCODE SDL_SCANCODE_LEFT
#define PLAYER_GO_RIGHT_SCANCODE SDL_SCANCODE_RIGHT
#define PLAYER_JUMP_SCANCODE SDL_SCANCODE_UP
#define PLAYER_DASH_SCANCODE SDL_SCANCODE_SPACE

enum STATE {STANDING_RIGHT, STANDING_LEFT, RUNNING_LEFT, RUNNING_RIGHT, JUMPING};

class Player : public GameObject
{
public:
    int j1_x, j1_y, j2_x, j2_y;
private:
    static Player* Static_Instance;
    int frameCount, jumps;
    float dashTime, dashLength;
    bool inAir, dashing, canDash;
    bool enableSmoothMovement, _NeedChangeState, allowInput;
    std::string _id;
    Uint32 lastDash;
    Animation JumpDust1, JumpDust2;
    STATE playerState, prevState;
public:
    static Player* GetInstance(){return Static_Instance;}

    Player();
    Player(Properties* prop);
    ~Player();

    
    inline STATE& GetState(){return playerState;}
    inline STATE& GetPrevState(){return prevState;}
    inline void SetState(STATE _state){playerState = _state;}
    inline void SetPrevState(){prevState = playerState;}
    inline bool& NeedChangeState(){return _NeedChangeState;};
    inline bool& GetInAir(){return inAir;}
    inline bool& SetInAir(){return inAir;}
    inline bool& GetAllowInput(){return allowInput;}
    inline bool& SetAllowInput(){return allowInput;}
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