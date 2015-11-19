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

	//returns a pointer to a position where a Ray from [position] in [direction] collides with a sphere at [center] with [radius]
	static vector3* SphereCollision(vector3 position, vector3 direction, vector3 center, float radius);

	//returns reference to colliding point between ray from [posiition] in [direction] with plane having [normal] and is [distance] from origin
	static vector3* PlaneCollision(vector3 position, vector3 direction, vector3 normal, float distance);

	//returns a reference to the point of collision between ray from [position] in [direction] with triangle surface spanning points p1-3
	//order of points are most likely relevant to the direction of the normal
	static vector3* TriangleCollision(vector3 position, vector3 direction, vector3 p1, vector3 p2, vector3 p3);

	//determines if ray from [position] in [direction] intersects with box with specified verticies
	//make sure to use sphere collision first, it's much faster
	static vector3* BoxCollision(vector3 position, vector3 direction, std::vector<vector3> verts);
	
	//conplex object raycast collision
	//takes vector of verticies and runs triangle collision many times
	static vector3* ComplexObjectCollision(vector3 position, vector3 direction, std::vector<vector3> verts);
};

