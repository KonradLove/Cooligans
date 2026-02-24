#pragma once

#include "config.h"

class Generator {
public:
	Generator();
	~Generator();
	bool generate(int x, int y, int z);
	bool generate(glm::ivec3 pos);
private:

};