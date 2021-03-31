#include "StateManager.h"

StateManager::StateManager(gef::Platform* platform, gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera) :
    current_state_(&menu_state_),
    states({&menu_state_, &in_game_state_}),
    menu_state_(sprite_renderer, font, platform, states),
    in_game_state_(sprite_renderer, renderer_3d, font, camera, platform, states),
    platform_(platform),
    sprite_renderer_(sprite_renderer),
    renderer_3d_(renderer_3d),
    font_(font),
    camera_(camera)
{
   
}

StateManager::~StateManager()
{
    
}

bool StateManager::Update(float frame_time, const gef::SonyController* controller)
{
    current_state_ = current_state_->Update(frame_time, controller);
    if (!current_state_) {
        return false;
    }
    return true;
}

void StateManager::Render()
{
    if (current_state_) {
        current_state_->Render();
    }
}

void StateManager::setState(State* state)
{
    current_state_->onExit();
    current_state_ = state;
    current_state_->onEnter();
}
