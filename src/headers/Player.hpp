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
    Player();
    Player(Properties* prop);
    ~Player();

    static Player* GetInstance(){return Static_Instance;}
    
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

    /* Override if needed
    inline Transform* getTransform(){return _Transform;}
    inline SDL_Texture* getTexture(){return texture;}
    inline SDL_Rect* getRect(){return &_Rect;}
    inline RigidBody2D* GetRigidBody(){return _RigidBody;}
    inline Transform* SetTransform(){return _Transform;}
    */

    void Render();
    void Update(float& dt);
    void Clean();
private:
    std::string _id; 
    static Player* Static_Instance;
    Animation JumpDust;
    int frameCount;
    int jumps;
    float dashTime, dashLength;
    bool inAir, dashing, canDash;
    bool allowInput;
    bool enableSmoothMovement, _NeedChangeState;
    STATE playerState, prevState;
    Uint32 lastDash;
};