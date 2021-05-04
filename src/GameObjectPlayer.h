#pragma once

#include "GameObjectMesh.h"
#include "includes.h"

class GameObjectPlayer : public GameObjectMesh {
public:

	bool dead = false;
	bool turbo = false;
	Vector3 position;
	Vector3 object_pos;
	CollisionModel3D* collision_model;
	void setCollisionModel();
	void update(float dt);
	Vector3 getPos();
	void up();
	void down();
	void left();
	void right();
};