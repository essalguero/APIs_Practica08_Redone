#include "Light.h"
#include "State.h"

#include <string>

Light::Type Light::getType() const
{
	return lightType;
}

void Light::setType(Light::Type type)
{
	lightType = type;
}

const glm::vec3& Light::getColor() const
{
	return lightColor;
}

void Light::setColor(const glm::vec3& color)
{
	lightColor = color;
}

float Light::getLinearAttenuation() const
{
	return linearAttenuation;
}

void Light::setLinearAttenuation(float att)
{
	linearAttenuation = att;
}

void Light::prepare(int index, std::shared_ptr<Shader>& shader) const
{

	std::string indexString = std::to_string(index);
	std::string variableName = "lights[" + indexString + "].lightVector";

	int location;

	if (lightType == Type::POINT)
	{
		// Pass the position in observer space
		glm::vec4 positionForShader;
		/*positionForShader = glm::vec4(1, 1, 1, lightType);
		positionForShader = glm::rotate(glm::translate(glm::mat4(), position), glm::angle(rotationQuat),
			glm::axis(rotationQuat)) * positionForShader;*/
		positionForShader = State::viewMatrix * glm::vec4(position, 1);
		location = shader->getLocation(variableName.c_str());
		shader->setVec4(location, positionForShader);
	}
	else
	{
		// Pass the direction in observer space
		glm::vec4 rotationForShader;
		location = shader->getLocation(variableName.c_str());

		/*rotationForShader = glm::vec4(rotation, lightType);
		rotationForShader = State::viewMatrix * rotationForShader;

		//rotationForShader = State::viewMatrix * glm::rotate(glm::translate(glm::mat4(), position), glm::angle(rotationQuat), glm::axis(rotationQuat)) * glm::vec4(1, 1, 1, lightType);
		//rotationForShader = glm::rotate(glm::translate(glm::mat4(), position), glm::angle(rotationQuat), glm::axis(rotationQuat)) * glm::vec4(1, 1, 1, lightType);

		location = shader->getLocation(variableName.c_str());
		shader->setVec4(location, rotationForShader);


		glm::vec3 vectorToRotate = glm::vec3(1, 1, 1);

		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), rotation.x, glm::vec3(1, 0, 0));
		rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0, 1, 0));
		rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0, 0, 1));

		glm::vec4 directionVector = rotationMatrix * glm::vec4(1, 1, 1, lightType);

		directionVector = normalize(directionVector);
		directionVector = State::viewMatrix * directionVector;

		shader->setVec4(location, directionVector);*/


		glm::vec4 directionVector = glm::vec4(glm::vec3(0, 0, 0) - position, lightType);

		directionVector = glm::rotate(glm::translate(glm::mat4(), position), glm::angle(rotationQuat), glm::axis(rotationQuat)) * glm::vec4(0.0f, 0.0f, 1.0f, lightType);
		//directionVector = glm::rotate(glm::translate(glm::mat4(), position), glm::angle(rotationQuat), glm::axis(rotationQuat)) * glm::normalize(directionVector);
		//glm::vec4 directionVector = glm::vec4(rotation, lightType);
		directionVector = State::viewMatrix * directionVector;

		//glm::vec4 directionVector = glm::vec4(10, 0, 1, lightType);
		shader->setVec4(location, directionVector);


/*#define SCALE(m) glm::scale(m, scale)
#define ROTATE(m) glm::rotate(m, glm::angle(rotationQuat), glm::axis(rotationQuat))
#define TRANSLATE(m) glm::translate(m, position)

		shader->setVec4(location, State::viewMatrix * SCALE(ROTATE(TRANSLATE(glm::mat4()))) * glm::vec4(1, 1, 1, lightType));
*/
	}

	variableName = "lights[" + indexString + "].linearAttenuation";
	location = shader->getLocation(variableName.c_str());
	shader->setFloat(location, linearAttenuation);

	variableName = "lights[" + indexString + "].lightColor";
	location = shader->getLocation(variableName.c_str());
	shader->setVec4(location, glm::vec4(lightColor, 1.0f));
}
