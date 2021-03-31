#pragma once
#include <maths/matrix44.h>
#include <maths\math_utils.h>
#include "system/platform.h"

class Camera
{
public:
	Camera(gef::Platform& platform);
	~Camera();

	void Update();

	gef::Matrix44 getProjectionMatrix() { return projection_matrix_; };
	gef::Matrix44 getViewMatrix() { return view_matrix_; };

	void setTarget(gef::Vector4 target) { camera_target_ = target; };
	void setPosition(gef::Vector4 pos) { camera_position_ = pos; };

	float fov_;
	float aspect_ratio_;

private:
	gef::Matrix44 projection_matrix_;
	gef::Matrix44 view_matrix_;

	gef::Platform& platform_;

	gef::Vector4 camera_target_;
	gef::Vector4 camera_position_;
	gef::Vector4 camera_up_;

	

	void SetupCamera();
};

