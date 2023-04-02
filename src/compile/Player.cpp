#include "Player.hpp"
#include "CollisionHandler.hpp"
#include "GameObjectHandler.hpp"
#include "Planet.hpp"
#include "Scenes.hpp"

Player* Player::Static_Instance = nullptr;

Player::Player(){
    Static_Instance = this;
}
Player::~Player(){std::cout << "Player deleted" << std::endl;}

Player::Player(Properties* prop){
    // Self reference
    Static_Instance = this;
    /*------------------------------------------------Initiate variables------------------------------------------------*/
    _id = std::string(prop->ID);
    ID = _id.c_str();
    w = prop->w;
    h = prop->h;
    layer = prop->layer;
    _scene = prop->scene;

    // This line must be after scene init
    GameObjectHandler::GetInstance()->addObject(_scene, this);
    
    _RigidBody = new RigidBody2D();
    _Transform = new Transform(prop->x, prop->y);
    _Animation = new Animation();
    
    /*animateSpeed: Time per animation frame. The lower the speed the faster the animation
    --------------change this-----\/---------------------------------------------------*/
    frameCount = prop->frameCount;
    _Animation->SetProp(ID, 0, frameCount, 150);
    playerState = STATE::STANDING_RIGHT;
    prevState = playerState;
    inAir = true;
    allowInput = true;
    _NeedChangeState = false;
    jumps = 2;
    dashing = false;
    canDash = true;
    lastDash = -DASH_COOL_DOWN;
    // Set collider
    _Rect.x = _Transform->x;
    _Rect.y = _Transform->y;
    _Rect.w = w * PLAYER_SCALE;
    _Rect.h = h * PLAYER_SCALE;
    _Collider = Collider({_Rect.x + OFFSET, _Rect.y, _Rect.w - 2*OFFSET, _Rect.h});
    JumpDust.SetProp("Jump_Dust", 0, 5, 80);
}

void Player::Render(){
    // Draw player
    _Animation->Render(_Transform->x, _Transform->y, w, h, PLAYER_SCALE);
    // Visualize collision box
    _Collider.Render();
    if (!(JumpDust.GetPrevFrame() == 5 && JumpDust.GetFrame() == 0)) JumpDust.Render(_Collider.GetBox().x, _Collider.GetBox().y + _Collider.GetBox().h, 23, 5, 2);
}

void Player::Update(float& dt){
    if (prevState != playerState) _NeedChangeState = true;
    if (_NeedChangeState){
        _NeedChangeState = false;
        if (playerState == STATE::STANDING_RIGHT){
            _Animation->SetProp(ID, 0, frameCount, 150);
            SetPrevState();
        }
        else if (playerState == STATE::STANDING_LEFT){
            _Animation->SetProp(ID, 0, frameCount, 150, SDL_FLIP_HORIZONTAL);
            SetPrevState();
        }
        else if (playerState == STATE::RUNNING_LEFT){
            _Animation->SetProp(ID, 1, frameCount, 80, SDL_FLIP_HORIZONTAL);
            SetPrevState();
        }
        else if (playerState == STATE::RUNNING_RIGHT){
            _Animation->SetProp(ID, 1, frameCount, 80);
            SetPrevState();
        }
        else if (playerState == STATE::JUMPING){
            SetPrevState();
            //JumpDust.SetProp("Jump_Dust", 0, 5, 80);
        }
    }
    if (allowInput){
        if (Input::GetInstance()->GetKeyDown(PLAYER_GO_RIGHT_SCANCODE)){
            if (Input::GetInstance()->GetKeyDown(PLAYER_GO_LEFT_SCANCODE) && enableSmoothMovement){
                _RigidBody->applyAccelerationX(ACCELERATE_TO_MAX_VELOCITY * BACKWARD);
                SetPrevState();
                SetState(STATE::RUNNING_LEFT);
            }
            else{
                _RigidBody->applyAccelerationX(ACCELERATE_TO_MAX_VELOCITY * FORWARD);
                SetPrevState();
                SetState(STATE::RUNNING_RIGHT);
            }
        }
        else if (Input::GetInstance()->GetKeyDown(PLAYER_GO_LEFT_SCANCODE)){
            _RigidBody->applyAccelerationX(ACCELERATE_TO_MAX_VELOCITY * BACKWARD);
            SetPrevState();
            SetState(STATE::RUNNING_LEFT);
        }
    }
    // Physics
    _RigidBody->Update(dt);
    CollisionHandler::GetInstance()->PlayerCollisions(_Collider);
    // Update the Animation
    _Animation->Update(dt);
    if (!(JumpDust.GetPrevFrame() == 5 && JumpDust.GetFrame() == 0)) JumpDust.Update(dt);
}

void Player::Clean(){
    delete _Animation;
    delete _RigidBody;
    delete _Transform;
}