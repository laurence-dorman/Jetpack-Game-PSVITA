#include "Camera.h"


Camera::Camera(gef::Platform& platform):
	platform_(platform)
{
	projection_matrix_.SetZero();
	view_matrix_.SetZero();

	SetupCamera();
}

Camera::~Camera()
{
}

void Camera::SetupCamera()
{
	camera_position_ = gef::Vector4(5.0f, 5.0f, -5.0f);
	camera_target_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	camera_up_ = gef::Vector4(0.0f, 1.0f, 0.0f);

	projection_matrix_ = platform_.PerspectiveProjectionFov(gef::DegToRad(60.f), platform_.width() / platform_.height(), 0.1f, 10.f);
	view_matrix_.LookAt(camera_position_, camera_target_, camera_up_);
}
