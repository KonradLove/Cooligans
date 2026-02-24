#pragma once
#include "shader_program.h"
#include "camera.h"

class EntityShader : public ShaderProgram {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float time;
protected:
	unsigned int uProj;
	unsigned int uModel;
	unsigned int uView;
	unsigned int uTime;
	unsigned int uPosition;
	Camera* camera;
};