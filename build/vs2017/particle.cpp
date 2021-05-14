#include "particle.h"
#include "graphics/primitive.h"
#include "maths/math_utils.h"

#include "system/debug_log.h"

Particle::Particle(gef::Material* material, gef::Mesh* mesh, gef::Matrix44 transform) :
	material_(material),
	mesh_(mesh),
	transform_(transform),
	time_left_(1.f),
	time_alive_(0.f),
	alpha_(0.75f)
{

	set_mesh(mesh_);

	rotation_ = gef::DegToRad(rand() % (280 - 260 + 1) + 260);
	//rotation_ = gef::DegToRad(270.f);
	this->set_transform(transform);
}

Particle::~Particle()
{
}

bool Particle::Update(float frame_time)
{
	time_left_ -= frame_time;
	time_alive_ += frame_time;

	material_->set_colour(gef::Colour(time_left_, time_left_, time_left_, time_left_).GetABGR());

	const gef::Primitive* primitive = this->mesh()->GetPrimitive(0);        // Extract the primitive you want
	const_cast<gef::Primitive*>(primitive)->set_material(material_);    // We need to const_cast so we can make changes to the primitive

	gef::Matrix44 translation;
	
	translation.SetIdentity();
	translation.SetTranslation(gef::Vector4(cosf(rotation_) / 5.f, sinf(rotation_)/ 5.f, 0));
	
	gef::Matrix44 new_transform;

	translation = translation * this->transform();
	
	gef::Vector4 pos = translation.GetTranslation();
	
	gef::Matrix44 scale;
	gef::Vector4 scale_vec(1.01f, 1.01f, 1.01f);
	scale.Scale(scale_vec);
	
	translation = translation * scale;
	
	translation.SetTranslation(pos);

	this->set_transform( translation);

	if (time_left_ <= 0.05f) {
		return false; // dead
	}
	return true; // alive
}
