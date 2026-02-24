#pragma once
#include "model.h"
#include "texture.h"
#include "renderable.h"

class MultitextureModel : public Renderable {
public:
	MultitextureModel(Model* model, std::vector<Texture*> textures);
	~MultitextureModel();
	void bind();
	void render();
private:
	Model* model;
	std::vector<Texture*> textures;
};