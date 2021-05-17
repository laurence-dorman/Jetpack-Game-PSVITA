#include "state_manager.h"

StateManager::StateManager(gef::Platform* platform, gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera) :
    current_state_(NULL),
    old_state_(NULL),
    states_({&mainmenu_state_, &ingame_state_, &pausemenu_state_ }),
    mainmenu_state_(sprite_renderer, font, platform, this),
    pausemenu_state_(sprite_renderer, font, platform, this),
    ingame_state_(sprite_renderer, renderer_3d, font, camera, platform, this),
    platform_(platform),
    sprite_renderer_(sprite_renderer),
    renderer_3d_(renderer_3d),
    font_(font),
    camera_(camera)
{
    setState(STATE::MENUSTATE);
}

StateManager::~StateManager()
{
    
}

bool StateManager::Update(float frame_time, const gef::SonyController* controller)
{
    old_state_ = current_state_;

    current_state_->Update(frame_time, controller);

    if (!current_state_) { // if current_state_ is null, return false (game closing)
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

void StateManager::setState(STATE s)
{
    if (old_state_) { // if old_state_ isnt null
        old_state_->onExit(); // do onExit for that state
    }

    current_state_ = states_[s];

    current_state_->onEnter(); // do onEnter for new state
}

void StateManager::quit()
{
    current_state_->onExit();
    current_state_ = NULL;
}
