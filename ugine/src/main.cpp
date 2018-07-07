/*#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif*/


#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>

#include <memory>


#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "common.h"
#include "Shader.h"
#include "Vertex.h"
#include "Buffer.h"
#include "Mesh.h"
#include "Entity.h"
#include "Model.h"
#include "Camera.h"
#include "World.h"
#include "Texture.h"
#include "Emitter.h"

#include "State.h"


#define FULLSCREEN false

const float ROTATION_SPEED = 0.02f;
const float MOVING_SPEED = 4.0f;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

std::string readString(const char* filename) {
	std::ifstream f(filename, std::ios_base::binary);
	std::stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}


int init() {
	
	// init glew
	if (glewInit()) {
		std::cout << "could not initialize glew" << std::endl;
		return -1;
	}

	// enable gl states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	return 0;

}

void configureEmitter(std::shared_ptr<Emitter>& emitter, glm::vec4 minColorRange, glm::vec4 maxColorRange,
	float minLifetimeRange, float maxLifetimeRange, float minRateRange, float maxRateRange,
	float minScaleRange, float maxScaleRange, glm::vec3 minVelocityRange, glm::vec3 maxVelocityRange,
	float minSpinRange, float maxSpinRange, bool emitting)
{
	emitter->setColorRange(minColorRange, maxColorRange);
	emitter->setLifetimeRange(minLifetimeRange, maxLifetimeRange);
	emitter->setRateRange(minRateRange, maxRateRange);
	emitter->setScaleRange(minScaleRange, maxScaleRange);
	emitter->setVelocityRange(minVelocityRange, maxVelocityRange);
	emitter->setSpinVelocityRange(minSpinRange, maxSpinRange);
	emitter->emit(emitting);
}


