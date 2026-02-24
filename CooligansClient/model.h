#pragma once

#include "config.h"
#include "renderable.h"

class Model : public Renderable {
public:
	Model(std::vector<float> vertices, std::vector<int> indices, std::vector<int> textures);
	~Model();
	void bind();
	void unbind();
	void render();
	void render_section(unsigned int start, unsigned int length);
	std::vector<int> textures;
private:
	unsigned int vao_id;
	unsigned int index_id;
	unsigned int vbo_id;
	unsigned int vertex_count;
	unsigned int index_count;
	
};