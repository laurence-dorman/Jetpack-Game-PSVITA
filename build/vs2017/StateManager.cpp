#include "StateManager.h"

StateManager::StateManager():
    current_state_(&menu_state_)
{
 
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
