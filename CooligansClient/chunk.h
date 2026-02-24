#pragma once

#include "config.h"
#include "texture.h"
#include "renderable.h"

class Chunk : public Renderable {
public:
	Chunk(Texture* top_texture, Texture* bottom_texture, std::vector<float> verts, std::vector<int> indices, glm::ivec3 position);
	~Chunk();
	void update_mesh(std::vector<float> verts, std::vector<int> indices);
	void render() override;
	void bind() override;
	glm::ivec3 position;

private:
	const unsigned int size = 16;
	unsigned int vao_id, vbo_id, index_id;
	unsigned int vertex_count, index_count;
	Texture* top_texture;
	Texture* bottom_texture;
	
};