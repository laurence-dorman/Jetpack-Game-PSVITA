#pragma once
#include "graphics/mesh_instance.h"
#include <maths/quaternion.h>
#include "maths/math_utils.h"

class PrimitiveBuilder;

namespace gef
{
	class Renderer3D;
}


class Player : public gef::MeshInstance
{
public:
	Player(PrimitiveBuilder* primitive_builder);
	~Player();

	void Update(float dt);

	gef::Vector4 getSpeed() { return speed; };
	void setSpeed(gef::Vector4 s) { speed = s; };

	void Init(PrimitiveBuilder* primitive_builder);
	void Render(gef::Renderer3D* renderer_3d);

	void setThrust(float t) { thrust = t; };
	float getThrust() { return thrust; };

	void setPosition(gef::Vector4 pos) { position = pos; };
	gef::Vector4 getPosition() { return position; };

	void setRotation(gef::Quaternion q) { rotation = q; };
	gef::Quaternion getRotation() { return rotation; };

private:

	gef::Vector4 speed;
	float thrust = 0.f;
	const float max_speed = 10.f;

	gef::Quaternion rotation;
	gef::Vector4 position;

	gef::Vector4 heading;

	gef::Matrix44 scale_matrix;
	gef::Matrix44 transl_matrix;
	gef::Matrix44 rotation_matrix_x;
	gef::Matrix44 rotation_matrix_y;
	gef::Matrix44 rotation_matrix_z;
};

