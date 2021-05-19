#pragma once

#include <graphics/sprite.h>
#include <maths/vector2.h>
#include <vector>
#include <system/platform.h>
#include <graphics/sprite_renderer.h>

class StarsManager
{
public:
	StarsManager(gef::Platform* platform, int num_stars);
	~StarsManager();

	void Render(gef::SpriteRenderer* sprite_renderer, float alpha);


private:
	std::vector<gef::Sprite*> stars;

	gef::Platform* platform_;
	int num_stars_;
};

