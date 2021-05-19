#pragma once

#include "graphics/scene.h"

class ModelLoader
{
public:

	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

};

