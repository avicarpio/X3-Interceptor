#pragma once

#include "includes.h"
#include "camera.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "game.h"
#include "rendertotexture.h"
#include "utils.h"

class HUD {
public:
	HUD(int sw, int sh);
	~HUD();

	Mesh* mesh;
	Camera* camera;

	Shader* shader;

	Texture* texture;

	void render();

};