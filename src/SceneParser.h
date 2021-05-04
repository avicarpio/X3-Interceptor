#pragma once

#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include "game.h"
#include "includes.h"
#include "utils.h"
#include <unordered_map>
#include "ParseObject.h"
#include "ParseObjectData.h"
#include "extra/textparser.h"
#include <string>
#include "GameObjectEnemy.h"
#include "GameObjectPlayer.h"

class SceneParser
{
public:
	int n_resources;
	std::vector<ParseObject> resources;
	int n_objects;
	std::vector<ParseObjectData> objects;

	void ParseData(const char* f);
	void loadScene();
	void printInfo();
	char* convert(std::string str);
};

#endif 