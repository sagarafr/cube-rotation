#pragma once

#include <string>
#include <utility>
#include <GL/freeglut.h>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void loadShaderVertexFromFile(const std::string& filename);
	void loadFragmentVertexFromFile(const std::string& filename);

	void loadShaderVertex(const std::string& shader);
	void loadShaderVertex(const char** shader);
	void loadFragmentVertex(const std::string& fragment);
	void loadFragmentVertex(const char** fragment);

	void compileShaderProgram();

	GLuint getShaderProgram() const {
		return mShaderProgram.second;
	}

private:
	std::pair<bool, GLuint> mShaderProgram;
	std::pair<bool, GLuint> mShaderVertex;
	std::pair<bool, GLuint> mFragmentVertex;

	std::string loadShaderFromFile(const std::string& filename);
	void shaderCompilation(const GLuint shaderID, const char** shader);
};
