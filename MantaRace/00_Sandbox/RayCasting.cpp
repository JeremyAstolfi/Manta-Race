#include "RayCasting.h"


RayCasting::RayCasting()
{
}


RayCasting::~RayCasting()
{
}

//returns a pointer to the intersection point if the ray (from position in direction) collides with the given sphere
//returns nullptr if no intersection
//sphere is the fastest collision check, use as a pretest
vector3* RayCasting::SphereCollision(vector3 position, vector3 direction, vector3 center, float radius){
	
	vector3 dist = position - center; //get the vector between ray's origin and the center of the circle
	//vector3 dir = direction.Normalize();
	float r = radius; 
	float b = glm::dot(dist, direction); //project the distance onto direction
	float c = glm::dot(dist, dist) - r * r;

	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f){
		return nullptr;
	}
	float disc= b*b - c; //find discriminant, 
	//distance's projection in the relevant direction squared minus the difference between distance and radius squared

	// discriminant less than 0 means ray did not pass through sphere
	if (disc < 0.0f){
		return nullptr;
	}

	//FINDING POINT OF INTERSECTION

	// calculate distance ray travels before intersection
	float t = -b - sqrt(disc);

	// negative t means the first possible intersection is before ray's origin,
	//in otherwords: ray originated inside the sphere
	if (t < 0.0f){
		t = 0.0f;
	}
	//distance t in direction added to origin point yields the magical point of intersection
	return &(position + t * direction);
}