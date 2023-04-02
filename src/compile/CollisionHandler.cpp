#include "CollisionHandler.hpp"
#include "Player.hpp"
#include "Engine.hpp"
#include "Scenes.hpp"
#include "GameObjectHandler.hpp"

CollisionHandler* CollisionHandler::StaticInstance = nullptr;

CollisionHandler::CollisionHandler(){}
CollisionHandler::~CollisionHandler(){
    SDL_Log("Collision Handler destroyed");
}

bool CollisionHandler::CheckCollision(Collider& _rectA, Collider& _rectB){
    //AABB method
    return (_rectA.GetBox().x < _rectB.GetBox().x + _rectB.GetBox().w) && (_rectA.GetBox().x + _rectA.GetBox().w > _rectB.GetBox().x) && (_rectA.GetBox().y < _rectB.GetBox().y + _rectB.GetBox().h) && (_rectA.GetBox().h + _rectA.GetBox().y > _rectB.GetBox().y);
}

bool CollisionHandler::GroundCollision(Collider& _rect){
    return (_rect.GetBox().y + _rect.GetBox().h > Engine::GetInstance()->GetGround().y);
}

void CollisionHandler::PlayerCollisions(Collider& player_rect){
    // Ground Collision
    if (GroundCollision(player_rect)){
        Player::GetInstance()->SetInAir() = false;
        Player::GetInstance()->SetTransform()->y = Engine::GetInstance()->GetGround().y - player_rect.GetBox().h;
        Player::GetInstance()->GetRigidBody()->resetVelocityY();
        Player::GetInstance()->ResetJumps();
    }

    // Map's sides collision
    if (player_rect.GetBox().x < 0) Player::GetInstance()->SetTransform()->x = -OFFSET;
    else if (player_rect.GetBox().x > (WIDTH-player_rect.GetBox().w)) Player::GetInstance()->SetTransform()->x = WIDTH-player_rect.GetBox().w-OFFSET;

    // Check collision with every gameobject
    for (std::set<GameObject*, custom_set>::iterator i = ((*GameObjectHandler::GetInstance()->GetGameObjectMap())[*GameObjectHandler::GetInstance()->ptr_current_scene]).begin(); i != ((*GameObjectHandler::GetInstance()->GetGameObjectMap())[*GameObjectHandler::GetInstance()->ptr_current_scene]).end(); i++){
        if (*i == Player::GetInstance()) continue;
        if ((strcmp((*i)->GetID(), "sun") == 0 || strcmp((*i)->GetID(), "moon") == 0) && CheckCollision(player_rect, (*i)->getCollider())){
            if (strcmp((*i)->GetID(), "sun") == 0){
                Scene_0::GetInstance()->HOURS.second += 1440/Scene_0::GetInstance()->max_sun;
                if (Scene_0::GetInstance()->HOURS.second >= 60){
                    Scene_0::GetInstance()->HOURS.first += 1;
                    Scene_0::GetInstance()->HOURS.second -= 60;
                }
            }
            else{
                Engine::GetInstance()->setGameState() = GAME_STATE::EXIT;
            }
            (*i)->Clean();
            ((*GameObjectHandler::GetInstance()->GetGameObjectMap())[*GameObjectHandler::GetInstance()->ptr_current_scene]).erase(i);
            delete *i;
        }
        else if (Player::GetInstance()->GetRigidBody()->getVelocity().y >= 0){ 
            if (strcmp((*i)->GetID(), "Left_platform") == 0 && 
                CheckCollision(player_rect, (*i)->getCollider()) && 
                player_rect.GetBox().y + player_rect.GetBox().h <= (*i)->getCollider().GetBox().y + MAX_POS_Y) {

                Player::GetInstance()->SetTransform()->y = (*i)->getCollider().GetBox().y - player_rect.GetBox().h;
                Player::GetInstance()->GetRigidBody()->resetVelocityY();
                Player::GetInstance()->SetInAir() = false;
                Player::GetInstance()->ResetJumps();
            }
            else if (strcmp((*i)->GetID(), "Right_platform") == 0 && 
                     CheckCollision(player_rect, (*i)->getCollider()) && 
                     player_rect.GetBox().y + player_rect.GetBox().h <= (*i)->getCollider().GetBox().y + MAX_POS_Y) {
                        
                Player::GetInstance()->SetInAir() = false;
                Player::GetInstance()->SetTransform()->y = (*i)->getCollider().GetBox().y - player_rect.GetBox().h;
                Player::GetInstance()->GetRigidBody()->resetVelocityY();
                Player::GetInstance()->ResetJumps();
            }
            else if (strcmp((*i)->GetID(), "Hover_platform") == 0 && 
                     CheckCollision(player_rect, (*i)->getCollider()) && 
                     player_rect.GetBox().y + player_rect.GetBox().h <= (*i)->getCollider().GetBox().y + MAX_POS_Y + 1) {
                Player::GetInstance()->SetInAir() = false;
                Player::GetInstance()->SetTransform()->y = (*i)->getCollider().GetBox().y - player_rect.GetBox().h;
                Player::GetInstance()->GetRigidBody()->resetVelocityY();
                Player::GetInstance()->ResetJumps();
            }
            // Double from platforms
            //else Player::GetInstance()->SetInAir() = true;
        }
    }
    // Update Player Rect
    Player::GetInstance()->UpdateCollider();
}