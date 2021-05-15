#pragma once

#include "particle.h"
#include "primitive_builder.h"
#include <vector>
#include <graphics/mesh_instance.h>
#include <graphics/renderer_3d.h>
#include "player.h"
#include "primitive_builder.h"
#include <system/platform.h>

class ParticleManager
{
public:
	ParticleManager(gef::Platform* platform);
	~ParticleManager();

	void Update(float frame_time);
	void Render(gef::Renderer3D* renderer_3d);

	void setTarget(Player* player) 
	{
		player_ = player;
	};

private:

	void addParticle(gef::Vector4 pos);

	std::vector<Particle*> particles_;

	Player* player_;
	PrimitiveBuilder* primitive_builder_;
	gef::Platform* platform_;

	float timer_;
};

