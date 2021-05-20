#pragma once
#include "game_object.h"
#include <graphics/renderer_3d.h>
#include "model_loader.h"

class Fuel : public GameObject
{
public:
	Fuel(b2World* world, b2Vec2 pos, gef::Platform* platform);
	~Fuel();

	void Update(float frame_time);
	void Render(gef::Renderer3D* renderer_3d);

	b2Vec2 getPosition() { return position_; }

private:
	ModelLoader* model_loader_;
	gef::Scene* scene_assets_;

	b2Vec2 position_;

	b2Body* fuel_body_;

	float rotation_;

	b2Vec2 rot_vec;

	float current_rotation_;

};

