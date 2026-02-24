#pragma once
#include "config.h"

class Texture {
public:
	int width, height, nChannels;
	Texture(std::string name, int type);
	~Texture();
	void bind(int texture_unit);
private:
	unsigned int texture_id;
};