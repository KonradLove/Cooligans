#pragma once

#include <string>

class ShaderProgram {
public:
	~ShaderProgram();

	void load_shader(std::string name);
	void Use();
	virtual void upload_uniforms() = 0;
protected:
	unsigned int program_id = 0;
private:
	unsigned int make_module(const std::string& path, unsigned int module_type);
};