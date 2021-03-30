#include "StateManager.h"

StateManager::StateManager(gef::Platform* platform, gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font):
    current_state_(&in_game_state_),
    menu_state_(sprite_renderer, font),
    in_game_state_(sprite_renderer, renderer_3d, font)
{
    platform_ = platform;
    sprite_renderer_ = sprite_renderer;
    renderer_3d_ = renderer_3d;
}

StateManager::~StateManager()
{
}

bool StateManager::Update(float frame_time, const gef::SonyController* controller)
{
    current_state_->Update(frame_time, controller);
    return true;
}

void StateManager::Render()
{
    current_state_->Render();
}

void StateManager::setState(State* state)
{
    current_state_ = state;
}
