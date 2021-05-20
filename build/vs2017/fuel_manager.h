#pragma once

#include "fuel.h"

#include <vector>

class FuelManager
{
public:
	FuelManager(b2World* world, gef::Platform* platform);
	~FuelManager();

	void Update(float frame_time);
	void Render(gef::Renderer3D* renderer_3d, b2Vec2 player_pos);
	void Reset();

private:
	std::vector<Fuel*> fuel_vec_;
	gef::Platform* platform_;

	b2World* world_;

	void spawnFuel(b2World* world, int num, b2Vec2 player_pos);
};

