#include "fuel.h"
#include "system/platform.h"
#include "system/debug_log.h"
#include "maths/math_utils.h"

Fuel::Fuel(b2World* world, b2Vec2 pos, gef::Platform* platform) :
	position_(pos),
	scene_assets_(NULL)
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

	// create a physics body for the fuel
	b2BodyDef fuel_body_def;
	fuel_body_def.type = b2_staticBody;
	fuel_body_def.position = pos;
	// create a connection between the rigid body and GameObject
	fuel_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	fuel_body_ = world->CreateBody(&fuel_body_def);
	
	// create the shape for the fuel
	b2PolygonShape fuel_shape;
	fuel_shape.SetAsBox(3.5f, 2.f, b2Vec2(0.0f, 2.0f), 0);

	// create the fixture
	b2FixtureDef fuel_fixture_def;
	fuel_fixture_def.shape = &fuel_shape;

	fuel_fixture_def.isSensor = true; // doesnt stop the player during collision but still checks for the collision

	// create the fixture on the rigid body
	fuel_body_->CreateFixture(&fuel_fixture_def);

	UpdateFromSimulation(fuel_body_);
}

Fuel::~Fuel()
{
	delete scene_assets_;
	scene_assets_ = NULL;
}

void Fuel::Update(float frame_time)
{


}

void Fuel::Render(gef::Renderer3D* renderer_3d)
{
	renderer_3d->DrawMesh(*this);
}
