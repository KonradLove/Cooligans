#pragma once
#include "renderable.h"
#include "config.h"
#include "default_shader.h"

class Entity {
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	Entity(glm::vec3 position) {
		Entity::position = position;
		invisible = true;
	}
	Entity(glm::vec3 position, Renderable* model) {
		Entity::position = position;
		scale = glm::vec3(1, 1, 1);
		rotation = glm::vec3(0, 0, 0);
		Entity::model = model;
	}
	Entity(glm::vec3 position, Renderable* model, DefaultShader* shader){
		Entity::position = position;
		scale = glm::vec3(1, 1, 1);
		rotation = glm::vec3(0, 0, 0);
		Entity::model = model;
		Entity::shader = shader;
		has_shader = true;
	}
	void render() {
		if (has_shader) {
			shader->position = position;
			shader->rotation = rotation;
			shader->scale = scale;
			shader->upload_uniforms();
			shader->Use();
		}
		model->bind();
		model->render();
	}
	virtual void update(float delta_time) {}
private:
	bool invisible = false;
	Renderable* model;
	bool has_shader = false;
	DefaultShader* shader;

};