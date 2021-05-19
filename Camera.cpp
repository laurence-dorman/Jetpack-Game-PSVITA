#include "camera.h"

Camera::Camera(gef::Platform& platform) :
	platform_(platform),
	fov_(gef::DegToRad(50.0f)),
	aspect_ratio_((float)platform.width() / (float)platform.height())
{
	projection_matrix_.SetZero();
	view_matrix_.SetZero();

	SetupCamera();
}

Camera::~Camera()
{
}

void Camera::Update(float dt)
{
	UpdateTarget(dt);

	view_matrix_.LookAt(camera_position_, current_lookat_, camera_up_);
	
	setPosition(current_position_);
}

void Camera::Reset()
{
	current_lookat_ = gef::Vector4(camera_target_->getPosition().x, camera_target_->getPosition().y + 5.f, 0.f);
	current_position_ = gef::Vector4(camera_target_->getPosition().x, camera_target_->getPosition().y + 5.f, Z_OFFSET);
}

void Camera::UpdateTarget(float dt)
{
	current_lookat_.Lerp(current_lookat_, gef::Vector4(camera_target_->getPosition().x, camera_target_->getPosition().y + 5.f, 0.f), 0.1f);
	current_position_.Lerp(current_position_, gef::Vector4(camera_target_->getPosition().x, camera_target_->getPosition().y + 5.f, Z_OFFSET), 0.1f);
}

void Camera::SetupCamera()
{
	camera_position_ = gef::Vector4(0.0f, 0.0f, Z_OFFSET);
	camera_up_ = gef::Vector4(0.0f, 1.0f, 0.0f);

	projection_matrix_ = platform_.PerspectiveProjectionFov(fov_, aspect_ratio_, 0.1f, 100.f);

}
