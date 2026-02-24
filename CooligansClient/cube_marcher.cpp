#include "cube_marcher.h"
#include <glm/gtx/normal.hpp>

CubeMarcher::CubeMarcher() {

}
CubeMarcher::ChunkMeshInfo* CubeMarcher::generate_mesh(WorldMap* map, ivec3 position) {
	std::vector<float> vertices;
	std::vector<int> indices;
	std::vector<int> textures;
	std::vector<GridVert> grid_verts;

	std::vector<int> grid_vertex_index((CHUNK_SIZE + 6) * (CHUNK_SIZE + 6) * (CHUNK_SIZE + 6) * 3, -1);

	int cIndex = 0;
	int flat_found = 0;
	int repeated = 0;
	for (int i = 1; i < CHUNK_SIZE + 1; i++) {
		for (int j = 1; j < CHUNK_SIZE + 1; j++) {
			for (int k = 1; k < CHUNK_SIZE + 1; k++) {
				glm::vec3 pos(i, j, k);
				int x = i + position.x;
				int y = j + position.y;
				int z = k + position.z;
				unsigned short index = 0;
				if (map->get_map_point(x - 1, y - 1, z - 1))		index |= 1;
				if (map->get_map_point(x, y - 1, z - 1))	index |= 2;
				if (map->get_map_point(x - 1, y, z - 1))	index |= 8;
				if (map->get_map_point(x, y, z - 1))		index |= 4;

				if (map->get_map_point(x - 1, y - 1, z))    index |= 16;
				if (map->get_map_point(x, y - 1, z))		index |= 32;
				if (map->get_map_point(x - 1, y, z))		index |= 128;
				if (map->get_map_point(x, y, z))			index |= 64;

				for (int t = 0; cubemarcher_tritable[index][t] != -1; t += 3) {
					glm::vec3 p1 = edge_positions[cubemarcher_tritable[index][t + 2]] + pos;
					glm::vec3 p2 = edge_positions[cubemarcher_tritable[index][t + 1]] + pos;
					glm::vec3 p3 = edge_positions[cubemarcher_tritable[index][t]] + pos;

					vec3 normal = triangleNormal(p1, p2, p3);

					for (int v = 0; v < 3; v++) {
						int offset = cubemarcher_tritable[index][t + (2 - v)];
						vec3 edge_pos = edge_positions[offset];
						ivec3 edge_pos_i = edge_positions_i[offset];
						/*int x_edge = floor((i + edge_pos.x) * 2.0);
						int y_edge = floor((j + edge_pos.y)*2.0);
						int z_edge = floor((k + edge_pos.z)*2.0);*/
						int x_edge = i * 2 + edge_pos_i.x;
						int y_edge = j * 2 + edge_pos_i.y;
						int z_edge = k * 2 + edge_pos_i.z;


						unsigned int flat = flatten(x_edge, y_edge, z_edge);

						int ver = grid_vertex_index[flat];
						if (ver == -1) {
							flat_found++;
							GridVert new_vert;
							new_vert.x = x_edge;
							new_vert.y = y_edge;
							new_vert.z = z_edge;
							new_vert.pos = pos + edge_positions[offset];
							new_vert.normal = normal;

							grid_verts.push_back(new_vert);
							grid_vertex_index[flat] = grid_verts.size() - 1;
							indices.push_back(grid_verts.size() - 1);


						}
						else {
							//if (ver == 0) repeated++;
							//std::cout << ver << std::endl;
							GridVert& old_vert = grid_verts[ver];
							old_vert.uses++;
							old_vert.normal += normal;
							indices.push_back(ver);
							repeated++;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < grid_verts.size(); i++) {
		//vec3 edge_pos = edge_positions[grid_verts[i].offset];
		vertices.push_back(grid_verts[i].pos.x + position.x);
		vertices.push_back(grid_verts[i].pos.y + position.y);
		vertices.push_back(grid_verts[i].pos.z + position.z);

		vec3 normal = glm::normalize(grid_verts[i].normal);
		vertices.push_back(normal.x);
		vertices.push_back(normal.y);
		vertices.push_back(normal.z);

		//vertices.push_back(grid_verts[i].ux);
		//vertices.push_back(grid_verts[i].uy);
	}
	grid_verts.clear();
	grid_vertex_index.clear();
	return new ChunkMeshInfo(vertices, indices);
}
Chunk* CubeMarcher::generate_mesh(Texture* top_texture, Texture* bottom_texture, WorldMap* map, ivec3 position) {
	ChunkMeshInfo* info = generate_mesh(map, position);
	//std::cout << flat_found << " " << repeated << std::endl;
	return new Chunk(top_texture, bottom_texture, info->verts, info->indices, position);
	//return new Model(vertices, indices, textures);
}
/*int CubeMarcher::flatten(int x, int y, int z, int offset)
{
	   return ((x * (CHUNK_SIZE+1) * (CHUNK_SIZE + 1)) + (y * (CHUNK_SIZE + 1)) + z) * 3 + offset;
}*/
unsigned int CubeMarcher::flatten(unsigned int x, unsigned int y, unsigned int z)
{
	return  (x * (CHUNK_SIZE+1) * 2 * (CHUNK_SIZE + 1) * 2) + (y * (CHUNK_SIZE + 1) * 2) + z;
}