int createCube(World & world)
{
	// Crear los Buffers que contiene los datos del cubo. El cubo lo forman dos buffers distintos (se usan una textura distinta en cada Buffer)
	// 1.- Caras laterales
	// 2.- Caras superior e inferion
	vector<Vertex> verticesLaterales;
	vector<uint16_t> indicesLaterales;
	vector<Vertex> verticesTapas;
	vector<uint16_t> indicesTapas;




	Vertex v0{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0, 0) };
	Vertex v1{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1, 0) };
	Vertex v2{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1, 1) };
	Vertex v3{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0, 1) };

	verticesLaterales.push_back(v0);
	verticesLaterales.push_back(v1);
	verticesLaterales.push_back(v2);
	verticesLaterales.push_back(v3);

	indicesLaterales.push_back(0);
	indicesLaterales.push_back(1);
	indicesLaterales.push_back(2);
	indicesLaterales.push_back(2);
	indicesLaterales.push_back(3);
	indicesLaterales.push_back(0);



	Vertex v4{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0, 0) };
	Vertex v5{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1, 0) };
	Vertex v6{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1, 1) };
	Vertex v7{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(0, 1) };

	verticesLaterales.push_back(v4);
	verticesLaterales.push_back(v5);
	verticesLaterales.push_back(v6);
	verticesLaterales.push_back(v7);


	indicesLaterales.push_back(4);
	indicesLaterales.push_back(5);
	indicesLaterales.push_back(6);
	indicesLaterales.push_back(6);
	indicesLaterales.push_back(7);
	indicesLaterales.push_back(4);


	Vertex v8{ glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec2(0, 0) };
	Vertex v9{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(1, 0) };
	Vertex v10{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1, 1) };
	Vertex v11{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0, 1) };

	verticesLaterales.push_back(v8);
	verticesLaterales.push_back(v9);
	verticesLaterales.push_back(v10);
	verticesLaterales.push_back(v11);

	indicesLaterales.push_back(8);
	indicesLaterales.push_back(9);
	indicesLaterales.push_back(10);
	indicesLaterales.push_back(10);
	indicesLaterales.push_back(11);
	indicesLaterales.push_back(8);



	Vertex v12{ glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0, 0) };
	Vertex v13{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1, 0) };
	Vertex v14{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1, 1) };
	Vertex v15{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0, 1) };

	verticesLaterales.push_back(v12);
	verticesLaterales.push_back(v13);
	verticesLaterales.push_back(v14);
	verticesLaterales.push_back(v15);

	indicesLaterales.push_back(12);
	indicesLaterales.push_back(13);
	indicesLaterales.push_back(14);
	indicesLaterales.push_back(14);
	indicesLaterales.push_back(15);
	indicesLaterales.push_back(12);

	//Insert indexes for the top and bottom sides of the cube
	Vertex v20{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0, 0) };
	Vertex v21{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1, 0) };
	Vertex v22{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1, 1) };
	Vertex v23{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0, 1) };

	verticesTapas.push_back(v20);
	verticesTapas.push_back(v21);
	verticesTapas.push_back(v22);
	verticesTapas.push_back(v23);

	indicesTapas.push_back(0);
	indicesTapas.push_back(1);
	indicesTapas.push_back(2);
	indicesTapas.push_back(2);
	indicesTapas.push_back(3);
	indicesTapas.push_back(0);

	Vertex v24{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0, 0) };
	Vertex v25{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1, 0) };
	Vertex v26{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1, 1) };
	Vertex v27{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0, 1) };

	verticesTapas.push_back(v24);
	verticesTapas.push_back(v25);
	verticesTapas.push_back(v26);
	verticesTapas.push_back(v27);

	indicesTapas.push_back(4);
	indicesTapas.push_back(5);
	indicesTapas.push_back(6);
	indicesTapas.push_back(6);
	indicesTapas.push_back(7);
	indicesTapas.push_back(4);

	// Creacion de los Buffers
	shared_ptr<Buffer> bufferDatosLaterales = Buffer::create(verticesLaterales, indicesLaterales);
	if (strcmp(bufferDatosLaterales->getError(), "") != 0)
	{
		cout << bufferDatosLaterales->getError() << endl;
		return 0;
	}

	shared_ptr<Buffer> bufferDatosTapas = Buffer::create(verticesTapas, indicesTapas);
	if (strcmp(bufferDatosTapas->getError(), "") != 0)
	{
		cout << bufferDatosTapas->getError() << endl;
		return 0;
	}

	// Crear un Mesh para el cubo
	shared_ptr<Mesh> cubeMesh = make_shared<Mesh>();

	// Crear un Model para el cubo
	shared_ptr<Model> cube = make_shared<Model>(cubeMesh);

	// Carga Material para caras laterales
	//Material materialFront = Material::Material(Texture::load("data/front.png"), nullptr);
	Material materialFront;
	// Carga Material para caras Superior e Inferior
	Material materialTop = Material::Material(Texture::load("data/top.png"), nullptr);

	// Añadir el Buffer que contiene los datos de las caras laterales al Mesh del cubo
	cubeMesh->addBuffer(bufferDatosLaterales, materialFront);
	// Añadir el Buffer que contiene los datos de las caras laterales al Mesh del cubo
	cubeMesh->addBuffer(bufferDatosTapas, materialTop);

	glm::vec3 scaleVector(1.0f, 1.0f, 1.0f);
	glm::vec3 rotationVector(0.0f, 0.0f, 0.0f);


	cube->setScale(scaleVector);
	cube->setRotation(rotationVector);
	cube->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	//Add the cube to the world object
	world.addEntity(cube);


	return 1;
}

// This method creates all the models and add them to the world
int createModelsInWorld(World & world, std::vector<Emitter>& emittersVector)
{
	// Load skybox model from file
	std::shared_ptr<Mesh>sceneMesh = Mesh::load("data/scene.msh.xml");

	if (sceneMesh == nullptr)
		return 0;

	// Create model
	shared_ptr<Model> sceneModel = make_shared<Model>(sceneMesh);
	//skyboxModel->setScale(vec3(20.0f, 20.0f, 20.0f));
	sceneModel->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//skyboxMesh->getMaterial(0).setLighting(false);

	// Add model
	world.addEntity(sceneModel);


	world.setShadows(true);
	world.setDepthOrtho(-10, 10, -10, 10, 1, 100);


	//createCube(world);
	// Set Lighting
	world.setAmbient(glm::vec3(0.3, 0.3, 0.3));
	//Light(glm::vec3 position, Type type, glm::vec3 color, float linearAttenuation, glm::vec3 direction)
	std::shared_ptr<Light>directionalLight = std::make_shared<Light>(vec3(1.0f, 0.0f, 0.0f), Light::Type::DIRECTIONAL,
		glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0, 0, 0));


	directionalLight->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	directionalLight->setRotation(glm::vec3(-30.0f, 0.0f, 0.0f));
	//directionalLight->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	directionalLight->move(glm::vec3(0.0f, 0.0f, -1.0f));

	world.addEntity(directionalLight);

 	return 1;
}


