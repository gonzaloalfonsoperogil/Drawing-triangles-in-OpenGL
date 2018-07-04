#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "common.h"
#include "../lib/glfw/glfw3.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "../project/Shader.h"
#include "../project/Buffer.h"
#include "../project/Vertex.h"
#include "../project/State.h"
#include "../project/World.h"
#include "../project/Model.h"
#include "../project/Camera.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


std::string readString(const std::string& filename) {
	std::ifstream ifs(filename.c_str(), std::ios_base::binary | std::ios_base::ate);
	std::vector<char> chars(ifs.tellg());
	ifs.seekg(0);
	ifs.read(chars.data(), chars.size());
	return std::string(chars.data(), chars.size());
}
GLFWwindow* win;
int Init()
{ 
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	// initialize opengl extensions
	if ( glewInit() != GLEW_OK ) {
		std::cout << "could not initialize opengl extensions" << std::endl;
		glfwTerminate();
		return -1;
	}
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);

	State::projectionMatrix = glm::mat4();
	std::string vertexShaderSource = readString("data/vertex.glsl");
	std::string fragmentShaderSource = readString("data/fragment.glsl");

	State::defaultShader = Shader::create(vertexShaderSource, fragmentShaderSource);
	
	
}

int main() {
	// init glfw
	Init();

	std::string vertexShaderSource = readString("data/vertex.glsl");
	std::string fragmentShaderSource = readString("data/fragment.glsl");

	std::shared_ptr<Shader> MyShader = Shader::create(vertexShaderSource, fragmentShaderSource);

	std::vector<Vertex> vertices = {
		Vertex(0,  1, 0,  0.9f, 0.3f, 0),
		Vertex(-1, -1, 0,  0.9f, 0.3f, 0),
		Vertex(1, -1, 0,  0.9f, 0.3f, 0),
	};

	std::vector<uint16_t> vertexBuffer = { 0,1,2 };
	std::shared_ptr<Buffer> MyBuffer = std::make_shared<Buffer>(vertices, vertexBuffer);


	std::shared_ptr<Mesh> ptrMesh = std::make_shared<Mesh>();
	ptrMesh->addBuffer(MyBuffer, MyShader);

	World world = World();
	for (int i = 0; i <= 2; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			std::shared_ptr<Model> ptrModel = std::make_shared<Model>(ptrMesh);
			ptrModel->setPosition(glm::vec3(3.0f * i - 3.0f, 0.0f, j));
			ptrModel->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
			world.addEntity(ptrModel);
		}
	}

	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	camera->setClearColor(glm::vec3(0, 0, 0));
	camera->setPosition(glm::vec3(0, 0, 6));
	camera->setRotation(glm::angleAxis(0.0f, glm::vec3(0, 1, 0)));
	camera->setProjection(glm::perspective(glm::radians(60.0f), (SCREEN_WIDTH * 1.0f) / (SCREEN_HEIGHT * 1.0f), 0.1f, 100.0f));
	world.addEntity(camera);
	



	// main loop
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);

		// setup viewport
		glViewport(0, 0, screenWidth, screenHeight);
		glScissor(0, 0, screenWidth, screenHeight);

		// clear screen
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera->setViewport(glm::ivec4(0, 0, screenWidth, screenHeight));
		
		
		world.update(deltaTime);
		world.draw();
		


		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown

	MyShader->~Shader();
	//glDeleteBuffers(1, &vertexBuffer);
	glfwTerminate();
}
