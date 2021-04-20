#pragma once
#include <graphics/mesh_instance.h>
#include <graphics/material.h>
#include <graphics/colour.h>

class Particle : public gef::MeshInstance
{
public:

	Particle(gef::Material* material, gef::Mesh* mesh, gef::Matrix44 transform);
	~Particle();

	void Update(float frame_time);

private:
	gef::Material* material_;
	gef::Mesh* mesh_;
	gef::Matrix44 transform_;

	float time_left_;
};

