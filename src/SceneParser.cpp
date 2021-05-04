#include "SceneParser.h"

void SceneParser::ParseData(const char* f) {

	TextParser text;
	ParseObject po;
	ParseObjectData pod;
	if (text.create(f) == false) {
		std::cout << "Error loading assets" << std::endl;
	}
	else {

		text.seek("RESOURCES");
		this->n_resources = text.getint();

		for (int i = 0; i < this->n_resources; i++) {
			std::string type;
			std::string name;
			std::string path;

			text.seek("RESOURCE");
			type = text.getword();
			text.seek("NAME");
			name = text.getword();
			text.seek("PATH");

			if (strcmp(convert(type),"SHADER") == 0) {
				std::string temp = text.getword();
				temp = temp + "-";
				temp = temp + text.getword();
				temp = temp + "-";
				path = temp;
			}else{
				path = text.getword();
			}

			po.type = convert(type);

			po.name = convert(name);

			po.path = convert(path);

			this->resources.push_back(po);
		}

		text.seek("OBJECTS");
		this->n_objects = text.getint();

		for (int i = 0; i < this->n_objects; i++) {

			std::string object;
			std::string name;
			std::string mesh;
			std::string shader;
			std::string texture;

			text.seek("OBJECT");
			object = text.getword();

			text.seek("NAME");
			name = text.getword();

			text.seek("MESH");
			mesh = text.getword();

			text.seek("SHADER");
			shader = text.getword();

			text.seek("TEXTURE");
			texture = text.getword();

			text.seek("POSITION");
			float f1 = text.getfloat();
			float f2 = text.getfloat();
			float f3 = text.getfloat();
			Vector3 pos = Vector3(f1, f2, f3);
			pod.position = pos;

			text.seek("ROTATION");
			f1 = text.getfloat();
			f2 = text.getfloat();
			f3 = text.getfloat();
			Vector3 rot = Vector3(f1, f2, f3);
			pod.rotation = rot;

			text.seek("SCALE");
			f1 = text.getfloat();
			f2 = text.getfloat();
			f3 = text.getfloat();
			Vector3 scale = Vector3(f1, f2, f3);
			pod.scale = scale;

			pod.object = convert(object);
			pod.name = convert(name);
			pod.mesh = convert(mesh);
			pod.shader = convert(shader);
			pod.texture = convert(texture);

			if (strcmp(convert(object), "GAMEOBJECTENEMY") == 0) {
				text.seek("WAYPOINTS");
				int n_waypoints = text.getint();
				for (int i = 0; i < n_waypoints; i++) {
					float wx = text.getfloat();
					float wy = text.getfloat();
					float wz = text.getfloat();
					pod.waypoints.push_back(Vector3(wx, wy, wz));
				}
			}

			

			this->objects.push_back(pod);
		}

		printInfo();

		loadScene();

	}
}

