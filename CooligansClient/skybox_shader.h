#pragma once

#include "shader_program.h"
#include "camera.h"
#include "entity_shader.h"

class SkyboxShader : public EntityShader {
public:
	SkyboxShader(Camera* camera);
	void upload_uniforms() override;
};