#include "skybox_shader.h"
#include "config.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

SkyboxShader::SkyboxShader(Camera* camera) {
	load_shader("skybox");

	time = 0;

	uTime = glGetUniformLocation(program_id, "time");

	uProj = glGetUniformLocation(program_id, "projection");
	uModel = glGetUniformLocation(program_id, "model");
	uView = glGetUniformLocation(program_id, "view");

	SkyboxShader::camera = camera;
}
void SkyboxShader::upload_uniforms() {
	//DefaultShader::time += 0.0002f;
	//glUniform1f(uTime, time);


	glm::mat4x4 m_mat = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
	m_mat = glm::translate(m_mat, position);
	m_mat = glm::scale(m_mat, scale);
	glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(m_mat));
	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(camera->view_matrix));
	glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(camera->generate_projection_matrix()));
}