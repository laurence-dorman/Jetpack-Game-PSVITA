#include "player.h"
#include "primitive_builder.h"
#include <graphics/renderer_3d.h>
#include "graphics/mesh.h"
#include "system/debug_log.h"

#define INITIAL_POS 0.0f, 9.57f

Player::Player() :
	player_body_(NULL),
	max_speed(10.f),
	scene_assets_(NULL),
	position_(0.f, 0.f),
	thrusting_(false),
	playing_(false),
	fuel_(MAX_FUEL)
{
	rotation_ = 0.f;
	current_rotation_ = 0.f;
}

Player::~Player()
{
	delete scene_assets_;
	scene_assets_ = NULL;

	delete mesh_;
	mesh_ = NULL;
}

void Player::Init(PrimitiveBuilder* primitive_builder, b2World* world, gef::Platform* platform, gef::AudioManager* audio_manager)
{
	audio_manager_ = audio_manager;

	scene_assets_ = new gef::Scene();
	scene_assets_ = model_loader_->LoadSceneAssets(*platform, "models/jetpack/player.scn");

	set_type(PLAYER);

	if (scene_assets_) {
		this->set_mesh(model_loader_->GetMeshFromSceneAssets(scene_assets_));
	}
	else {
		gef::DebugOut("Scene file %s failed to load\n", "models/jetpack/player.scn");
	}


	// create a physics body for the player
	b2BodyDef player_body_def;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position = b2Vec2(INITIAL_POS);
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

void Player::Update(float dt, const gef::SonyController* controller, int difficulty)
{
	if (controller->buttons_down() & gef_SONY_CTRL_SQUARE && fuel_ > 0) {
		thrusting_ = true;
		rotation_ = lerpRotation(controller->left_stick_x_axis() * -MAX_ANGLE, 0.1f);

		rot_vec.Set(-sin(rotation_), cos(rotation_));
		rot_vec *= (ACCELERATION_MODIFIER * dt) / difficulty;

		player_body_->ApplyLinearImpulseToCenter(rot_vec, 1);

		if (!audio_manager_->sample_voice_playing(3)) {
			audio_manager_->PlaySample(3, 1);
		}

		fuel_ -= (dt * difficulty);
		
	}
	else {

		audio_manager_->StopPlayingSampleVoice(3);
		thrusting_ = false;
		rotation_ = lerpRotation(0.f, 0.07f);

	}

	// apply air resistance
	player_body_->ApplyForceToCenter(getAirResistance(player_body_->GetLinearVelocity()), 1);

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
	fuel_ = MAX_FUEL;
	position_.Set(INITIAL_POS);
	player_body_->SetTransform(b2Vec2(INITIAL_POS), 0.f);
}
