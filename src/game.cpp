#include "game.h"

//some globals
float angle = 0;
RenderToTexture* rt = NULL;

Game* Game::instance = NULL;

HUD* hud;

Game::Game(SDL_Window* window)
{
	this->window = window;
	instance = this;

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	SDL_GetWindowSize( window, &window_width, &window_height );
	std::cout << " * Window size: " << window_width << " x " << window_height << std::endl;

	keystate = NULL;
	mouse_locked = false;
}

//Here we have already GL working, so we can create meshes and textures
void Game::init(void)
{

    std::cout << " * Path: " << getPath() << std::endl;
    
    //SDL_SetWindowSize(window, 50,50);

	//create our camera
	camera = new Camera();
	//camera->lookAt(Vector3(0, 25, 25), Vector3(0, 0, 0), Vector3(0, 1, 0)); //position the camera and point to 0,0,0
	//camera->setPerspective(70.0f, (float)window_width / (float)window_height, 0.1f, 10000.0f); //set the projection, we want to be perspective
	
	SceneParser* sp = new SceneParser();
	sp->ParseData("data/scene1.txt");

	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->selectWaypoint();
	}

	hud = new HUD(800, 600);
	Mesh* bullet = new Mesh();
	bullet->loadASE("data/assets/bullet.ASE");
	bullMan = new BulletManager(bullet,30);

	//hide the cursor
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse
}

//what to do when the image has to be draw
void Game::render(void)
{
	bullMan->render();
	bullMan->checkCollision(enemies);

	//set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//update view and projection matrices, and push gl matrices for fixed pipeline rendering
	camera->set();

	for (size_t i = 0; i < skyboxes.size(); i++) {
		skyboxes[i]->render(camera);
	}

	for (size_t i = 0; i < meshes.size(); i++) {
		meshes[i]->render(camera);
	}

	for (size_t i = 0; i < enemies.size(); i++) {
		if (!enemies[i]->dead) {
			enemies[i]->render(camera);
			//enemies[i]->rotateTarget();
		}		
	}

	if (!player[0]->dead) {
		player[0]->render(camera);
	}

	hud->render();

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{
	double speed = seconds_elapsed * 100; //the speed is defined by the seconds_elapsed so it goes constant

	//mouse input to rotate the cam
	if ((mouse_state & SDL_BUTTON_LEFT) || mouse_locked ) //is left button pressed?
	{
		camera->rotate(mouse_delta.x * 0.005f, Vector3(0,-1,0));
		camera->rotate(mouse_delta.y * 0.005f, camera->getLocalVector( Vector3(-1,0,0)));
	}

	//to navigate with the mouse fixed in the middle
	if (mouse_locked)
	{
		int center_x = (int)floor(window_width*0.5f);
		int center_y = (int)floor(window_height*0.5f);
        //center_x = center_y = 50;
		SDL_WarpMouseInWindow(this->window, center_x, center_y); //put the mouse back in the middle of the screen
		//SDL_WarpMouseGlobal(center_x, center_y); //put the mouse back in the middle of the screen
        
        this->mouse_position.x = (float)center_x;
        this->mouse_position.y = (float)center_y;
	}
    
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i]->update(seconds_elapsed);
	}

	// Move player
	//async input to move the camera around
	if (!player[0]->dead) {
		if (keystate[SDL_SCANCODE_LSHIFT]) player[0]->turbo = true; //move faster with left shift
		if (!keystate[SDL_SCANCODE_LSHIFT]) player[0]->turbo = false;
		if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) player[0]->up();
		if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) player[0]->down();
		if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) player[0]->left();
		if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) player[0]->right();
		if (keystate[SDL_SCANCODE_SPACE]) bullMan->createBullet(player[0]->getPos(), player[0]->model.frontVector().normalize(), 20, 150, player[0]);
	}

	Vector3 dest = Vector3(player[0]->getPos().x, player[0]->getPos().y + 50, player[0]->getPos().z + 90);
	Vector3 player_pos = player[0]->getPos();
	Vector3 front = player[0]->model.frontVector().normalize();
	Vector3 upVector = player[0]->model.topVector().normalize();

	//Vector3 look = Vector3(player[0]->getPos().x, player[0]->getPos().y + 50, player[0]->getPos().z + 90);
	Vector3 look = player_pos + (front * 90) + (upVector * 30);

	look = camera->eye.lerp(look, 0.1);

	//3rd Person Camera
	camera->lookAt(
		look,
		player_pos, 
		upVector);
	camera->setPerspective(70.0f, (float)window_width / (float)window_height, 0.1f, 10000.0f); //set the projection, we want to be perspective

	player[0]->update(seconds_elapsed);

	angle += (float)seconds_elapsed * 10;

	//Collision

	GameObjectPlayer* A;
	GameObjectEnemy* B;

	for (int i = 0; i < enemies.size(); i++) {
		A = player[0];
		B = enemies[i];

		A->collision_model->setTransform(A->model.m);
		B->collision_model->setTransform(B->model.m);

		bool collision = A->collision_model->collision(B->collision_model);

		if (collision && !B->dead) {
			player[0]->dead = true;
		}
	}
}

//Keyboard event handler (sync input)
void Game::onKeyPressed( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: exit(0); //ESC key, kill the app
	}
}


void Game::onMouseButton( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
	}
}

void Game::setWindowSize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
    
	/*
    Uint32 flags = SDL_GetWindowFlags(window);
    if(flags & SDL_WINDOW_ALLOW_HIGHDPI)
    {
        width *= 2;
        height *= 2;
    }
	*/

	glViewport( 0,0, width, height );
	camera->aspect =  width / (float)height;
	window_width = width;
	window_height = height;
}

