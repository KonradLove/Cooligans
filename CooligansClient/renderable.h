#pragma once

class Renderable {
public:
	virtual void render() = 0;
	virtual void bind() = 0;
};