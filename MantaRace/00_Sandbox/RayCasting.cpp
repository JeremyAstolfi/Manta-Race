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
vector3* RayCasting::TriangleCollision(vector3 position, vector3 direction, vector3 p1, vector3 p2, vector3 p3){
	//calculate plane normal and distance using points
	//run plane colision to get point, then test if point is within triangle
	//normal = (p1-p2)x(p1-p3)
	//d = normal.x * (any point, lets say p1).x + n.y * p.y + n.z * p.z
	vector3 norm = glm::cross(p1 - p2, p1 - p3);

	float d = norm.x*p1.x + norm.y*p1.y + norm.z*p1.z;

	//find where ray intersects plane
	vector3* intersection = PlaneCollision(position, direction, norm, d);

	//if ray does not intersect with triangles plane, it can't possibly intersect triangle
	if (intersection != nullptr){

		//determine if point is within triangle
		//attempting "Barycentric Technique"

		//get two sides of the triangle from point 1
		vector3 s1 = p2 - p1;
		vector3 s2 = p3 - p1;
		//line between point 1 and intersection
		vector3 mid = *intersection - p1;

		//find dots for each vector by each vector
		float dot11 = glm::dot(s1, s1);
		float dot12 = glm::dot(s1, s2);
		float dot1m = glm::dot(s1, mid);
		float dot22 = glm::dot(s2, s2);
		float dot2m = glm::dot(s2, mid);

		//the common denominator for two following equations
		float denom = (dot11 * dot22 - dot12 * dot12);
		//projecting mid onto each side
		float ps1 = (dot22 * dot1m - dot12 * dot2m) / denom;
		float ps2 = (dot11 * dot2m - dot12 * dot1m) / denom;
		//these projections repesent how far along the side that point is on a scale of 0 to 1
		//1 being the far corner and 0 being corner 1. a ps greater than 1 is beyond the far corner, and negative is behind corner 1 (both mean out of triangle)
		//basically, if this were a right triangle set on the origin, this would check if mid's x and y fall into the height and width
		//if the sum of these projections is greater than 1, than mid is too long and extends beyond the far side of the triangle
		//if either projection is greater than 1, so will the sum, these don't need to be checked individually
		if (ps1 >= 0 && ps2 >= 0 && ps1 + ps2 < 1){
			//previously found intersection point is within triangle, return it as triangle's intersection point
			return intersection;
		}
	}

	//is ray either does not intersect plane, or does so outside the triangle, return null for no intersection with triangle
	return intersection;
}

//BoxCollision
//call tricollision 12 times?
//create squarecollision and call 6 times?
vector3* RayCasting::BoxCollision(vector3 position, vector3 direction, std::vector<vector3> verts){
	if (verts.size() != 8){ //not a box, ray doesn't collide with a box
		return nullptr;    //I hope to make a more versatile 3d object collision method in the future, but for now box is strictly box
	}

	//test every tri in box, if any return an intersection point return it, no need to keep checking other tris
	//topside
	vector3* triTest= TriangleCollision(position, direction, verts[0], verts[1], verts[2]);
	if (triTest!=nullptr){
		return triTest;
	}
	triTest = TriangleCollision(position, direction, verts[1], verts[2], verts[3]);
	if (triTest != nullptr){
		return triTest;
	}

	//frontside
	triTest = TriangleCollision(position, direction, verts[0], verts[1], verts[6]);
	if (triTest != nullptr){
		return triTest;
	}
	triTest = TriangleCollision(position, direction, verts[1], verts[6], verts[5]);
	if (triTest != nullptr){
		return triTest;
	}

	//leftside
	triTest = TriangleCollision(position, direction, verts[0], verts[3], verts[8]);
	if (triTest != nullptr){
		return triTest;
	}
	triTest = TriangleCollision(position, direction, verts[3], verts[8], verts[5]);
	if (triTest != nullptr){
		return triTest;
	}

	//backside
	triTest = TriangleCollision(position, direction, verts[2], verts[3], verts[8]);
	if (triTest != nullptr){
		return triTest;
	}
	triTest = TriangleCollision(position, direction, verts[3], verts[8], verts[7]);
	if (triTest != nullptr){
		return triTest;
	}

	//rightside
	triTest = TriangleCollision(position, direction, verts[1], verts[2], verts[7]);
	if (triTest != nullptr){
		return triTest;
	}
	triTest = TriangleCollision(position, direction, verts[2], verts[7], verts[6]);
	if (triTest != nullptr){
		return triTest;
	}

	//bottomside
	triTest = TriangleCollision(position, direction, verts[5], verts[6], verts[7]);
	if (triTest != nullptr){
		return triTest;
	}
	triTest = TriangleCollision(position, direction, verts[6], verts[7], verts[8]);
	if (triTest != nullptr){
		return triTest;
	}

	//if no intersection found by now, return null
	return nullptr;

	//I imagine for a box it would be twice as effective to make a QuadCollision method
	//but I think that's the extend of a quadCollision method, tris are more useable for complex objects

	//this is my understanding of raycasting so far,it's possible I will have to change my approach when I make the complex object collision method
}


//conplex object raycast collision
//takes vector of verticies and runs triangle collision many times
//in theory this is how complex collision will work, however I do not currently have sufficient understanding of where the verts vector comes from
//if the verts are being stored in an order that is not linear, the loop will need to be adjusted
vector3* RayCasting::ComplexObjectCollision(vector3 position, vector3 direction, std::vector<vector3> verts){
	if (verts.size() < 3){ //not enough verts for a single tri
		return nullptr;
	}
	//if a point of intersection is found on any tri, return it
	int size = verts.size();
	vector3* triTest;
	for (int v = 0; v < size-2; v++){
		triTest = TriangleCollision(position, direction, verts[v], verts[v+1], verts[v+2]);
		if (triTest != nullptr){
			return triTest;
		}
	}
	//special case, connect final verts back around with initial verts
	triTest = TriangleCollision(position, direction, verts[size-2], verts[size-1], verts[0]);
	if (triTest != nullptr){
		return triTest;
	}
	triTest = TriangleCollision(position, direction, verts[size-1], verts[0], verts[1]);
	if (triTest != nullptr){
		return triTest;
	}

	//no collision, return null
	return nullptr;
}