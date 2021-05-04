#include "GameObjectPlayer.h"

void GameObjectPlayer::update(float dt) {

	object_pos = Vector3(
		this->model.m[12],
		this->model.m[13],
		this->model.m[14]);

	if (!dead) {
		if (turbo) {
			this->model.traslate(-front.x *dt * 600, -front.y *dt * 600, -front.z *dt * 600);
		}
		else {
			this->model.traslate(-front.x *dt * 100, -front.y *dt * 100, -front.z *dt * 100);
		}
	}


}

Vector3 GameObjectPlayer::getPos() {
	return object_pos;
}

void GameObjectPlayer::up() {
	this->model.rotateLocal(0.03, Vector3(1, 0, 0));
}

void GameObjectPlayer::down() {
	this->model.rotateLocal(-0.03, Vector3(1, 0, 0));
}

void GameObjectPlayer::left() {
	this->model.rotateLocal(-0.025, Vector3(0, 0, 1));
}

void GameObjectPlayer::right() {
	this->model.rotateLocal(0.025, Vector3(0, 0, 1));
}

void GameObjectPlayer::setCollisionModel() {
	collision_model = newCollisionModel3D();

	collision_model->setTriangleNumber(mesh->indices.size() / 3);

	for (size_t i = 0; i < mesh->indices.size() / 3; i++) {
		Vector3 v1 = mesh->vertices[mesh->indices[i * 3]];
		Vector3 v2 = mesh->vertices[mesh->indices[i * 3 + 1]];
		Vector3 v3 = mesh->vertices[mesh->indices[i * 3 + 2]];

		collision_model->addTriangle(v1.x, v1.y, v1.z,
			v2.x, v2.y, v2.z,
			v3.x, v3.y, v3.z);
	}

	collision_model->finalize();
}