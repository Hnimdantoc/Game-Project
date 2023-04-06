#include "Player1.hpp"
#include "CollisionHandler.hpp"
#include "GameObjectHandler.hpp"
#include "Planet.hpp"
#include "Scenes.hpp"

Player1* Player1::Static_Instance = nullptr;

Player1::Player1(){
    Static_Instance = this;
}
Player1::~Player1(){
    SDL_Log("Player1 destroyed");
}

Player1::Player1(Properties* prop){
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
    player1Action.first = STATE::STANDING;
    player1Action.second = FACE::RIGHT;
    SetPrevState();
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
    _Collider = Collider({_Rect.x + OFFSET, _Rect.y + OFFSET, _Rect.w - 2*OFFSET, _Rect.h - OFFSET});
    JumpDust1.SetProp("Jump_Dust", 0, 5, 80);
    JumpDust2.SetProp("Jump_Dust", 0, 5, 80);
    delete prop;
}

void Player1::Render(){
    // Draw Player1
    _Animation->Render(_Transform->x, _Transform->y, w, h, PLAYER_SCALE);
    // Visualize collision box
    _Collider.Render();
    if (!(JumpDust1.GetPrevFrame() == 4 && JumpDust1.GetFrame() == 0) && jumps == 1) JumpDust1.Render(j1_x, j1_y, 23, 5, 2);
    if (!(JumpDust2.GetPrevFrame() == 4 && JumpDust2.GetFrame() == 0) && jumps == 0) JumpDust2.Render(j2_x, j2_y, 23, 5, 2);
}

void Player1::Update(float& dt){
    if (prevAction != player1Action) _NeedChangeState = true;
    if (_NeedChangeState){
        _NeedChangeState = false;
        switch (player1Action.first){
            case STATE::STANDING:
                _Animation->SetProp(ID, 0, frameCount, 150);
                break;
            case STATE::RUNNING:
                _Animation->SetProp(ID, 1, frameCount, 80);
                break;
            case STATE::JUMPING:
                break;
        }
        if (player1Action.second == FACE::LEFT) _Animation->SetFlip(SDL_FLIP_HORIZONTAL);
        SetPrevState();
    }
    if (allowInput){
        if (Input::GetInstance()->GetKeyDown(PLAYER1_GO_RIGHT_SCANCODE)){
            if (Input::GetInstance()->GetKeyDown(PLAYER1_GO_LEFT_SCANCODE) && enableSmoothMovement){
                _RigidBody->applyAccelerationX(ACCELERATE_TO_MAX_VELOCITY * BACKWARD);
                SetPrevState();
                SetState(STATE::RUNNING, FACE::LEFT);
                if (Player::GetInstance()->GetRigidBody()->getVelocity().x == 0 && CollisionHandler::GetInstance()->CheckCollision(_Collider, Player::GetInstance()->getCollider())){
                    Player::GetInstance()->GetRigidBody()->applyForceX(-10000.0f);
                }
            }
            else{
                _RigidBody->applyAccelerationX(ACCELERATE_TO_MAX_VELOCITY * FORWARD);
                SetPrevState();
                SetState(STATE::RUNNING, FACE::RIGHT);
                if (Player::GetInstance()->GetRigidBody()->getVelocity().x == 0 && CollisionHandler::GetInstance()->CheckCollision(_Collider, Player::GetInstance()->getCollider())){
                    Player::GetInstance()->GetRigidBody()->applyForceX(10000.0f);
                }
            }
        }
        else if (Input::GetInstance()->GetKeyDown(PLAYER1_GO_LEFT_SCANCODE)){
            _RigidBody->applyAccelerationX(ACCELERATE_TO_MAX_VELOCITY * BACKWARD);
            SetPrevState();
            SetState(STATE::RUNNING, FACE::LEFT);
            if (Player::GetInstance()->GetRigidBody()->getVelocity().x == 0 && CollisionHandler::GetInstance()->CheckCollision(_Collider, Player::GetInstance()->getCollider())){
                Player::GetInstance()->GetRigidBody()->applyForceX(-10000.0f);
            }
        }
    }
    // Physics
    if (!dashing) _RigidBody->Update(dt);
    else {
        Player1::GetInstance()->GetRigidBody()->setPosition().y = Player1::GetInstance()->GetRigidBody()->getVelocity().y * dt;
        Player1::GetInstance()->GetRigidBody()->setPosition().x = Player1::GetInstance()->GetRigidBody()->getVelocity().x * dt;
        Player1::GetInstance()->GetRigidBody()->applyVelocityX(Player1::GetInstance()->GetRigidBody()->getAcceleration().x * dt + Player1::GetInstance()->GetRigidBody()->getVelocity().x);
        Player1::GetInstance()->DashTime() += dt;
        Player1::GetInstance()->DashLength() -= abs(Player1::GetInstance()->GetRigidBody()->getPosition().x) + abs(Player1::GetInstance()->GetRigidBody()->getPosition().y);
        if (Player1::GetInstance()->DashTime() >= 0.15 || Player1::GetInstance()->DashLength() <= 0) {
            Player1::GetInstance()->CanDash() = true;
            Player1::GetInstance()->Dashing() = false;
            Player1::GetInstance()->SetAllowInput() = true;
            Player1::GetInstance()->GetRigidBody()->resetAccelerationX();
            Player1::GetInstance()->GetRigidBody()->resetVelocity();
            Player1::GetInstance()->GetRigidBody()->resetPosition();
        }
    }
    _RigidBody->resetForceX();
    Player1::GetInstance()->getTransform()->translateVector({_RigidBody->getPosition().x, _RigidBody->getPosition().y});
    Player1::GetInstance()->UpdateCollider();
    // Update the Animation
    _Animation->Update(dt);
    if (!(JumpDust1.GetPrevFrame() == 4 && JumpDust1.GetFrame() == 0) && jumps == 1) JumpDust1.Update(dt);
    if (!(JumpDust2.GetPrevFrame() == 4 && JumpDust2.GetFrame() == 0) && jumps == 0) JumpDust2.Update(dt);
    // Update Collision box
    CollisionHandler::GetInstance()->Player1Collisions(_Collider);
}

void Player1::Clean(){
    delete _Animation;
    delete _RigidBody;
    delete _Transform;
}