int main(int, char**) {

	//Camera rotation is update in every frame
	float angle = 0.0f;

	std::vector<Emitter> emittersVector;
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "could not initalize glfw" << std::endl;
		return -1;
	}
	atexit(glfwTerminate);

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "U-gine", FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (!window) {
		std::cout << "could not create glfw window" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (init())
		return -1;


	// Store the Shader in the global object State
	State::defaultShader = Shader::create(readString("data/shader.vert"), readString("data/shader.frag"));

	// If there  was any error on the generation of the sharder, raise an error
	if (strcmp(State::defaultShader->getError(), "") != 0)
	{
	cout << State::defaultShader->getError() << endl;
		return -1;
	}

	// Generate the world
	World world;

	// Generate a camera and store it in the world
	shared_ptr<Camera> camera = make_shared<Camera>();
	camera->setPosition(glm::vec3(0.0f, 8.0f, -12.0f));
	camera->setRotation(glm::vec3(-30.0f, 180.0f, 0.0f));
	camera->setClearColor(glm::vec3(0.0f, 0.0f, 0.0f));
	world.addEntity(camera);

	// Generate the objects in the world
	if (!createModelsInWorld(world, emittersVector))
	{
		cout << "Error creating the Model objects in the world" << endl;
		return -1;
	}

	double xPrev;
	double yPrev;

	glfwGetCursorPos(window, &xPrev, &yPrev);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Bucle principal
	float lastTime = static_cast<float>(glfwGetTime());
	while ( !glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) ) {

		// update delta time
		float newTime = static_cast<float>(glfwGetTime());
		float deltaTime = newTime - lastTime;
		lastTime = newTime;


		// Check key status
		if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP))
		{
			camera->move(vec3(0.0f, 0.0f, -MOVING_SPEED) * deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN))
		{
			camera->move(vec3(0.0f, 0.0f, MOVING_SPEED) * deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT))
		{
			camera->move(vec3(-MOVING_SPEED, 0.0f, 0.0f) * deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT))
		{
			camera->move(vec3(MOVING_SPEED, 0.0f, 0.0f) * deltaTime);
		}

		double xCurrent, yCurrent;

		//Check mouse position
		glfwGetCursorPos(window, &xCurrent, &yCurrent);

		glm::vec3 newRotation = glm::vec3((yPrev - yCurrent), (xPrev - xCurrent), 0.0f) * ROTATION_SPEED;
		glm::vec3 currentRot = camera->getRotation();
		camera->setRotation((currentRot + newRotation));
		yPrev = yCurrent;
		xPrev = xCurrent;
		

		// get updated screen size
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);

		// report screen size
		std::stringstream ss;
		ss << screenWidth << "x" << screenHeight;
		glfwSetWindowTitle(window, ss.str().c_str());

		// Update viewport in case the screen has been resized
		camera->setViewport(glm::ivec4(0, 0, screenWidth, screenHeight));

		//light rotation
		//deltaTime = 0.003;
		shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(world.getEntity(world.getNumEntities() - 1)); //->setPosition(camera->getPosition());
		angle += 32 * deltaTime;

		//shared_ptr<Model> cube = std::dynamic_pointer_cast<Model>(world.getEntity(world.getNumEntities() - 2));

		light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		glm::vec3 currentRotation = light->getRotation();
		currentRotation.y = angle + 180;
		light->setRotation(currentRotation);
		light->move(glm::vec3(0.0f, 0.0f, 1.0f));


		/*light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		light->setRotation(glm::vec3(0, 180, 0));
		light->move(glm::vec3(0, 0, 1));*/

		/*glm::quat rot = glm::rotate(glm::quat(), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		rot = glm::rotate(rot, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		light->setRotationQuat(rot);
		light->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		light->move(glm::vec3(0.0f, 0.0f, 1.0f));*/
		//light->setRotationQuat(rot);

		//cube->setPosition(light->getPosition());
		//cube->setRotation(light->getRotation());

		//light->move(glm::vec3(0.0f, 0.0f, 1.0f));

		std::cout << light->getPosition().x << ", " << light->getPosition().y << ", " << light->getPosition().z << std::endl;
		//std::cout << light->getRotation().x << ", " << light->getRotation().y << ", " << light->getRotation().z << std::endl;

		// Set projection matrix in case the screen has been resized
		glm::mat4 projectionMatrix = glm::perspective(45.0f,
			static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 100.0f);
		camera->setProjection(projectionMatrix);

		
		// Draw the objects
		world.update(deltaTime);
		world.draw();

		// update swap chain & process events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	return 0;
}