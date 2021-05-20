#pragma once

#include "graphics/sprite_renderer.h"
#include "graphics/sprite.h"
#include "graphics/colour.h"
#include "graphics/font.h"
#include "system/platform.h"

class HUD
{
public:
	HUD();
	~HUD();

	void Update(float fuel);
	void Render(gef::SpriteRenderer* sprite_renderer, gef::Font* font);

private:

	gef::Sprite fuel_bar_;

	gef::Vector4 colour_;

};

