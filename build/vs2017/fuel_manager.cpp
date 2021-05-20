#include "fuel_manager.h"

FuelManager::FuelManager(b2World* world, gef::Platform* platform, std::vector<b2Body*>* bodies_scheduled_for_removal) :
	platform_(platform),
	world_(world),
	bodies_scheduled_for_removal_(bodies_scheduled_for_removal)
{
	srand(time(NULL));

	spawnFuel(world, 1, b2Vec2(0.f, 9.57f)); // initial spawn
}

FuelManager::~FuelManager()
{
	for (auto f : fuel_vec_) {
		delete f;
	}
	fuel_vec_.clear();
}

void FuelManager::Update(float frame_time)
{
	for (auto f : fuel_vec_) {
		f->Update(frame_time);
	}

}

void FuelManager::Render(gef::Renderer3D* renderer_3d, b2Vec2 player_pos)
{
	for (auto f : fuel_vec_) {
		if (std::abs(f->getPosition().x - player_pos.x) < 110.f && std::abs(f->getPosition().y - player_pos.y) < 60.f) { // only render if player is near
			f->Render(renderer_3d);
		}
	}
}

void FuelManager::Reset()
{
	for (auto f : fuel_vec_) {
		delete f;
	}
	fuel_vec_.clear();

	spawnFuel(world_, 1, b2Vec2(0.f, 9.57f));
}

void FuelManager::spawnFuel(b2World* world, int num, b2Vec2 player_pos)
{
	for (auto f : fuel_vec_) { // remove old fuels
		f->~Fuel();
		bodies_scheduled_for_removal_->push_back(f->getBody()); // schedule body for removal
	}

	fuel_vec_.clear(); // clear vec

	// generate position of new fuel based on player position and random
	float rand_x = float(rand() % ( (int(player_pos.x) + SPAWN_DELTA_X) - (int(player_pos.x) - SPAWN_DELTA_X) + 1) + (int(player_pos.x) - SPAWN_DELTA_X));
	float y = player_pos.y + (float)SPAWN_DELTA_Y;

	Fuel* fuel = new Fuel(world, b2Vec2(rand_x, y), platform_);
	fuel_vec_.push_back(fuel);
	
}
