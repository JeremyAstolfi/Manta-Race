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
	float c = glm::dot(dist, dist) - r * r; //distance squared - radius squared

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

vector3* RayCasting::PlaneCollision(vector3 position, vector3 direction, vector3 center, float radius){
	return &vector3(0.0f);
}
//returns reference to colliding point between ray from [posiition] in [direction] with plane having [normal] and is [distance] from origin
vector3* RayCasting::PlaneCollision(vector3 position, vector3 direction, vector3 normal, float distance){
	//P = P0 + tV
	//point of intersection if position plus (direction scaled to length t)
	//t is -(P0 * N + d)/( V * N )
	//thats negative of (position  projected onto normal plus distance) divided by direction projected onto normal
	
	//formula for a plain: ax + by + cz + d = 0
	//<abc> is noraml, <xyz> is desired point, d is distance from point 0
	//distance should be equal to ( postion.x *normal.x plus that for y and for z) plus d
	float dist = (position.x*normal.x + position.y*normal.y + position.z * normal.z) + distance;

	//project direction onto normal
	float dot1 = glm::dot(direction, normal);
	//determine if ray is parallel to plane
	if (dot1 == 0){
		return nullptr;
	}

	//how far ray travels before collision
	float d = (( glm::dot(position,normal) + dist) / dot1);

	if (d < 0){ //d is negative, plane exists behind ray
		return nullptr;
	}

	//return point of collision
	return &(position + direction*d);
}

//returns a reference to the point of collision between ray from [position] in [direction] with triangle surface spanning points p1-3
//order of points are most likely relevant to the direction of the normal
//vector3* RayCasting::TriangleCollision(vector3 position, vector3 direction, vector3 p1, vector3 p2, vector3 p3){
	//calculate plane normal and distance using points
	//run plane colision to get point, then test if point is within triangle
	//return nullptr;
//}
vector3* RayCasting::PlaneCollision(vector3 position, vector3 direction, vector3 center, float radius){
	return &vector3(0.0f);
}