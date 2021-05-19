#include "particle_manager.h"

ParticleManager::ParticleManager(gef::Platform* platform) :
	timer_(0.f),
	player_(NULL),
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

	delete primitive_builder_;
	primitive_builder_ = NULL;
}

void ParticleManager::Update(float frame_time)
{
	if (player_->isThrusting()) {
		timer_ += frame_time;
		if (timer_ >= 0.02f) { // spawn rate =~ 0.02s
			timer_ = 0.f;
			addParticle(&gef::Vector4(-0.55f, 0.f, 0.f)); // left booster
			addParticle(&gef::Vector4(0.55f, 0.f, 0.f));  // right booster
		}
	}

	for (int i = 0; i < particles_.size(); i++) {
		if (!particles_[i]->Update(frame_time)) {
			particles_[i]->~Particle();
			delete particles_[i];
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

void ParticleManager::Reset()
{
	for (auto p : particles_) {
		delete p;
	}
	particles_.clear();
}

void ParticleManager::addParticle(gef::Vector4 *pos)
{
	gef::Material* particle_material = new gef::Material(); // create new material (each particle has own material)
	particle_material->set_colour(gef::Colour(1.0f, 1.0f, 1.0f).GetABGR()); // initial colour is white
	gef::Mesh* particle_mesh = primitive_builder_->CreateSphereMesh(0.6f, 5, 5, gef::Vector4(0.f, 0.f, 0.f), particle_material); // create sphere mesh with material

	gef::Matrix44* transform = new gef::Matrix44(); // create transform matrix that translates to pos
	transform->SetIdentity();
	transform->SetTranslation(*pos);

	*transform = *transform * player_->transform(); // translates from player by pos

	particles_.push_back(new Particle(particle_material, particle_mesh, transform));
}
