#include "Player.h"
#include "primitive_builder.h"
#include <graphics/renderer_3d.h>

Player::Player() :
	player_body_(NULL),
	max_speed(10.f),
	trans_anim_(NULL),
	scene_assets_(NULL)
{
	speed = b2Vec2(0.0f, 0.0f);
	position = b2Vec2(0.0f, 4.0f);
	heading = b2Vec2(0.f, 0.f);
	timer = 0.f;
	rotation_ = 0.f;
}

Player::~Player()
{
	delete scene_assets_;
	scene_assets_ = NULL;

	delete player_;
	player_ = NULL;

	delete mesh_;
	mesh_ = NULL;
}

void Player::Init(PrimitiveBuilder* primitive_builder, b2World* world, gef::Platform* platform)
{
	scene_assets_ = new gef::Scene();
	scene_assets_ = model_loader_->LoadSceneAssets(*platform, "models/jetpack/player.scn");

	/* animation stuff (not using for now)
	//if (scene_assets_)
	//{
	//	//player_mesh_.set_mesh(model_loader_->GetMeshFromSceneAssets(scene_assets_));
	//}
	//else
	//{
	//	//gef::DebugOut("Scene file %s failed to load\n", "models/jetpack/player.scn");
	//}

	//scene_assets_->CreateMaterials(*platform);

	//mesh_ = animation_loader_->GetMesh(scene_assets_, platform, 0);

	//gef::Skeleton* skeleton = animation_loader_->GetFirstSkeleton(scene_assets_);

	//if (skeleton) {
	//	player_ = new gef::SkinnedMeshInstance(*skeleton);
	//	anim_player_.Init(player_->bind_pose());
	//	player_->set_mesh(mesh_);
	//	// setup the mesh for the player
	//	//this->set_mesh(player_->mesh());
	//}
	*/

	if (scene_assets_) {
		this->set_mesh(model_loader_->GetMeshFromSceneAssets(scene_assets_));
	}
	else {
		gef::DebugOut("Scene file %s failed to load\n", "models/jetpack/player.scn");
	}

	/* animation stuff (not using for now)
	//trans_anim_ = animation_loader_->LoadAnimation("models/player/player@transition.scn", "", platform);

	//if (trans_anim_) {
	//	anim_player_.set_clip(trans_anim_);
	//	anim_player_.set_looping(true);
	//	anim_player_.set_anim_time(0.0f);
	//}
	*/

	// create a physics body for the player
	b2BodyDef player_body_def;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position = b2Vec2(0.0f, 0.0f);
	// create a connection between the rigid body and GameObject
	player_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	player_body_ = world->CreateBody(&player_body_def);

	// create the shape for the player
	b2PolygonShape player_shape;
	player_shape.SetAsBox(0.4f, 6.0f, b2Vec2(0.0f, 6.f), 0);

	//player_shape.Set(player_mesh_.mesh(), player_mesh_.mesh());

	// create the fixture
	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;
	player_fixture_def.friction = 0.5f;

	// create the fixture on the rigid body
	player_body_->CreateFixture(&player_fixture_def);
}

void Player::Update(float dt, const gef::SonyController* controller)
{
	// animation stuff (not using for now)
	//if (player_) {
	//	anim_player_.Update(dt, player_->bind_pose());
	//
	//	player_->UpdateBoneMatrices(anim_player_.pose());
	//

	//if (player_)
	//{
	//	gef::Matrix44 player_transform;
	//	player_transform.SetIdentity();
	//	player_->set_transform(player_transform);
	//}


	if (controller->buttons_down() & gef_SONY_CTRL_SQUARE) {
		rotation_ = clamp((rotation_ + gef::DegToRad(controller->left_stick_x_axis() * -2.f)), gef::DegToRad(-45.f), gef::DegToRad(45.f));
		rot_vec.Set(-sin(rotation_), cos(rotation_));
		rot_vec *= 10;

		player_body_->ApplyLinearImpulseToCenter(rot_vec, 1);

		timer = 0.f;
	}
	else {
		if (timer < 1 && std::abs(rotation_ - 0.f) >= 0.01f) {
			rotation_ = gef::Lerp(rotation_, 0.f, timer);
			timer += dt*0.3;
		}
		else {
			timer = 0.f;
			rotation_ = 0.f;
		}
	}

	//gef::DebugOut("Rotation: %.2f\n", gef::RadToDeg(rotation_));

	gef::DebugOut("Velocity: (%.1f, %.1f)\n", player_body_->GetLinearVelocity().x, player_body_->GetLinearVelocity().y);

	b2Vec2 vel = player_body_->GetLinearVelocity();
	float speed = vel.Normalize();

	//gef::DebugOut("Speed: %.2f\n", speed);

	if (player_body_->GetLinearVelocity().y > max_speed && controller->buttons_down() & gef_SONY_CTRL_SQUARE) {
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

void Player::Render(gef::Renderer3D* renderer_3d)
{
	renderer_3d->DrawMesh(*this);

	//animation stuff(not using for now)
	//if (player_) {
	//	renderer_3d->DrawSkinnedMesh(*player_, player_->bone_matrices());
	//}
		
}

float Player::clamp(const float v, const float lo, const float hi)
{
	assert(!(hi < lo));
	return (v < lo) ? lo : (hi < v) ? hi : v;
}
