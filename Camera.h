#pragma once
#include <maths/matrix44.h>
#include <maths\math_utils.h>
#include "system/platform.h"
#include "player.h"

#define Z_OFFSET 65.f

class Camera
{
public:
	Camera(gef::Platform& platform);
	~Camera();

	void Update(float dt);
	void Reset();

	gef::Matrix44 getProjectionMatrix() { return projection_matrix_; };
	gef::Matrix44 getViewMatrix() { return view_matrix_; };

	void setTarget(Player* target) { 
		camera_target_ = target; 
		current_lookat_ = gef::Vector4(target->getPosition().x, target->getPosition().y, 0.f); 
		current_position_ = gef::Vector4(target->getPosition().x, target->getPosition().y, Z_OFFSET);
	};

	void setPosition(gef::Vector4 pos) { camera_position_ = pos; };
	gef::Vector4 getPosition() { return camera_position_; };
	void UpdateTarget(float dt);

	float fov_;
	float aspect_ratio_;

private:
	gef::Matrix44 projection_matrix_;
	gef::Matrix44 view_matrix_;

	gef::Platform& platform_;

	Player* camera_target_;
	gef::Vector4 current_lookat_;
	gef::Vector4 current_position_;
	gef::Vector4 camera_position_;
	gef::Vector4 camera_up_;

	float max_speed;

	void SetupCamera();
};

