#pragma once

#include "shader_program.h"
#include "camera.h"
#include "entity_shader.h"

class WaterShader : public EntityShader {
public:
	WaterShader(Camera* camera);
	void upload_uniforms() override;
};