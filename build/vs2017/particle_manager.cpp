#include "particle_manager.h"

ParticleManager::ParticleManager(gef::Platform* platform):
	timer_(0.f),
	target_(NULL),
	platform_(platform)
{
	primitive_builder_ = new PrimitiveBuilder(*platform_);
	particle_material_ = new gef::Material();
	particle_material_->set_colour(gef::Colour(1.0f, 1.0f, 1.0f).GetABGR());
	particle_mesh_ = primitive_builder_->CreateSphereMesh(1.f, 5, 5, gef::Vector4(0.f, 0.f, 0.f), particle_material_);
}

ParticleManager::~ParticleManager()
{
	for (auto p : particles_) {
		delete p;
	}
	particles_.clear();
}

void ParticleManager::Update(float frame_time)
{
	timer_ += frame_time;

	if (timer_ >= 0.1f) {
		timer_ = 0.f;
		Particle* particle = new Particle(particle_material_, particle_mesh_, target_->transform());

		particles_.push_back(particle);
	}
}

void ParticleManager::Render(gef::Renderer3D* renderer_3d)
{
	for (auto p : particles_) {
		renderer_3d->DrawMesh(*p);
	}
}
