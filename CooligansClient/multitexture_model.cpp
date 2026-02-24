#include "multitexture_model.h"

MultitextureModel::MultitextureModel(Model* model, std::vector<Texture*> textures) {
	MultitextureModel::model = model;
	MultitextureModel::textures = textures;
}
MultitextureModel::~MultitextureModel() {
}
void MultitextureModel::bind() {}
void MultitextureModel::render() {
	int start = 0;
	model->bind();
	for (int i = 0; i < textures.size(); i++) {
		int texLength = model->textures[i];
		textures[i]->bind(GL_TEXTURE0);
		model->render_section(start, texLength);
		start += texLength;
	}
}