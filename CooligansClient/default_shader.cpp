#include "default_shader.h"
#include "config.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

DefaultShader::DefaultShader(Camera* camera) {
	load_shader("default");

	time = 0;

	uTime = glGetUniformLocation(program_id, "time");

	uProj = glGetUniformLocation(program_id, "projection");
	uModel = glGetUniformLocation(program_id, "model");
	uView = glGetUniformLocation(program_id, "view");

	uPosition = glGetUniformLocation(program_id, "objectPosition");

	DefaultShader::camera = camera;
}
void DefaultShader::upload_uniforms() {
	//DefaultShader::time += 0.0002f;
	//glUniform1f(uTime, time);
	
	glm::mat4x4 m_mat = glm::identity<glm::mat4x4>();;
	m_mat = glm::translate(m_mat, position);
	m_mat = glm::scale(m_mat, scale);
	m_mat = glm::rotate(m_mat, rotation.x, glm::vec3(1, 0, 0));
	m_mat = glm::rotate(m_mat, rotation.y, glm::vec3(0, 1, 0));
	m_mat = glm::rotate(m_mat, rotation.z, glm::vec3(0, 0, 1));
	//
	//
	//
	glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(m_mat));
	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(camera->view_matrix));
	glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(camera->generate_projection_matrix()));
	glUniform3f(uPosition, position.x, position.y, position.z);
	
}