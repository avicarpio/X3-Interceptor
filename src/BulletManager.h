#pragma once

#include "framework.h"
#include "GameObject.h"
#include "mesh.h"
#include "shader.h"
#include "GameObjectMesh.h"
#include "GameObjectEnemy.h"

struct Bullet {
	bool valid;
	Vector3 position;
	Vector3 old_position;
	Vector3 velocity;
	float ttl;
	float power;
	GameObject* owner;
};

class BulletManager {
public:

	Mesh* bullet_mesh;
	std::vector<Bullet> bullets_vector;
	Shader* shader;
	bool can_fire = true;
	int ttf;

	BulletManager(Mesh* theMesh, int max_bullets);

	void render();
	void update(float elapsed_time);
	void createBullet(Vector3 pos, Vector3 vel, float power, float ttl, GameObject* owner);
	void checkCollision(std::vector<GameObjectEnemy*>& colliders);
};