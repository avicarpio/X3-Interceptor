#include "ResourceManager.h"

ResourceManager::ResourceManager() {

}

//load a mesh into memory, and associate it with a handle
void ResourceManager::loadMesh(const std::string handle,
	const std::string path)
{
	Mesh *mesh = new Mesh();
	mesh->loadASE(path.c_str());
	m_meshes[handle] = mesh;
}//load a texture into memory, and associate it with a handle
void ResourceManager::loadTexture(const std::string handle,
	const std::string path)
{
	Texture *texture = new Texture();
	texture->load(path.c_str());
	m_textures[handle] = texture;
}//load a shader into memory, and associate it with a handle
void ResourceManager::loadShader(const std::string handle,
	const std::string path_vertex, const std::string path_frag)
{
	Shader *shader = new Shader();
	if (!shader->load(path_vertex, path_frag))
	{
		std::cout << "shader not found or error" << std::endl;
		exit(0);
	}
	m_shaders[handle] = shader;
}

Mesh* ResourceManager::getMesh(const std::string name) {
	return m_meshes.at(name);
}

Texture* ResourceManager::getTexture(const std::string name) {
	return m_textures.at(name);
}

Shader* ResourceManager::getShader(const std::string name) {
	return m_shaders.at(name);
}