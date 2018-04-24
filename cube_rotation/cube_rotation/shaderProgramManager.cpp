#include "shaderProgramManager.hpp"

void ShaderProgramManager::addShaderProgramFromFile(const std::string id, const std::string& fileShaderVertex, const std::string& fileFragmentVertex) {
	ShaderProgram* shader = new ShaderProgram();
	shader->loadShaderVertexFromFile(fileShaderVertex);
	shader->loadFragmentVertexFromFile(fileFragmentVertex);
	shader->compileShaderProgram();
	// TODO check the return value if its insert or not
	mElements.emplace(id, shader);
}
