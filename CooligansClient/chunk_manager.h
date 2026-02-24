#pragma once

#include "chunk.h"
#include "cube_marcher.h"
#include "chunk_shader.h"
#include "world_map.h"

class ChunkManager {
public:
	ChunkManager(Camera* cam, WorldMap* map, Texture* top_texture, Texture* bottom_texture, CubeMarcher* cube_marcher);
	~ChunkManager();
	void update_chunk(Chunk* chunk, CubeMarcher::ChunkMeshInfo* info);
	void set_val(glm::ivec3 pos, bool val);
	Chunk* chunks[NUM_CHUNKS_X][NUM_CHUNKS_Y][NUM_CHUNKS_Z];
	void render();
private:
	WorldMap* map;
	
	ChunkShader* shader;
	Texture* top_texture;
	Texture* bottom_texture;
	CubeMarcher* cube_marcher;
};