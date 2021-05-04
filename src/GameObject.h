#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "framework.h"
#include "includes.h"

class GameObject
{
public:
	//modificar constructor de gameobject poara decir
	//parent = NULL;
	Matrix44 model;
	std::string name;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	//...
	void addChild(GameObject* obj);
	void removeChild(GameObject* obj);
	void clear();//you implement this!
	Matrix44 getGlobalMatrix(); //returns transform in world coordinates
	void render();
	void update(float dt);
};

#endif