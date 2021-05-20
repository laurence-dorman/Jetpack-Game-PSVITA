#include "cloud.h"
#include "system/debug_log.h"

Cloud::Cloud(gef::Vector4 pos, int scale, gef::Platform* platform) :
	scene_assets_(NULL),
	pos_(pos),
	speed_(0.5f)
{

	scene_assets_ = new gef::Scene();
	scene_assets_ = model_loader_->LoadSceneAssets(*platform, "models/cloud.scn");

	if (scene_assets_) {
		this->set_mesh(model_loader_->GetMeshFromSceneAssets(scene_assets_));
	}
	else {
		gef::DebugOut("Scene file %s failed to load\n", "models/cloud.scn");
	}
	// generate random movement direction (-1 or 1)
	direction_ = ((rand() % 2 + 1) == 1 ? 1 : -1);


	gef::Matrix44 cloud_transform;
	cloud_transform.SetIdentity();

	cloud_transform.SetTranslation(gef::Vector4(pos.x(), pos.y(), pos.z())); // translate to pos

	gef::Matrix44 scale_matrix;
	gef::Vector4 scale_vec(scale, scale, scale); // scale by scale
	scale_matrix.Scale(scale_vec);

	cloud_transform = cloud_transform * scale_matrix;

	cloud_transform.SetTranslation(pos); // translate back to pos

	this->set_transform(cloud_transform);

}

Cloud::~Cloud()
{
	delete scene_assets_;
	scene_assets_ = NULL;
}

void Cloud::Update(float frame_time)
{
	gef::Matrix44 cloud_transform;
	cloud_transform.SetIdentity();
	cloud_transform.SetTranslation(gef::Vector4(direction_ * frame_time * speed_, 0.f , 0.f)); // move in direction

	pos_ = this->transform().GetTranslation();

	cloud_transform = cloud_transform * this->transform();
	
	this->set_transform(cloud_transform);
}

void Cloud::Render(gef::Renderer3D* renderer_3d)
{
	renderer_3d->DrawMesh(*this);
}
