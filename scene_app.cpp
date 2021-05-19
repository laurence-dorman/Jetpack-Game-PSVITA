#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <graphics/mesh.h>
#include <maths/math_utils.h>
#include <input/sony_controller_input_manager.h>
#include <graphics/sprite.h>
#include <audio/audio_manager.h>

#include "load_texture.h"

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	input_manager_(NULL),
	audio_manager_(NULL),
	font_(NULL),
	controller_manager_(NULL),
	state_manager_(NULL),
	camera_(NULL)
{
}

void SceneApp::Init()
{
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	InitFont();

	// init camera
	camera_ = new Camera(platform_); 

	// initialise input manager
	input_manager_ = gef::InputManager::Create(platform_);

	// audio manager
	audio_manager_ = gef::AudioManager::Create();
	audio_manager_->SetMasterVolume(50.f);

	// state manager
	state_manager_ = new StateManager(&platform_, sprite_renderer_, renderer_3d_, font_, camera_, audio_manager_);

}

void SceneApp::CleanUp()
{
	delete input_manager_;
	input_manager_ = NULL;

	CleanUpFont();

	audio_manager_->UnloadAllSamples();
	audio_manager_->UnloadMusic();

	delete audio_manager_;
	audio_manager_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete state_manager_;
	state_manager_ = NULL;

	delete camera_;
	camera_ = NULL;
}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	input_manager_->Update();

	// INPUT
	controller_manager_ = input_manager_->controller_input();

	if (controller_manager_)
	{
		const gef::SonyController* controller = controller_manager_->GetController(0);

		if (controller)
		{
			return state_manager_->Update(frame_time, controller);
		}
	}

	return true;
}


void SceneApp::Render()
{
	sprite_renderer_->Begin();
	state_manager_->Render();
	DrawHUD();
}


void SceneApp::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("yu_gothic");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void SceneApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(5.0f, 5.0f, -0.9f), 0.75f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f",  fps_);
	}
	sprite_renderer_->End();
}