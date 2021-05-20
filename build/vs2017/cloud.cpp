#include "cloud.h"
#include "system/debug_log.h"

Cloud::Cloud(gef::Vector4 pos, int scale, gef::Platform* platform) :
	scene_assets_(NULL),
	pos_(pos)
{
	scene_assets_ = new gef::Scene();
	scene_assets_ = model_loader_->LoadSceneAssets(*platform, "models/cloud.scn");

	if (scene_assets_) {
		this->set_mesh(model_loader_->GetMeshFromSceneAssets(scene_assets_));
	}
	else {
		gef::DebugOut("Scene file %s failed to load\n", "models/cloud.scn");
	}

	gef::Matrix44 cloud_transform;
	cloud_transform.SetIdentity();

	cloud_transform.SetTranslation(gef::Vector4(pos.x(), pos.y(), pos.z()));

	gef::Matrix44 scale_matrix;
	gef::Vector4 scale_vec(scale, scale, scale);
	scale_matrix.Scale(scale_vec);

	cloud_transform = cloud_transform * scale_matrix;

	cloud_transform.SetTranslation(pos);

	this->set_transform(cloud_transform);

}

Cloud::~Cloud()
{
}

void Cloud::Update(float frame_time)
{
	
}

void Cloud::Render(gef::Renderer3D* renderer_3d)
{
	renderer_3d->DrawMesh(*this);
}
