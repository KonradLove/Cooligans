#include "world_map.h"

WorldMap::WorldMap(Generator* generator) {
	WorldMap::generator = generator;

	for (int x = 0; x < WORLD_MAP_SIZE_X; x++) {
		for (int y = 0; y < WORLD_MAP_SIZE_Y; y++) {
			for (int z = 0; z < WORLD_MAP_SIZE_Z; z++) {
				map[x][y][z] = generator->generate(x, y, z);
			}
		}
	}
}

WorldMap::~WorldMap() {
	
}

bool WorldMap::get_map_point(int x, int y, int z) {
	if (!in_bounds(x,y,z)) return false;
	return map[x][y][z];
}
bool WorldMap::in_bounds(int x, int y, int z) {
	return !(x<0 || y < 0 || z < 0 || x > WORLD_MAP_SIZE_X || y > WORLD_MAP_SIZE_Y || z > WORLD_MAP_SIZE_Z);
}
bool WorldMap::in_bounds(glm::ivec3 pos) {
	return in_bounds(pos.x, pos.y, pos.z);
}
void WorldMap::set_map_point(int x, int y, int z, bool val) {
	map[x][y][z] = val;
}

bool WorldMap::get_map_point(glm::ivec3 pos) {
	return get_map_point(pos.x, pos.y, pos.z);
}



void WorldMap::set_map_point(glm::ivec3 pos, bool val) {
	set_map_point(pos.x, pos.y, pos.z, val);
}