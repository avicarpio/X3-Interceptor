#pragma once

#ifndef GAMEOBJECTENVIRONMENT_H
#define GAMEOBJECTENVIRONMENT_H


#include "GameObject.h"
//#include "game.h"
#include "ResourceManager.h"
#include "camera.h"

class GameObjectEnvironment : public GameObject
{
public:
	//Attributes of this class
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Vector3 color;
	float angle = 0;

	//overwritten virtual functions
	void render(Camera* camera);
	void update(float dt);
};

#endif