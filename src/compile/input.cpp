#include "input.hpp"
#include "Player.hpp"
#include "Planet.hpp"
#include "SceneManager.hpp"
#include "Scenes.hpp"

Input* Input::static_Instance = nullptr;

Input::Input(){
    KeyState = SDL_GetKeyboardState(NULL);
}   

Input::~Input(){}

void Input::Listen(){    
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                Engine::GetInstance()->setGameState() = GAME_STATE::EXIT;
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_KEYUP:
                KeyUp();
                break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key_scan_code){
    return KeyState[key_scan_code] == 1;
}

void Input::KeyUp(){
    KeyState = SDL_GetKeyboardState(NULL);
    
    if (SceneManager::GetInstance()->GetCurrentSceneID() == PLAYSCENE){
        Player::GetInstance()->SetPrevState();
        switch (event.key.keysym.scancode){
            case PLAYER_GO_RIGHT_SCANCODE:
                Player::GetInstance()->GetRigidBody()->applyAccelerationX(BACKWARD * DECCELERATE_TO_ZERO);
                Player::GetInstance()->SetState(STATE::STANDING_RIGHT);
                break;
            case PLAYER_GO_LEFT_SCANCODE:
                Player::GetInstance()->GetRigidBody()->applyAccelerationX(FORWARD * DECCELERATE_TO_ZERO);
                Player::GetInstance()->SetState(STATE::STANDING_LEFT);
                break;
            case SDL_SCANCODE_ESCAPE:
                SceneManager::GetInstance()->ChangeScene(MENU_SCENE);
                break;
        }
        if (Player::GetInstance()->GetPrevState() != Player::GetInstance()->GetState() && SceneManager::GetInstance()->GetCurrentSceneID() == PLAYSCENE) Player::GetInstance()->NeedChangeState() = true;
    }
    else if (SceneManager::GetInstance()->GetCurrentSceneID() == MENU_SCENE){

    }
}

void Input::KeyDown(){
    KeyState = SDL_GetKeyboardState(NULL);
    
    if (SceneManager::GetInstance()->GetCurrentSceneID() == PLAYSCENE){
        if (event.key.keysym.scancode == PLAYER_JUMP_SCANCODE && Player::GetInstance()->GetRemainJumps() > 0){
        Player::GetInstance()->SetInAir() = true;
        Player::GetInstance()->GetRigidBody()->applyVelocityY(JUMP_VELOCITY * UPWARD);
        Player::GetInstance()->SetAllowInput() = false;
        Player::GetInstance()->SetPrevState();
        Player::GetInstance()->ReduceJumps();
        Player::GetInstance()->SetState(STATE::JUMPING);
        }
        if (event.key.keysym.scancode == PLAYER_DASH_SCANCODE && Player::GetInstance()->CanDash() && SDL_GetTicks() - Player::GetInstance()->GetLastDash() >= DASH_COOL_DOWN){
            Player::GetInstance()->Dashing() = true;
            Player::GetInstance()->CanDash() = false;
            Player::GetInstance()->DashLength() = 150;
            Player::GetInstance()->DashTime() = 0;
            Player::GetInstance()->GetLastDash() = SDL_GetTicks();
            Player::GetInstance()->GetRigidBody()->resetAccelerationX();
            Player::GetInstance()->GetRigidBody()->resetVelocity();
            Player::GetInstance()->GetRigidBody()->resetPosition();
            Player::GetInstance()->SetAllowInput() = false;
            if (Player::GetInstance()->GetState() == STATE::RUNNING_RIGHT) Player::GetInstance()->GetRigidBody()->applyVelocityX(DASH_VELLOCITY * FORWARD);
            else if (Player::GetInstance()->GetState() == STATE::RUNNING_LEFT) Player::GetInstance()->GetRigidBody()->applyVelocityX(DASH_VELLOCITY * BACKWARD);
            else Player::GetInstance()->GetRigidBody()->applyVelocityY(DASH_VELLOCITY * UPWARD);
        }
        
        if (KeyState[PLAYER_GO_RIGHT_SCANCODE] && event.key.keysym.scancode == PLAYER_GO_LEFT_SCANCODE) Player::GetInstance()->SetSmoothMovement() = true;
        if (KeyState[PLAYER_GO_LEFT_SCANCODE] && event.key.keysym.scancode == PLAYER_GO_RIGHT_SCANCODE) Player::GetInstance()->SetSmoothMovement() = false;    
    }
    else if (SceneManager::GetInstance()->GetCurrentSceneID() == MENU_SCENE){
        switch(event.key.keysym.scancode){
            case SDL_SCANCODE_DOWN:
                Menu::GetInstance()->j++;
                if (Menu::GetInstance()->j == Menu::GetInstance()->GetVectorRect()[Menu::GetInstance()->i].size()) Menu::GetInstance()->j = 0;
                Menu::GetInstance()->currentRect = Menu::GetInstance()->GetVectorRect()[Menu::GetInstance()->i][Menu::GetInstance()->j];
                break;
            case SDL_SCANCODE_UP:
                Menu::GetInstance()->j--;
                if (Menu::GetInstance()->j < 0) Menu::GetInstance()->j = Menu::GetInstance()->GetVectorRect()[Menu::GetInstance()->i].size()-1;
                Menu::GetInstance()->currentRect = Menu::GetInstance()->GetVectorRect()[Menu::GetInstance()->i][Menu::GetInstance()->j];
                break;
            case SDL_SCANCODE_RETURN:
                if (Menu::GetInstance()->currentRect == &Menu::GetInstance()->play_rect) SceneManager::GetInstance()->ChangeScene(PLAYSCENE);
                break;
        }
    }
}