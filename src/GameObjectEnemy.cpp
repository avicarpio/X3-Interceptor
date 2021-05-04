#include "GameObjectEnemy.h"

void GameObjectEnemy::update(float dt) {
	if (this->name != "STATION") {

		Vector3 object_pos(
			this->model.m[12],
			this->model.m[13],
			this->model.m[14]);

		if ((abs(object_pos.x - target.x) >= 5 || abs(object_pos.y - target.y) >= 5 || abs(object_pos.z - target.z) >= 5)) {
			this->model.traslate(-front.x *dt * 50, -front.y *dt * 50, -front.z *dt * 50);
			rotateTarget();
		}
		else {
			selectWaypoint();
			std::cout << this->name << std::endl;
			std::cout << "NEW WAYPOINT: " << target.x << "," << target.y << "," << target.z << std::endl;
		}
	}

}

void GameObjectEnemy::rotateTarget() {

	Vector3 object_pos(
		this->model.m[12],
		this->model.m[13],
		this->model.m[14]);

	to_target = (target - object_pos).normalize();
	Vector3 real_front = this->model.frontVector().normalize();

	angle_rotation = 3.14159265359 - acos(to_target.dot(real_front));
	axis = to_target.cross(real_front);

	Matrix44 inv = this->model;
	inv.inverse();
	rot_axis = inv.rotateVector(axis);

	if (angle_rotation > 0.1)
		this->model.rotateLocal(-0.04, rot_axis);
}

void GameObjectEnemy::selectWaypoint() {

	srand(time(NULL));
	rand() % waypoints.size();
	target = waypoints[rand() % waypoints.size()];

}

void GameObjectEnemy::setCollisionModel() {
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

void GameObjectEnemy::onCollideBullet() {

	this->dead = true;

}