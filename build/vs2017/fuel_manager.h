#pragma once

#include "fuel.h"

#include <vector>

class FuelManager
{
public:
	FuelManager(b2World* world, gef::Platform* platform, std::vector<b2Body*>* bodies_scheduled_for_removal);
	~FuelManager();

	void Update(float frame_time);
	void Render(gef::Renderer3D* renderer_3d, b2Vec2 player_pos);
	void Reset();

	void spawnFuel(b2World* world, int num, b2Vec2 player_pos);

private:
	std::vector<Fuel*> fuel_vec_;
	gef::Platform* platform_;

	b2World* world_;

	std::vector <b2Body*>* bodies_scheduled_for_removal_;
	
};

