#include "cloud_manager.h"

CloudManager::CloudManager(gef::Platform* platform)
{
	srand(time(NULL));

	for (int i = 0; i < 100; i++) {
		float rand_x = float(rand() % (400 -(-400) + 1) + (-400) );
		float rand_y = float(rand() % 400 + 25);
		float rand_z = float(rand() % (15 - (-50) + 1) + (-50));

		Cloud* cloud = new Cloud(gef::Vector4(rand_x, rand_y, rand_z), rand() % 1 + 5, platform);
		clouds_.push_back(cloud);
	}
}

CloudManager::~CloudManager()
{
	for (auto c : clouds_) {
		delete c;
	}
	clouds_.clear();
}

void CloudManager::Update(float frame_time)
{
	for (auto c : clouds_) {
		c->Update(frame_time);
	}
}

void CloudManager::Render(gef::Renderer3D* renderer_3d, gef::Vector4 player_pos)
{
	for (auto c : clouds_) {
		if (std::abs(c->getPosition().x() - player_pos.x()) < 110.f && std::abs(c->getPosition().y() - player_pos.y()) < 60.f) { // only render if player is near
			c->Render(renderer_3d);
		}
	}
}
