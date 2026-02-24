#pragma once

#include "shader_program.h"
#include "camera.h"
#include "entity_shader.h"

class ChunkShader : public EntityShader {
public:
	ChunkShader(Camera* camera);
	void upload_uniforms() override;
};