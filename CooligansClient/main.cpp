#include "config.h"
#include "skybox.h"
#include "model.h"
#include "camera.h"
#include "texture.h"
#include "textured_model.h"
#include "obj_loader.h"
#include "entity.h"
#include <math.h>
#include <chrono>
#include <thread>
#include "chunk_manager.h"
#include "water.h"
#include "player.h"

//https://github.com/SRombauts/SimplexNoise/
//stb_image.h

int main() {
	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}

	window = glfwCreateWindow(1920, 1080, "Cooligans", NULL, NULL);
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Camera* camera = new Camera(glm::vec3(0, 0, 3));

	
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);


	auto last_time = std::chrono::steady_clock::now();

	Texture* top_texture = new Texture("snow", GL_LINEAR);
	Texture* bottom_texture = new Texture("ice", GL_LINEAR);

	Texture* sky_texture = new Texture("sky1", GL_LINEAR);

	DefaultShader* shader = new DefaultShader(camera);

	Skybox* skybox = new Skybox(sky_texture, shader, camera);

	Water* water = new Water(camera);

	Generator* generator = new Generator();
	CubeMarcher* cube_marcher = new CubeMarcher();
	WorldMap* map = new WorldMap(generator);

	ChunkManager* chunk_manager = new ChunkManager(camera, map, top_texture, bottom_texture, cube_marcher);

	Player* player = new Player(glm::vec3(10, 100, 10), map, camera);

	using namespace std::chrono_literals;
	while (!glfwWindowShouldClose(window)) {

		auto current_time = std::chrono::steady_clock::now();
		auto elapsed = current_time - last_time;
		double delta_time = elapsed.count() / 500000000.0;
		last_time = std::chrono::steady_clock::now();

		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			player->position.x += sin(camera->rotation.y) * delta_time * 3;
			player->position.z += -cos(camera->rotation.y) * delta_time * 3;
		}if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			player->position.x -= sin(camera->rotation.y) * delta_time * 3;
			player->position.z -= -cos(camera->rotation.y) * delta_time * 3;
		}if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			player->position.y += delta_time * 2;
		}if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			player->position.y -= delta_time * 2;
		}if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			camera->rotation.y -= delta_time * 2.5f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			camera->rotation.y += delta_time * 2.5f;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			camera->rotation.x -= delta_time * 2.5f;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			camera->rotation.x += delta_time * 2.5f;
		camera->update();
		player->update(delta_time);

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			
			chunk_manager->set_val((glm::ivec3)camera->position, true);
		}


		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		//glDisable(GL_DEPTH_TEST);
		skybox->render(delta_time);
		//glEnable(GL_DEPTH_TEST);

		water->render(delta_time);

		chunk_manager->render();


		glfwSwapBuffers(window);
		std::this_thread::sleep_for(0.1us);
	}
	
	delete chunk_manager;
	delete top_texture;
	delete bottom_texture;
	delete sky_texture;
	delete map;
	delete generator;
	delete water;
	delete skybox;

	glfwTerminate();
	return 0;
}