#include "model.h"

Model::Model(std::vector<float> vertices, std::vector<int> indices, std::vector<int> textures)
{
    vertex_count = vertices.size();
    index_count = indices.size();

    Model::textures = textures;

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
        GL_FALSE, 8 * sizeof(float), (void*)0);

    //normal
    glVertexAttribPointer(1, 3, GL_FLOAT,
        GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));

    //uv
    glVertexAttribPointer(2, 2, GL_FLOAT,
        GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}


Model::~Model() {
    glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao_id);
	glDeleteBuffers(1, &vbo_id);
    glDeleteBuffers(1, &index_id);
}

void Model::bind() {
	glBindVertexArray(vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vao_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
}
void Model::render() {
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
}
void Model::render_section(unsigned int start, unsigned int length)
{
    glDrawElements(GL_TRIANGLES, length * 3, GL_UNSIGNED_INT, (const void*)(start * 3 * sizeof(int)));
}
void Model::unbind() {
	glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}