#include "camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

Camera::Camera(glm::vec3 position){
	Camera::position = position;
	Camera::rotation = glm::vec3(0, 0, 0);
	Camera::fov = 90.0f;
	Camera::aspect = 1920.0f / 1080.0f;
	Camera::near = 0.01f;
	Camera::far = 1000.0f;
	dirty = true;
	projection_matrix = generate_projection_matrix();
}

float Camera::get_aspect() { return aspect; }
void Camera::set_aspect(float aspect) { Camera::aspect = aspect; }

float Camera::get_near() { return near; }
void Camera::set_near(float aspect) { Camera::near = near; dirty = true; }


float Camera::get_far() { return far; }
void Camera::set_far(float aspect) { Camera::far = far; dirty = true; }

float Camera::get_fov() { return fov; }
void Camera::set_fov(float fov) { Camera::fov = fov; dirty = true; }

glm::mat4x4 Camera::generate_projection_matrix() {
	if (!dirty) return projection_matrix;
	projection_matrix = glm::perspectiveFov(3.141592f * (fov / 180.0f), aspect, 1.0f, near, far);
	dirty = false;
	return projection_matrix;
}

glm::mat4x4 Camera::create_view_matrix() {
	glm::mat4x4 matrix = glm::identity<glm::mat4x4>();
	matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
	matrix = glm::translate(matrix, -position);
	return matrix;
}
glm::mat4x4 Camera::get_untranslated_view_matrix() {
	glm::mat4x4 matrix = glm::identity<glm::mat4x4>();
	matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
	return matrix;
}

void Camera::update() {
	view_matrix = Camera::create_view_matrix();
}

