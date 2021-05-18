#pragma once
#include "graphics/mesh_instance.h"
#include <maths/quaternion.h>
#include "maths/math_utils.h"
#include <input/sony_controller_input_manager.h>
#include <box2d/Box2D.h>
#include "model_loader.h"
#include <system/debug_log.h>
#include <animation/skeleton.h>
#include <graphics/skinned_mesh_instance.h>
#include "motion_clip_player.h"
#include "animation_loader.h"
#include "utilities.h"
#include <audio/audio_manager.h>

#define ACCELERATION_MODIFIER 200.f
#define MAX_ANGLE 1.047198f // 60 degrees in rad

class PrimitiveBuilder;

namespace gef
{
	class Renderer3D;
}


class Player : public gef::MeshInstance
{
public:
	Player();
	~Player();

	void Update(float dt, const gef::SonyController* controller);

	void Init(PrimitiveBuilder* primitive_builder, b2World* world, gef::Platform* platform, gef::AudioManager* audio_manager);
	void Render(gef::Renderer3D* renderer_3d);

	void setThrust(float t) { thrust = t; };
	float getThrust() { return thrust; };

	void setPosition(b2Vec2 pos) { position_ = pos; };
	b2Vec2 getPosition() { return position_; };

	float lerpRotation(float target, float time);

	b2Vec2 getAirResistance(b2Vec2 vel);

	bool isThrusting() { return thrusting_; };

private:
	float thrust = 0.f;
	const float max_speed = 10.f;

	b2Vec2 position_;

	b2Body* player_body_;

	ModelLoader* model_loader_;

	//gef::MeshInstance player_mesh_;
	gef::Scene* scene_assets_;

	float rotation_;

	b2Vec2 rot_vec;

	float current_rotation_;

	gef::SkinnedMeshInstance* player_;

	MotionClipPlayer anim_player_;
	gef::Animation* trans_anim_;

	AnimationLoader* animation_loader_;

	gef::AudioManager* audio_manager_;

	bool thrusting_;

	bool playing_;

};

