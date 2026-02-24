#pragma once

#include "shader_program.h"
#include "camera.h"
#include "entity_shader.h"

class DefaultShader : public EntityShader {
public:
	DefaultShader(Camera* camera);
	void upload_uniforms() override;
};