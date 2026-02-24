#pragma once
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
class Camera {
public:
	Camera(glm::vec3 position);

	void set_fov(float fov);
	float get_fov();

	void set_near(float near);
	float get_near();

	void set_far(float far);
	float get_far();

	void set_aspect(float aspect);
	float get_aspect();

	glm::mat4x4 generate_projection_matrix();

	void update();

	glm::mat4x4 get_untranslated_view_matrix();

	glm::vec3 position;
	glm::vec3 rotation;

	glm::mat4x4 view_matrix;

private:
	glm::mat4x4 projection_matrix;

	glm::mat4x4 create_view_matrix();

	float fov, near, far, aspect;
	bool dirty;

};