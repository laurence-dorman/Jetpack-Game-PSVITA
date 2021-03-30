#include "Player.h"
#include "primitive_builder.h"
#include <graphics/renderer_3d.h>


Player::Player(PrimitiveBuilder* primitive_builder)
{
	Init(primitive_builder);
	speed = gef::Vector4(0.f, 0.f, 0.f, 0.f);
	position = gef::Vector4(0.f, 0.f, 0.f, 0.f);
	heading = gef::Vector4(0.f, 0.f, 0.f, 0.f);

	transl_matrix.SetIdentity();
	scale_matrix.SetIdentity();

	rotation_matrix_x.SetIdentity();
	rotation_matrix_y.SetIdentity();
	rotation_matrix_z.SetIdentity();
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	heading.set_x(sinf(rotation.y));
	heading.set_z(cosf(rotation.y));

	setPosition(getPosition() += heading*dt * thrust * 10);

	transl_matrix.SetTranslation(position);

	rotation_matrix_x.RotationX(rotation.x);
	rotation_matrix_y.RotationY(rotation.y);
	rotation_matrix_z.RotationZ(rotation.z);

	set_transform(scale_matrix * rotation_matrix_x * rotation_matrix_y * rotation_matrix_z * transl_matrix);
}

void Player::Init(PrimitiveBuilder* primitive_builder)
{
	set_mesh(primitive_builder->GetDefaultCubeMesh());
}

void Player::Render(gef::Renderer3D* renderer_3d)
{
	renderer_3d->DrawMesh(*this);
}