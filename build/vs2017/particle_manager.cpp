#include "particle_manager.h"

ParticleManager::ParticleManager(gef::Platform* platform):
	timer_(0.f),
	target_(NULL),
	platform_(platform)
{
	primitive_builder_ = new PrimitiveBuilder(*platform_);
	srand(time(NULL));
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

	if (timer_ >= 0.02f) {
		timer_ = 0.f;
		if (target_->isThrusting()) {

			gef::Material* particle_material = new gef::Material();
			particle_material->set_colour(gef::Colour(1.0f, 1.0f, 1.0f).GetABGR());
			gef::Mesh* particle_mesh = primitive_builder_->CreateSphereMesh(0.6f, 5, 5, gef::Vector4(0.f, 0.f, 0.f), particle_material);

			addParticle(particle_material, particle_mesh, gef::Vector4(-0.55f, 0.f, 0.f)); // left booster
			addParticle(particle_material, particle_mesh, gef::Vector4(0.55f, 0.f, 0.f)); // right booster
		}
	}

	for (int i = 0; i < particles_.size(); i++) {
		if (!particles_[i]->Update(frame_time)) {
			particles_.erase(particles_.begin() + i); 
		}
	}
}

void ParticleManager::Render(gef::Renderer3D* renderer_3d)
{
	for (auto p : particles_) {
		renderer_3d->DrawMesh(*p);
	}
}

void ParticleManager::addParticle(gef::Material* mat, gef::Mesh* mesh, gef::Vector4 pos)
{
	gef::Matrix44 transform;
	transform.SetIdentity();
	transform.SetTranslation(pos);

	transform = transform * target_->transform();

	Particle* particle = new Particle(mat, mesh, transform);

	particles_.push_back(particle);
}
