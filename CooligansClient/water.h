#pragma once
#include "model.h"
#include "texture.h"
#include "camera.h"
#include "water_shader.h"

class Water {
public:
	Water(Camera* cam);
	~Water();
	void render(float delta_time);
private:
	float time;
	WaterShader* water_shader;
	Model* water_model;
	Texture* water_texture;
};