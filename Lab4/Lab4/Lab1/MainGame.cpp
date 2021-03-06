#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
    Mesh* mesh1();
	Mesh* mesh2();
//	Texture* texture();
	//Audio* audioDevice();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 
	//whistle = audioDevice.loadSound("..\\res\\bang.wav");
	//backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	//texture = Texture("..\\res\\bricks.jpg");
	

	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};
	
	texID = getCubeMap(faces);
	mesh1.loadModel("..\\res\\skull.obj");
	mesh2.loadModel("..\\res\\shirt.obj");
	mesh3.loadModel("..\\res\\cat.obj");
	mesh4.loadModel("..\\res\\sky.obj");
	
	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius());
		//playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		//audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

//void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
//{
//	
//	ALint state; 
//	alGetSourcei(Source, AL_SOURCE_STATE, &state);
//	/*
//	Possible values of state
//	AL_INITIAL
//	AL_STOPPED
//	AL_PLAYING
//	AL_PAUSED
//	*/
//	if (AL_PLAYING != state)
//	{
//		audioDevice.playSound(Source, pos);
//	}
//}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	Shader shader("..\\res\\geo.vert", "..\\res\\geo.frag", "..\\res\\geo.geom"); //new shader
	Shader shader2("..\\res\\shader.vert", "..\\res\\shader.frag",NULL);
	Shader shader3("..\\res\\reflection.vert", "..\\res\\reflection.frag", NULL);
	Shader shader4("..\\res\\sky.vert", "..\\res\\sky.frag", NULL);
	

	//Texture texture("..\\res\\bricks.jpg"); //load texture
	//Texture texture1("..\\res\\water.jpg"); //load texture
	
	//transform.SetPos(glm::vec3(sinf(counter), 0.5, 0.0));
	//transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetPos(glm::vec3(0., 0, 0.));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	myCamera.setPos(glm::vec3(sin(counter)*6.,0.f,cos(counter)*6.));
	shader.Bind();
	shader.Update(transform, myCamera);
	glUniform1f(glGetUniformLocation(shader.getShaderProgram(), "time"),counter);
	//texture.Bind(0);
	mesh1.draw();
	mesh1.updateSphereData(*transform.GetPos(), 0.62f);


	shader2.Bind();
	transform.SetPos(glm::vec3(2., 0, 0.));
	shader2.Update(transform, myCamera);
	glUniform1f(glGetUniformLocation(shader2.getShaderProgram(), "time"), counter);
	//glUniform1f(glGetUniformLocation(shader.getShaderProgram(), "time"), counter);
	//texture.Bind(0);
	mesh2.draw();
	mesh2.updateSphereData(*transform.GetPos(), 0.62f);

	shader3.Bind();
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	transform.SetPos(glm::vec3(-2., 0, 0.));
	shader3.Update(transform, myCamera);

	mesh3.draw();
	mesh3.updateSphereData(*transform.GetPos(), 0.62f);

	shader4.Bind();
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	transform.SetPos(glm::vec3(0., 0, 0.));
	shader4.Update(transform, myCamera);

	mesh4.draw();
	mesh4.updateSphereData(*transform.GetPos(), 0.62f);


	counter = counter + 0.01f;
	

/*
	transform.SetPos(glm::vec3(-sinf(counter), -0.5, -sinf(counter)*5));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh2.draw();
	mesh2.updateSphereData(*transform.GetPos(), 0.62f);
	counter = counter + 0.05f;

	*/			
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 