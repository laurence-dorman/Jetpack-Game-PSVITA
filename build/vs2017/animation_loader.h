#pragma once
#include "animation/animation.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Mesh;
	class Scene;
	class Skeleton;
	class Platform;
}

class AnimationLoader
{
public:
	gef::Animation* LoadAnimation(const char* anim_scene_filename, const char* anim_name, gef::Platform* platform);
	gef::Skeleton* GetFirstSkeleton(gef::Scene* scene);
	gef::Mesh* GetMesh(gef::Scene* scene, gef::Platform* platform, int i);
};

