#pragma once

#ifndef SCENE_H
#define SCENE_H


#include "GameObject.h"
#include "camera.h"

class Scene
{
public:
	Scene();
	~Scene();
	//scene graph starts from here
	GameObject* root;
	//optional - you can choose whether to put the camera in Scene
	//or leave it in game
	Camera* camera;
	//a list of all lights - could be within graph or not
	Vector3* light_pos;
	//standard render and update functions
	void render();
	void update(float);
};

#endif