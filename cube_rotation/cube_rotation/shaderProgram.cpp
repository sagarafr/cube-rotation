#include <GL/glew.h>
#include <GL/freeglut.h>
#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include "shaderProgram.hpp"

ShaderProgram::ShaderProgram() {
	mShaderVertex = std::make_pair<bool, GLuint>(false, static_cast<GLuint>(0));
	mFragmentVertex = std::make_pair<bool, GLuint>(false, static_cast<GLuint>(0));
	mShaderProgram = std::make_pair<bool, GLuint>(false, static_cast<GLuint>(0));
}

ShaderProgram::~ShaderProgram() {
	if (mShaderVertex.first) {
		glDeleteShader(mShaderVertex.second);
	}
	if (mFragmentVertex.first) {
		glDeleteShader(mFragmentVertex.second);
	}
	if (mShaderProgram.first) {
		glDeleteProgram(mShaderProgram.second);
	}
}

void ShaderProgram::loadShaderVertexFromFile(const std::string& filename) {
	std::string shader(loadShaderFromFile(filename));
	loadShaderVertex(shader);
}

void ShaderProgram::loadFragmentVertexFromFile(const std::string& filename) {
	std::string shader(loadShaderFromFile(filename));
	loadFragmentVertex(shader);
}

void ShaderProgram::loadShaderVertex(const std::string& shader) {
	const char* shaderCStr = shader.c_str();
	loadShaderVertex(&shaderCStr);
}

void ShaderProgram::loadShaderVertex(const char** shader) {
	if (mShaderVertex.first) {
		mShaderVertex.first = false;
		glDeleteShader(mShaderVertex.second);
	}
	mShaderVertex.second = glCreateShader(GL_VERTEX_SHADER);
	shaderCompilation(mShaderVertex.second, shader);
	mShaderVertex.first = true;
}

void ShaderProgram::loadFragmentVertex(const std::string& fragment) {
	const char* shaderCStr = fragment.c_str();
	loadFragmentVertex(&shaderCStr);
}

void ShaderProgram::loadFragmentVertex(const char** fragment) {
	if (mFragmentVertex.first) {
		mFragmentVertex.first = false;
		glDeleteShader(mFragmentVertex.second);
	}
	mFragmentVertex.second = glCreateShader(GL_FRAGMENT_SHADER);
	shaderCompilation(mFragmentVertex.second, fragment);
	mFragmentVertex.first = true;
}

void ShaderProgram::shaderCompilation(const GLuint shaderID, const char** shader) {
	int success;
	int lengthLog;
	glShaderSource(shaderID, 1, shader, nullptr);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &lengthLog);
	if (!success) {
		std::string log(lengthLog, ' ');
		glGetShaderInfoLog(shaderID, lengthLog, nullptr, &log[0]);
		log.erase(std::remove(log.begin(), log.end(), '\n'), log.end());
		throw std::runtime_error(log);
	}
}

std::string ShaderProgram::loadShaderFromFile(const std::string& filename) {
	std::ifstream vertexShaderStream(filename, std::ios::in);
	std::string shader;
	if (vertexShaderStream.is_open()) {
		std::stringstream strStream;
		strStream << vertexShaderStream.rdbuf();
		shader = strStream.str();
		vertexShaderStream.close();
	}
	return shader;
}

void ShaderProgram::compileShaderProgram() {
	int success;
	int lengthLog;
	if (mShaderProgram.first) {
		glDeleteProgram(mShaderProgram.second);
		mShaderProgram.first = false;
	}
	mShaderProgram.second = glCreateProgram();
	if (mShaderVertex.first) {
		glAttachShader(mShaderProgram.second, mShaderVertex.second);
	}
	if (mFragmentVertex.first) {
		glAttachShader(mShaderProgram.second, mFragmentVertex.second);
	}
	glLinkProgram(mShaderProgram.second);
	glGetProgramiv(mShaderProgram.second, GL_LINK_STATUS, &success);
	glGetProgramiv(mShaderProgram.second, GL_INFO_LOG_LENGTH, &lengthLog);
	if (!success) {
		std::string log(lengthLog, ' ');
		glGetShaderInfoLog(mShaderProgram.second, lengthLog, nullptr, &log[0]);
		log.erase(std::remove(log.begin(), log.end(), '\n'), log.end());
		throw std::runtime_error(log);
	}
	mShaderProgram.first = true;
}
