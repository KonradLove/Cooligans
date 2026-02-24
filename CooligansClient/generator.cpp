#include "generator.h"
#include "SimplexNoise.h"
#include <math.h>

Generator::Generator() {
}
Generator::~Generator() {

}

bool Generator::generate(int x, int y, int z) {
	if (y >= 46) return false;
	//srand(5);
	glm::vec3 pos(x + 1000, y + 1000, z+1000);
	glm::vec3 normalised_pos(x / (float)WORLD_MAP_SIZE_X, y / (float)WORLD_MAP_SIZE_Y, z / (float)WORLD_MAP_SIZE_Z);
	normalised_pos = (normalised_pos - 0.5f) * 2.0f;
	pos /= 30.0f;
	float height_mod = -1.0f * powf(normalised_pos.x, 8) - powf(normalised_pos.z, 8) + 1.0f;
	float noise_val_3d = (SimplexNoise::noise(pos.x,pos.y,pos.z)+1.0f)/2.0f;
	noise_val_3d += (SimplexNoise::noise(pos.x*2.0f, pos.y * 2.0f, pos.z * 2.0f)) / 3.0f;

	//float noise_val_2d = (SimplexNoise::noise(pos.x/2.0f, pos.z / 2.0f)+1.0f)/4.0f;
	float boundary = y / (48.0f*height_mod);
	//bool base_ground = noise_val_2d+0.2f > boundary;
	if (noise_val_3d > boundary && height_mod > 0.0f) return true;
	//if (base_ground) return true;
	return false;
}
bool Generator::generate(glm::ivec3 pos) {
	return generate(pos.x, pos.y, pos.z);
}