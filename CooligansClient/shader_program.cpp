#include "shader_program.h"
#include "config.h"

void ShaderProgram::load_shader(std::string name) {
	int vert_pointer = make_module("res/shaders/" + name + ".vert", GL_VERTEX_SHADER);
	int frag_pointer = make_module("res/shaders/" + name + ".frag", GL_FRAGMENT_SHADER);

	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vert_pointer);
	glAttachShader(shader, frag_pointer);
	glLinkProgram(shader);

	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetProgramInfoLog(shader, 1024, NULL, errorLog);
		std::cout << "Shader Linking Error!\n" << errorLog << std::endl;
	}

	glDeleteShader(vert_pointer);
	glDeleteShader(frag_pointer);

	ShaderProgram::program_id = shader;
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(program_id);
}

void ShaderProgram::Use() {
	glUseProgram(program_id);
}

unsigned int ShaderProgram::make_module(const std::string& path, unsigned int module_type) {
	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(path);
	while (std::getline(file, line)) {
		bufferedLines << line << "\n";
	}

	std::string shaderSource = bufferedLines.str();
	const char* shaderSrc = shaderSource.c_str();
	bufferedLines.clear();
	file.close();

	unsigned int shaderModule = glCreateShader(module_type);
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	glCompileShader(shaderModule);

	int success;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		std::cout << "Compilation Error!\n" << errorLog << std::endl;
	}

	return shaderModule;
}

