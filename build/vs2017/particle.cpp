#include "particle.h"

Particle::Particle(gef::Material* material, gef::Mesh* mesh, gef::Matrix44 transform) :
	material_(material),
	mesh_(mesh),
	transform_(transform),
	time_left_(1.f)
{
	set_mesh(mesh_);
	
	this->set_transform(transform);
}

Particle::~Particle()
{
}

void Particle::Update(float frame_time)
{
	time_left_ -= frame_time;
	material_->set_colour(gef::Colour(1.0f, 1.0f, 1.0f, time_left_).GetABGR());
	
}
