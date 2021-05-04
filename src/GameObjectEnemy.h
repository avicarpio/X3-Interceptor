#pragma once

#include "GameObjectMesh.h"
#include "includes.h"
#include <ctime>

class GameObjectEnemy : public GameObjectMesh {
public:
	bool dead = false;
	std::vector<Vector3> waypoints;
	Vector3 target;
	Vector3 to_target;
	float angle_rotation;
	Vector3 axis;
	Vector3 rot_axis;
	bool ftime = true;
	CollisionModel3D* collision_model;
	void setCollisionModel();
	void update(float dt);
	void rotateTarget();
	void selectWaypoint();
	void onCollideBullet();
};