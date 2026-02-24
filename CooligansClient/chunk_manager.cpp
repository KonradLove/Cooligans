#include "chunk_manager.h"

ChunkManager::ChunkManager(Camera* cam, WorldMap* map, Texture* top_texture, Texture* bottom_texture, CubeMarcher* cube_marcher) {
	ChunkManager::map = map;
	ChunkManager::shader = new ChunkShader(cam);
	ChunkManager::cube_marcher = cube_marcher;
	ChunkManager::top_texture = top_texture;
	ChunkManager::bottom_texture = bottom_texture;
	for (int i = 0; i < NUM_CHUNKS_X; i++) {
		for (int j = 0; j < NUM_CHUNKS_Y; j++) {
			for (int k = 0; k < NUM_CHUNKS_Z; k++) {
				chunks[i][j][k] = cube_marcher->generate_mesh(top_texture, bottom_texture, map, glm::ivec3(i*CHUNK_SIZE, j * CHUNK_SIZE, k * CHUNK_SIZE));
			}
		}
	}
}

void ChunkManager::render() {
	top_texture->bind(GL_TEXTURE0);
	bottom_texture->bind(GL_TEXTURE1);
	shader->Use();
	shader->upload_uniforms();
	for (int i = 0; i < NUM_CHUNKS_X; i++) {
		for (int j = 0; j < NUM_CHUNKS_Y; j++) {
			for (int k = 0; k < NUM_CHUNKS_Z; k++) {
				chunks[i][j][k]->bind();
				chunks[i][j][k]->render();
			}
		}
	}
	
}

ChunkManager::~ChunkManager() {
	
	for (int i = 0; i < NUM_CHUNKS_X; i++) {
		for (int j = 0; j < NUM_CHUNKS_Y; j++) {
			for (int k = 0; k < NUM_CHUNKS_Z; k++) {
				delete chunks[i][j][k];
			}
		}
	}
	delete shader;
	delete cube_marcher;
}

void ChunkManager::update_chunk(Chunk* chunk, CubeMarcher::ChunkMeshInfo* info)
{
	chunk->update_mesh(info->verts, info->indices);
}

void ChunkManager::set_val(glm::ivec3 pos, bool val)
{

	if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x >= WORLD_MAP_SIZE_X || pos.y >= WORLD_MAP_SIZE_Y || pos.z >= WORLD_MAP_SIZE_Z)
		return;
	map->set_map_point(pos, val);
	int chunkx = (pos.x) / CHUNK_SIZE;
	int chunky = (pos.y) / CHUNK_SIZE;
	int chunkz = (pos.z) / CHUNK_SIZE;
	update_chunk(chunks[chunkx][chunky][chunkz], cube_marcher->generate_mesh(map, glm::ivec3(chunkx*CHUNK_SIZE, chunky * CHUNK_SIZE, chunkz * CHUNK_SIZE)));
}
