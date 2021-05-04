#include "GameObject.h"
#include <algorithm>
#include "camera.h"
#include "game.h"
#include "Scene.h"

Matrix44 GameObject::getGlobalMatrix() {
	if (this->parent)
		return this->parent->getGlobalMatrix() * this->model;
	else
		return this->model;
}

void GameObject::removeChild(GameObject* obj) {
	//moves obj to end of vector
	std::vector<GameObject*>::iterator i = std::remove(this->children.begin(),
		this->children.end(), obj);
	//actually removes it
	this->children.erase(i, this->children.end());
	//deletes the memory associated with obj
	delete (obj);
}

void GameObject::addChild(GameObject* obj) {
	//make this object the parent of the child
	obj->parent = this;
	//add to list
	this->children.push_back(obj);
}

void GameObject::clear() {

}

void GameObject::render() {
	//Camera* camera = scene->camera;
	//Vector3* light_pos = scene.light_pos;
}

void GameObject::update(float dt) {

}


