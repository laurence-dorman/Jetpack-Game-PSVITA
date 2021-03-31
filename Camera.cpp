#include "Camera.h"


Camera::Camera(gef::Platform& platform):
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

void Camera::Update()
{
	view_matrix_.LookAt(camera_position_, camera_target_, camera_up_);
}

void Camera::SetupCamera()
{
	camera_position_ = gef::Vector4(-2.0f, 4.0f, 10.f);
	camera_target_ = gef::Vector4(0.0f, 2.0f, 0.0f);
	camera_up_ = gef::Vector4(0.0f, 1.0f, 0.0f);

	projection_matrix_ = platform_.PerspectiveProjectionFov(fov_, aspect_ratio_, 0.1f, 100.f);
	view_matrix_.LookAt(camera_position_, camera_target_, camera_up_);
}
