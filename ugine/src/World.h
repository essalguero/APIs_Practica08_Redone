#pragma once

#include "common.h"
#include "Entity.h"
#include "Camera.h"
#include "Light.h"
#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Framebuffer.h"

class World
{
public:
	World();

	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(const std::shared_ptr<Entity>& entity);
	size_t getNumEntities() const;
	const std::shared_ptr<Entity>& getEntity(size_t index) const;
	std::shared_ptr<Entity>& getEntity(size_t index);
	void update(float deltaTime);
	void draw();

	const glm::vec3& getAmbient() const;
	void setAmbient(const glm::vec3& ambient);

	void setShadows(bool enable);
	void setDepthOrtho(float left, float right,
		float bottom, float top, float near, float far);

private:

	glm::vec3 getEulerRotation(glm::vec3 directionVector);

	std::vector<std::shared_ptr<Entity>> entitiesVector;
	std::vector<std::shared_ptr<Camera>> camerasVector;

	glm::vec3 ambientLight;
	std::vector<std::shared_ptr<Light>> lightsVector;

	std::shared_ptr<Camera> depthCamera;

	std::shared_ptr<Shader> depthShader;

	bool castShadows;
	glm::mat4 orthoMatrix;
	float farValue;
};