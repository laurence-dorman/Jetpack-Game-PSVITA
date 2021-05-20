#include "fuel.h"
#include "system/platform.h"
#include "system/debug_log.h"
#include "maths/math_utils.h"

Fuel::Fuel(b2World* world, b2Vec2 pos, gef::Platform* platform) :
	position_(pos),
	scene_assets_(NULL),
	rotation_(0.f)
{
	set_type(FUEL);

	scene_assets_ = new gef::Scene();
	scene_assets_ = model_loader_->LoadSceneAssets(*platform, "models/fuel.scn");

	if (scene_assets_) {
		this->set_mesh(model_loader_->GetMeshFromSceneAssets(scene_assets_));
	}
	else {
		gef::DebugOut("Scene file %s failed to load\n", "models/fuel.scn");
	}

	// create a physics body for the player
	b2BodyDef fuel_body_def;
	fuel_body_def.type = b2_staticBody;
	fuel_body_def.position = pos;
	// create a connection between the rigid body and GameObject
	fuel_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	fuel_body_ = world->CreateBody(&fuel_body_def);

	// create the shape for the player
	b2PolygonShape fuel_shape;
	fuel_shape.SetAsBox(2.f, 2.f, b2Vec2(0.0f, -1.0f), 0);

	// create the fixture
	b2FixtureDef fuel_fixture_def;
	fuel_fixture_def.shape = &fuel_shape;

	// create the fixture on the rigid body
	fuel_body_->CreateFixture(&fuel_fixture_def);

	UpdateFromSimulation(fuel_body_);
}

Fuel::~Fuel()
{
}

void Fuel::Update(float frame_time)
{
	rotation_ = frame_time;

	fuel_body_->SetTransform(fuel_body_->GetPosition(), rotation_);
	
	gef::Matrix44 fuel_transform;
	fuel_transform.SetIdentity();
	
	fuel_transform.RotationY(fuel_body_->GetAngle());
	
	this->set_transform(transform_ * fuel_transform);

}

void Fuel::Render(gef::Renderer3D* renderer_3d)
{
	renderer_3d->DrawMesh(*this);
}
