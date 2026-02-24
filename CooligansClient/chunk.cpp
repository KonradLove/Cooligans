#include "chunk.h"

Chunk::Chunk(Texture* top_texture, Texture* bottom_texture, std::vector<float> vertices, std::vector<int> indices, glm::ivec3 position) {
	Chunk::top_texture = top_texture;
	Chunk::bottom_texture = bottom_texture;
    Chunk::position = position;
    Chunk::vertex_count = vertices.size();
    Chunk::index_count = indices.size();

    //VBO
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    size_t vboBufferSize = vertices.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, vboBufferSize, vertices.data(),
        GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //INDEX
    glGenBuffers(1, &index_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
    size_t indexBufferSize = indices.size() * sizeof(int);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //VAO
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT,
        GL_FALSE, 6 * sizeof(float), (void*)0);

    //normal
    glVertexAttribPointer(1, 3, GL_FLOAT,
        GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    //uv
    //glVertexAttribPointer(2, 2, GL_FLOAT,
    //    GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    //glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

Chunk::~Chunk() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao_id);
    glDeleteBuffers(1, &vbo_id);
    glDeleteBuffers(1, &index_id);
}

void Chunk::render() {
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
}

void Chunk::bind()
{
    glBindVertexArray(vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vao_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
    bottom_texture->bind(GL_TEXTURE0);
    top_texture->bind(GL_TEXTURE1);
}

void Chunk::update_mesh(std::vector<float> verts, std::vector<int> indices) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    vertex_count = verts.size();
    index_count = indices.size();
}