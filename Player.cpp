#include "Player.h"
#include "primitive_builder.h"
#include <graphics/renderer_3d.h>

Player::Player() :
	player_body_(NULL),
	max_speed(10.f)
{
	speed = b2Vec2(0.0f, 0.0f);
	position = b2Vec2(0.0f, 4.0f);
	heading = b2Vec2(0.f, 0.f);
}

Player::~Player()
{
}

void Player::Update(float dt, const gef::SonyController* controller)
{
	//if (player_body_->GetLinearVelocity().y > 0.05 || player_body_->GetLinearVelocity().y < -0.05) {
	//	rotation = gef::DegToRad(controller->left_stick_x_axis() * -60.f);
	//	rot_vec.Set(-sin(rotation), cos(rotation));
	//	rot_vec *= 20;
	//}
	//else {
	//	rotation = gef::DegToRad(0.f);
	//	rot_vec.Set(-sin(rotation), cos(rotation));
	//	rot_vec *= 20;
	//}



	if (controller->left_stick_x_axis() != 0.f) {
		player_body_->SetAwake(true);
	}

	if (controller->buttons_down() & gef_SONY_CTRL_SQUARE) {
		rotation_ = gef::DegToRad(controller->left_stick_x_axis() * -60.f);
		rot_vec.Set(-sin(rotation_), cos(rotation_));
		rot_vec *= 20;

		player_body_->ApplyLinearImpulseToCenter(rot_vec, 1);
	}
	else
	{
		rotation_ = gef::DegToRad(0.f);
		rot_vec.Set(-sin(rotation_), cos(rotation_));
		rot_vec *= 20;
	}

	gef::DebugOut("Velocity: (%.1f, %.1f)\n", player_body_->GetLinearVelocity().x, player_body_->GetLinearVelocity().y);

	b2Vec2 vel = player_body_->GetLinearVelocity();
	float speed = vel.Normalize();

	if (speed > max_speed && controller->buttons_down() & gef_SONY_CTRL_SQUARE) {
		player_body_->SetLinearVelocity(max_speed * vel);
	}

	player_body_->SetTransform(player_body_->GetPosition(), rotation_);

	gef::Matrix44 player_transform;
	player_transform.SetIdentity();
	player_transform.RotationZ(player_body_->GetAngle());
	player_transform.SetTranslation(gef::Vector4(player_body_->GetPosition().x, player_body_->GetPosition().y, 0.f));
	this->set_transform(player_transform);

	position.Set(player_body_->GetPosition().x, player_body_->GetPosition().y);
}

void Player::Init(PrimitiveBuilder* primitive_builder, b2World* world, gef::Platform* platform)
{
	scene_assets_ = model_loader_->LoadSceneAssets(*platform, "models/jetpack/player.scn");

	if (scene_assets_)
	{
		player_mesh_.set_mesh(model_loader_->GetMeshFromSceneAssets(scene_assets_));
	}
	else
	{
		gef::DebugOut("Scene file %s failed to load\n", "models/jetpack/player.scn");
	}

	// setup the mesh for the player
	this->set_mesh(player_mesh_.mesh());

	// create a physics body for the player
	b2BodyDef player_body_def;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position = b2Vec2(0.0f, 4.0f);
	// create a connection between the rigid body and GameObject
	player_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	player_body_ = world->CreateBody(&player_body_def);

	// create the shape for the player
	b2PolygonShape player_shape;
	player_shape.SetAsBox(1.5f, 7.0f, b2Vec2(0.0f, 7.0f), 0);

	//player_shape.Set(player_mesh_.mesh(), player_mesh_.mesh());

	// create the fixture
	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;

	// create the fixture on the rigid body
	player_body_->CreateFixture(&player_fixture_def);
}

void Player::Render(gef::Renderer3D* renderer_3d)
{
	renderer_3d->DrawMesh(*this);
}