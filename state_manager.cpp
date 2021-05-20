#include "state_manager.h"
#include <audio/audio_manager.h>

StateManager::StateManager(gef::Platform* platform, gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera, gef::AudioManager* audio_manager, Settings* settings) :
    current_state_(NULL),
    states_({&mainmenu_state_, &ingame_state_, &pausemenu_state_ , &howto_state_, &mainsettings_state_, &splash_state_, &gameover_state_}),
    settings_(settings),
    mainmenu_state_(sprite_renderer, audio_manager, font, platform, this),
    ingame_state_(sprite_renderer, audio_manager, renderer_3d, font, camera, platform, this),
    pausemenu_state_(sprite_renderer, audio_manager, font, platform, this, settings),
    howto_state_(sprite_renderer, audio_manager, font, platform, this),
    mainsettings_state_(sprite_renderer, audio_manager, font, platform, this, settings),
    splash_state_(sprite_renderer, audio_manager, font, platform, this),
    gameover_state_(sprite_renderer, audio_manager, font, platform, this),
    platform_(platform),
    sprite_renderer_(sprite_renderer),
    renderer_3d_(renderer_3d),
    font_(font),
    camera_(camera),
    audio_manager_(audio_manager)
{
    setState(STATE::SPLASHSTATE);
    
}

StateManager::~StateManager()
{
    
}

bool StateManager::Update(float frame_time, const gef::SonyController* controller)
{

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
    if (current_state_) { // if current_state_ isnt null
        current_state_->onExit(); // do onExit for that state
    }

    current_state_ = states_[s];

    current_state_->onEnter(); // do onEnter for new state
}

void StateManager::quit()
{
    current_state_->onExit();
    current_state_ = NULL;
}
