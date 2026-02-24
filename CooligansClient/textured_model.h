#pragma once
#include "model.h"
#include "texture.h"
#include "renderable.h"

class TexturedModel : public Renderable {
public:
	TexturedModel(Model* model, Texture* texture);
	~TexturedModel();
	void bind();
	void render();
private:
	Model* model;
	Texture* texture;
};