void SceneParser::loadScene() {

	ResourceManager* resource_manager = new ResourceManager();

	char * first_path;
	char * second_path;

	for (int i = 0; i < this->n_resources; i++) {

		int n_case = 0;

		if (strcmp(this->resources[i].type,"MESH") == 0) {
			n_case = 1;
		}

		if (strcmp(this->resources[i].type, "SHADER") == 0) {
			char * temp = strdup(this->resources[i].path);
			char * token = std::strtok(temp, "-");
			first_path = token;
			token = std::strtok(NULL, "-");
			second_path = token;
			n_case = 2;
		}

		if (strcmp(this->resources[i].type, "TEXTURE") == 0) {
			n_case = 3;
		}

		switch(n_case){
			case 1:
				resource_manager->loadMesh(this->resources[i].name, this->resources[i].path);

				break;

			case 2:
				resource_manager->loadShader(this->resources[i].name, first_path, second_path);

				break;

			case 3:
				resource_manager->loadTexture(this->resources[i].name, this->resources[i].path);

				break;

			default:
				std::cout << "Error loading assets (0)" << std::endl;
				
				break;

		}
	}

	GameObjectMesh* new_mesh;
	GameObjectEnvironment* new_mesh2;
	GameObjectEnemy* new_mesh3;
	GameObjectPlayer* new_mesh4;

	for (int i = 0; i < this->objects.size(); i++) {

		int n_case = 0;

		if (strcmp(this->objects[i].object, "GAMEOBJECTMESH") == 0) {
			n_case = 1;
		}

		if (strcmp(this->objects[i].object, "GAMEOBJECTENVIRONMENT") == 0) {
			n_case = 2;
		}

		if (strcmp(this->objects[i].object, "GAMEOBJECTENEMY") == 0) {
			n_case = 3;
		}

		if (strcmp(this->objects[i].object, "GAMEOBJECTPLAYER") == 0) {
			n_case = 4;
		}


		switch (n_case) {
			case 1:
				new_mesh = new GameObjectMesh();
				new_mesh->name = this->objects[i].name;
				new_mesh->mesh = resource_manager->getMesh(this->objects[i].mesh);
				new_mesh->shader = resource_manager->getShader(this->objects[i].shader);
				new_mesh->texture = resource_manager->getTexture(this->objects[i].texture);
				new_mesh->model.traslate(this->objects[i].position.x, this->objects[i].position.y, this->objects[i].position.z);
				new_mesh->model.rotateVector(this->objects[i].rotation);
				new_mesh->model.scale(this->objects[i].scale.x, this->objects[i].scale.y, this->objects[i].scale.z);
				new_mesh->setCollisionModel();
				Game::instance->meshes.push_back(new_mesh);
				break;

			case 2:
				new_mesh2 = new GameObjectEnvironment();
				new_mesh2->name = this->objects[i].name;
				new_mesh2->mesh = resource_manager->getMesh(this->objects[i].mesh);
				new_mesh2->shader = resource_manager->getShader(this->objects[i].shader);
				new_mesh2->texture = resource_manager->getTexture(this->objects[i].texture);
				Game::instance->skyboxes.push_back(new_mesh2);
				break;

			case 3:
				new_mesh3 = new GameObjectEnemy();
				new_mesh3->name = this->objects[i].name;
				new_mesh3->mesh = resource_manager->getMesh(this->objects[i].mesh);
				new_mesh3->shader = resource_manager->getShader(this->objects[i].shader);
				new_mesh3->texture = resource_manager->getTexture(this->objects[i].texture);
				new_mesh3->model.traslate(this->objects[i].position.x, this->objects[i].position.y, this->objects[i].position.z);
				new_mesh3->model.rotateVector(this->objects[i].rotation);
				new_mesh3->model.scale(this->objects[i].scale.x * 3, this->objects[i].scale.y * 3, this->objects[i].scale.z * 3);
				new_mesh3->waypoints = this->objects[i].waypoints;
				new_mesh3->setCollisionModel();
				Game::instance->enemies.push_back(new_mesh3);
				break;

			case 4:
				new_mesh4 = new GameObjectPlayer();
				new_mesh4->name = this->objects[i].name;
				new_mesh4->mesh = resource_manager->getMesh(this->objects[i].mesh);
				new_mesh4->shader = resource_manager->getShader(this->objects[i].shader);
				new_mesh4->texture = resource_manager->getTexture(this->objects[i].texture);
				new_mesh4->model.traslate(this->objects[i].position.x, this->objects[i].position.y, this->objects[i].position.z);
				new_mesh4->model.rotateVector(this->objects[i].rotation);
				new_mesh4->model.scale(this->objects[i].scale.x, this->objects[i].scale.y, this->objects[i].scale.z);
				new_mesh4->setCollisionModel();
				Game::instance->player.push_back(new_mesh4);
				break;

			default:
				std::cout << "Error loading assets (1)" << std::endl;

				break;

		}
	}
	
}

void SceneParser::printInfo() {
	std::cout << "Resources: " << this->n_resources << std::endl;

	for (int i = 0; i < this->n_resources; i++) {
		std::cout << "	Resource: " << this->resources[i].type << std::endl;
		std::cout << "	Name: " << this->resources[i].name << std::endl;
		std::cout << "	Path: " << this->resources[i].path << std::endl;
		std::cout << std::endl;
	}

	std::cout << "Objects: " << this->n_objects << std::endl;

	for (int i = 0; i < this->n_objects; i++) {
		std::cout << "	Object: " << this->objects[i].object << std::endl;
		std::cout << "	Name: " << this->objects[i].name << std::endl;
		std::cout << "	Mesh: " << this->objects[i].mesh << std::endl;
		std::cout << "	Shader: " << this->objects[i].shader << std::endl;
		std::cout << "	Texture: " << this->objects[i].texture << std::endl;
		std::cout << "	Position: " << this->objects[i].position.x << "," << this->objects[i].position.y << "," << this->objects[i].position.z << std::endl;
		std::cout << "	Rotation: " << this->objects[i].rotation.x << "," << this->objects[i].rotation.y << "," << this->objects[i].rotation.z << std::endl;
		std::cout << "	Scale: " << this->objects[i].scale.x << "," << this->objects[i].scale.y << "," << this->objects[i].scale.z << std::endl;
		std::cout << std::endl;

	}
}

char* SceneParser::convert(std::string str) {
	char * aux = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), aux);
	aux[str.size()] = '\0';
	
	return aux;
}