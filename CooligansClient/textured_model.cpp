#include "textured_model.h"

TexturedModel::TexturedModel(Model* model, Texture* texture) {
	TexturedModel::model = model;
	TexturedModel::texture = texture;
}
TexturedModel::~TexturedModel() {
}
void TexturedModel::bind() {
	texture->bind(GL_TEXTURE0);
	model->bind();
}
void TexturedModel::render() {
	model->render();
}