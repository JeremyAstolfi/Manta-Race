#pragma once

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "BoundingObjectManager.h"
using namespace ReEng;

static class RayCasting
{
public:
	RayCasting();
	~RayCasting();

	static vector3* SphereCollision(vector3 position, vector3 direction, vector3 center, float radius);
};

