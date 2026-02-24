#include "skybox.h"
#include <random>
#include <math.h>

#include "obj_loader.h"

glm::vec3 Skybox::get_cloud_pos(Cloud& cloud, int c) {
	glm::vec3 c_pos(cosf(cloud.rotation + c / 50.0) * 140.0 + 48, 80.0f + cloud.offset * 40.0f, sinf(cloud.rotation + c / 50.0) * 140.0 + 48);
	c_pos += (rand_float() - 0.5f) * 20.0f;
	return c_pos;
}

Skybox::Skybox(Texture* sky_texture, DefaultShader* shader, Camera* cam) {
	Skybox::shader = shader;

	Skybox::sky_texture = sky_texture;
	cloud_texture = new Texture("cloud", GL_LINEAR);
	iceberg_texture = new Texture("iceberg", GL_LINEAR);

	sky_shader = new SkyboxShader(cam);
	sky_shader->scale  = glm::vec3(1,1,1) * 250.0f;
	sky_shader->position = glm::vec3(48, -50.0f, 48);

	sky_model = OBJLoader::loadOBJ("Sky");
	cloud_model = OBJLoader::loadOBJ("Clouds");

	iceberg_models.push_back(OBJLoader::loadOBJ("icebergs/iceberg1"));
	iceberg_models.push_back(OBJLoader::loadOBJ("icebergs/iceberg2"));
	iceberg_models.push_back(OBJLoader::loadOBJ("icebergs/iceberg3"));
	for (int i = 0; i < 20; i++) {
		float dist = 120.0f + rand_float()*80.0;
		float rot = rand_float() * 6.28f;
		glm::vec3 pos(cosf(rot)*dist, 7, sinf(rot)*dist);
		
		icebergs.push_back(Iceberg(pos, rand()%iceberg_models.size(), 5.0f + rand_float() * 10.0f, 6.28f * rand_float()));
	}

	/*for (int i = 0; i < 4; i++) {
		float rot = rand_float() * 6.28f;
		Cloud cloud = Cloud(rand_float(), rot);
		for (int c = 0; c < CLOUD_PARTS; c++) {
			cloud.cloud_positions.push_back(get_cloud_pos(cloud,c));

		}
		
		clouds.push_back(cloud);
	}*/
}
float Skybox::rand_float() {
	return rand() / ((float)RAND_MAX);
}

Skybox::~Skybox() {
	delete sky_model;
	delete cloud_model;
	delete cloud_texture;
	delete sky_shader;
	delete iceberg_texture;
	for (Model* model : iceberg_models) {
		delete model;
	}
}

void Skybox::render(float delta_time) {
	sky_shader->Use();
	sky_shader->upload_uniforms();
	sky_model->bind();
	sky_texture->bind(GL_TEXTURE0);
	sky_model->render();


	shader->Use();
	


	iceberg_texture->bind(GL_TEXTURE0);

	for (Iceberg& iceberg : icebergs) {

		shader->scale = glm::vec3(1, 1, 1)*iceberg.scale;
		shader->position = iceberg.position + glm::vec3(48,0,48);
		shader->rotation = glm::vec3(0, iceberg.rot, 0);
		shader->upload_uniforms();

		iceberg_models[iceberg.iceberg]->bind();
		iceberg_models[iceberg.iceberg]->render();
	}
	/*cloud_texture->bind(GL_TEXTURE0);
	cloud_model->bind();

	for (Cloud& cloud : clouds) {
		for (int c = 0; c < CLOUD_PARTS; c++ ) {
			glm::vec3 position = cloud.cloud_positions[c];
			shader->position = position;
			float osc = cloud.rotation*100.0 + c / 2.0;
			float size = sin(osc) + 1.0;
			shader->scale = glm::vec3(size > 1.0f ? 1.0f : size)*5.0f;
			shader->rotation = glm::vec3(0);
			shader->upload_uniforms();
			cloud_model->render();
			
			//if (c >= cloud.cloud_positions.size()-1) {
				if (size < 0.01f && cos(osc)<0) {
					cloud.cloud_positions[c] = get_cloud_pos(cloud, c);

					//std::swap(cloud.cloud_positions[0], cloud.cloud_positions[CLOUD_PARTS - 1]);

				}
			//}
		}
		
		cloud.rotation += delta_time/200.0;

	}*/


}