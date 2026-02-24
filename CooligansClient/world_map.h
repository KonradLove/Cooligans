#pragma once

#include <glm/glm.hpp>
#include "generator.h"
#include "config.h"

class WorldMap {
public:
	WorldMap(Generator* generator);
	~WorldMap();

	bool get_map_point(int x, int y, int z);
	bool get_map_point(glm::ivec3 pos);

	void set_map_point(int x, int y, int z, bool val);
	void set_map_point(glm::ivec3 pos, bool val);

	bool in_bounds(int x, int y, int z);
	bool in_bounds(glm::ivec3 pos);
private:
	bool map[WORLD_MAP_SIZE_X][WORLD_MAP_SIZE_Y][WORLD_MAP_SIZE_Z];
	Generator* generator;
};