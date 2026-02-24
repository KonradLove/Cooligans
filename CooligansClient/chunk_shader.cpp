#include "chunk_shader.h"
#include "config.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

ChunkShader::ChunkShader(Camera* camera) {
	load_shader("chunk");

	time = 0;

	uProj = glGetUniformLocation(program_id, "projection");
	uModel = 0;
	uView = glGetUniformLocation(program_id, "view");

	ChunkShader::camera = camera;
}
void ChunkShader::upload_uniforms() {
	//glm::mat4x4 m_mat = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
	//m_mat = glm::translate(m_mat, position);
	//glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(m_mat));
	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(camera->view_matrix));
	glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(camera->generate_projection_matrix()));

}