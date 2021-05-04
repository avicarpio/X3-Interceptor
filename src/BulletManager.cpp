#include "BulletManager.h"

BulletManager::BulletManager(Mesh* mesh, int max_bullets) {

	bullet_mesh = mesh;

	bullets_vector.resize(max_bullets);

}

void BulletManager::render() {

	


	for (int i = 0; i < bullets_vector.size(); i++) {
		if (bullets_vector[i].valid) {

			bullets_vector[i].position = bullets_vector[i].position + bullets_vector[i].velocity * -1 * 10;

		}

		if (bullets_vector[i].ttl < 0) {
			bullets_vector[i].valid = false;
		}
		else {
			bullets_vector[i].ttl--;
		}
	}

	if (!can_fire) {
		if (ttf < 0) {
			can_fire = true;
		}
		else {
			ttf--;
		}
	}


}

void BulletManager::createBullet(Vector3 pos, Vector3 vel, float power, float ttl, GameObject* owner) {
	if (can_fire) {
		Bullet b;

		b.valid = true;
		b.position = pos;
		b.velocity = vel;
		b.power = power;
		b.ttl = ttl;
		b.owner = owner;

		for (size_t i = 0; i < bullets_vector.size(); i++) {
			if (!bullets_vector[i].valid) {
				bullets_vector[i] = b;
				break;
			}
		}
		can_fire = false;
		ttf = 30;
	}
	else {
	}
}

void BulletManager::checkCollision(std::vector<GameObjectEnemy*>& colliders) {
	for (size_t i = 0; i < bullets_vector.size(); i++) {
		if (!bullets_vector[i].valid) continue;

		for (size_t j = 0; j < colliders.size(); j++) {
			if (bullets_vector[i].owner == colliders[j]) continue;

			GameObjectEnemy* go = dynamic_cast<GameObjectEnemy*>(colliders[j]);

			go->collision_model->setTransform(go->model.m);

			if (go->collision_model->rayCollision(bullets_vector[i].old_position.v,
												bullets_vector[i].position.v,
												false, 0, 1)) {
				bullets_vector[i].valid = false;

				//Vector3 collision_point;
				//go->collision_model->getCollisionPoint(collision_point.v, true);

				go->onCollideBullet();

				continue;
			}
		}
	}
}