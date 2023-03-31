#include "Collider.hpp"
#include "Engine.hpp"

Collider::Collider(){}

Collider::~Collider(){}

void Collider::Render(){
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), R, G, B, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}