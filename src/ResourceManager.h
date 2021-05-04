#pragma once
#ifndef RES_MAN_H
#define RES_MAN_H
#include <unordered_map>
#include "mesh.h"
#include "texture.h"
#include "shader.h"

class ResourceManager
{
private:
	//maps for storing handles to pointers to asset objects
	std::unordered_map<std::string, Mesh*> m_meshes;
	std::unordered_map<std::string, Texture*> m_textures;
	std::unordered_map<std::string, Shader*> m_shaders;
	//more lists (audio etc.) will go here later
	
public:
	//unused constructor and destructor
	ResourceManager();
	~ResourceManager();
	void loadMesh(const std::string, const std::string);
	void loadTexture(const std::string, const std::string);
	void loadShader(const std::string, const std::string, const std::string);
	Mesh* getMesh(const std::string);
	Texture* getTexture(const std::string);
	Shader* getShader(const std::string);
};

#endif