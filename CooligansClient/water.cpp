#include "water.h"
#include "obj_loader.h"

Water::Water(Camera* cam) {
	water_shader = new WaterShader(cam);
	water_model = OBJLoader::loadOBJ("Water");
	water_texture = new Texture("water", GL_LINEAR);
	water_shader->position = glm::vec3(48, 5, 48);
	water_shader->scale = glm::vec3(1, 1, 1) * 250.0f;
	time = 0;
}
Water::~Water() {
	delete water_shader;
	delete water_model;
	delete water_texture;
}

void Water::render(float delta_time) {
	time += delta_time;

	water_shader->Use();
	water_shader->time = time;
	water_shader->upload_uniforms();
	water_texture->bind(GL_TEXTURE0);
	water_model->bind();
	water_model->render();
	
}