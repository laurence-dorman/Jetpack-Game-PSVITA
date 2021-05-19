#include "player.h"
#include "primitive_builder.h"
#include <graphics/renderer_3d.h>
#include "graphics/mesh.h"
#include "system/debug_log.h"

Player::Player() :
	player_body_(NULL),
	max_speed(10.f),
	trans_anim_(NULL),
	scene_assets_(NULL),
	position_(0.f, 0.f),
	thrusting_(false),
	playing_(false),
	fuel_(10.f)
{
	rotation_ = 0.f;
	current_rotation_ = 0.f;
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

void Player::Init(PrimitiveBuilder* primitive_builder, b2World* world, gef::Platform* platform, gef::AudioManager* audio_manager)
{
	audio_manager_ = audio_manager;

	audio_manager_->LoadSample("thruster.wav", *platform);

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
	player_body_def.position = b2Vec2(0.0f, 6.0f);
	// create a connection between the rigid body and GameObject
	player_body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	player_body_ = world->CreateBody(&player_body_def);

	// create the shape for the player
	b2PolygonShape player_shape;
	player_shape.SetAsBox(0.4f, 6.3f, b2Vec2(0.0f, -0.75f), 0);
	

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

	gef::DebugOut("FUEL: %.2f\n", fuel_);

	if (controller->buttons_down() & gef_SONY_CTRL_SQUARE && fuel_ > 0) {
		thrusting_ = true;
		rotation_ = lerpRotation(controller->left_stick_x_axis() * -MAX_ANGLE, 0.1f);

		rot_vec.Set(-sin(rotation_), cos(rotation_));
		rot_vec *= ACCELERATION_MODIFIER * dt;

		player_body_->ApplyLinearImpulseToCenter(rot_vec, 1);

		if (!audio_manager_->sample_voice_playing(3)) {
			audio_manager_->PlaySample(3, 1);
		}

		fuel_ -= dt;
		
	}
	else {

		audio_manager_->StopPlayingSampleVoice(3);
		thrusting_ = false;
		rotation_ = lerpRotation(0.f, 0.07f);

	}

	// apply air resistance
	player_body_->ApplyForceToCenter(getAirResistance(player_body_->GetLinearVelocity()), 1);

	//gef::DebugOut("Velocity: (%.1f, %.1f)\n", player_body_->GetLinearVelocity().x, player_body_->GetLinearVelocity().y);
	//gef::DebugOut("Position: (%.1f, %.1f)\n", player_body_->GetPosition().x, player_body_->GetPosition().y);
	//gef::DebugOut("Rotation: %.2f\n", gef::RadToDeg(rotation_));

	player_body_->SetTransform(player_body_->GetPosition(), rotation_);

	gef::Matrix44 player_transform;
	player_transform.SetIdentity();

	player_transform.RotationZ(player_body_->GetAngle());

	player_transform.SetTranslation(gef::Vector4(player_body_->GetPosition().x, player_body_->GetPosition().y, 0.f));

	this->set_transform(player_transform);

	position_ = player_body_->GetPosition();
}

void Player::Render(gef::Renderer3D* renderer_3d)
{
	renderer_3d->DrawMesh(*this);

	//animation stuff(not using for now)
	//if (player_) {
	//	renderer_3d->DrawSkinnedMesh(*player_, player_->bone_matrices());
	//}
		
}

float Player::lerpRotation(float target, float time)
{
	current_rotation_ = gef::Lerp(current_rotation_, target, time);
	return current_rotation_;
}

b2Vec2 Player::getAirResistance(b2Vec2 vel)
{
	b2Vec2 v_sqr;
	v_sqr = player_body_->GetLinearVelocity();
	v_sqr.x *= v_sqr.x;
	v_sqr.y *= v_sqr.y;

	b2Vec2 air_resistance;
	air_resistance.x = 0.5f * v_sqr.x;
	air_resistance.y = 0.5f * v_sqr.y;

	air_resistance.y *= (player_body_->GetLinearVelocity().y > 0) ? -1.f : 0.2f;
	air_resistance.x *= (player_body_->GetLinearVelocity().x > 0) ? -1.f : 1.f;

	return air_resistance;
}

void Player::Reset()
{
	player_body_->SetLinearVelocity(b2Vec2(0.f, 0.f));
	thrusting_ = false;
	playing_ = false;
	rotation_ = 0.f;
	current_rotation_ = 0.f;
	fuel_ = 10.f;
	position_.Set(0.f, 6.f);
	player_body_->SetTransform(b2Vec2(0.0f, 6.0f), 0.f);
}
