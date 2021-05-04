#include "HUD.h"

HUD::HUD(int sw, int sh) {
	camera = new Camera();
	camera->setOrthographic(0, sw, 0, sh, 0.1, 2);
	camera->updateViewMatrix();

	mesh = new Mesh();
	mesh->vertices.resize(4);
	mesh->uvs.resize(4);

	mesh->vertices[0] = Vector3(0, 0, 1);
	mesh->vertices[1] = Vector3(sw, 0, 1);
	mesh->vertices[2] = Vector3(sw, sh, 1);
	mesh->vertices[3] = Vector3(0, sh, 1);

	mesh->uvs[0] = Vector2(0, 0);
	mesh->uvs[1] = Vector2(1, 0);
	mesh->uvs[2] = Vector2(1, 1);
	mesh->uvs[3] = Vector2(0, 1);

	mesh->indices.resize(6);
	mesh->indices[0] = 0;
	mesh->indices[1] = 1;
	mesh->indices[2] = 2;
	mesh->indices[3] = 0;
	mesh->indices[4] = 2;
	mesh->indices[5] = 3;

	mesh->genBuffers();

	shader = new Shader();
	shader->load("data/shaders/hud.vert", "data/shaders/hud.frag");

	

	texture = new Texture();
	texture->load("data/assets/idle_HUD.tga");

	
}

void HUD::render() {
		
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader->enable();
	shader->setMatrix44("u_mvp", camera->viewprojection_matrix);
	shader->setTexture("u_texture_diffuse", texture);
	
	mesh->render(GL_TRIANGLES, shader);
	shader->disable();

}

