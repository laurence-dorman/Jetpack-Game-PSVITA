#pragma once

#include "cloud.h"
#include <vector>

class CloudManager
{
public:
	CloudManager(gef::Platform* platform);
	~CloudManager();

	void Update(float frame_time);
	void Render(gef::Renderer3D* renderer_3d, gef::Vector4 player_pos);
	void Reset();

private:
	std::vector<Cloud*> clouds_;
	gef::Platform* platform_;

	void spawnClouds(int num);
};

