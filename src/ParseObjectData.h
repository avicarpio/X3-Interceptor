#pragma once

#ifndef PARSEOBJECTDATA_H
#define PARSEOBJECTDATA_H


#include "includes.h"
#include <cmath>

class ParseObjectData
{
public:
	char* object;
	char* name;
	char* mesh;
	char* shader;
	char* texture;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	std::vector<Vector3> waypoints;
};

#endif