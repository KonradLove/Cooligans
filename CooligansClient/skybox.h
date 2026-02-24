#pragma once
#define CLOUD_PARTS 20

#include "config.h"
#include "texture.h"
#include "default_shader.h"
#include "skybox_shader.h"
#include "model.h"

class Skybox {
public:
	Skybox(Texture* sky_texture, DefaultShader* default_shader, Camera* cam);
	~Skybox();
	void render(float delta_time);

private:
	struct Iceberg {
		glm::vec3 position;
		int iceberg;
		float scale;
		float rot;
		Iceberg(glm::vec3 pos, int ice, float s, float r) {
			position = pos;
			iceberg = ice;
			scale = s;
			rot = r;
		}
	};
	struct Cloud {
		float offset;
		float rotation;
		std::vector<glm::vec3> cloud_positions;
		Cloud(float _offset, float _rotation) {
			offset = _offset;
			rotation = _rotation;
		}
	};
	Texture* sky_texture;
	Texture* cloud_texture;
	Texture* iceberg_texture;
	Model* sky_model;
	Model* cloud_model;
	SkyboxShader* sky_shader;
	DefaultShader* shader;
	std::vector<Model*> iceberg_models;
	std::vector<Iceberg> icebergs;
	std::vector<Cloud> clouds;
	float rand_float();
	glm::vec3 get_cloud_pos(Cloud& cloud, int c);
};