#include "stars_manager.h"

StarsManager::StarsManager(gef::Platform* platform, int num_stars):
	platform_(platform),
	num_stars_(num_stars)
{

	for (int i = 0; i < num_stars_; i++) {
		gef::Sprite* star = new gef::Sprite();
		star->set_colour(gef::Colour(1.0f, 1.0f, 1.0f, 1.0f).GetABGR());
		star->set_position(gef::Vector4(float(rand() % platform_->width()), float(rand() % platform_->height()), 30.f));
		float size = float(rand() % + 2);
		star->set_width(size);
		star->set_height(size);

		stars.push_back(star);
	}
}

StarsManager::~StarsManager()
{
	for (auto s : stars) {
		delete s;
	}
	stars.clear();
}

void StarsManager::Render(gef::SpriteRenderer* sprite_renderer, float alpha)
{
	for (size_t i = 0; i < num_stars_; i++) {
		stars[i]->set_colour(gef::Colour(1.0f, 1.0f, 1.0f, alpha).GetABGR());
		sprite_renderer->DrawSprite(*stars[i]);
	}
}


