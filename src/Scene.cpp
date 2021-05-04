#include "Scene.h"

Scene::Scene() {
	this->root = new GameObject();
	light_pos = new Vector3(100, 100, 100);
}
Scene::~Scene() {
	this->root->clear();
	delete this->root;
}
void Scene::render() {
	this->root->render();
}
void Scene::update(float dt) {
	this->root->update(dt);
}