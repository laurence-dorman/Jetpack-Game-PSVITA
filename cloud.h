#pragma once

#include "graphics/mesh_instance.h"
#include "model_loader.h"
#include "graphics/renderer_3d.h"

class Cloud : public gef::MeshInstance
{
public:
	Cloud(gef::Vector4, int scale, gef::Platform* platform);
	~Cloud();

	void Update(float frame_time);
	void Render(gef::Renderer3D* renderer_3d);
	gef::Vector4 getPosition() { return pos_; };

private:

	ModelLoader* model_loader_;
	gef::Scene* scene_assets_;
	gef::Vector4 pos_;

	int direction_;
	float speed_;
};

