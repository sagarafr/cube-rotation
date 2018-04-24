#pragma once

#include <GL/freeglut.h>
#include "idManager.hpp"
#include "singelton.hpp"
#include "shaderProgram.hpp"

class ShaderProgramManager : public Singelton<ShaderProgramManager>, public IDManager<ShaderProgram> {
public:
	ShaderProgramManager() {}

	ShaderProgramManager(const ShaderProgramManager& manager) = delete;
	ShaderProgramManager(const ShaderProgramManager&& manager) = delete;

	ShaderProgramManager& operator=(const ShaderProgramManager& manager) = delete;
	ShaderProgramManager& operator=(const ShaderProgramManager&& manager) = delete;

	virtual ~ShaderProgramManager() {}
	void addShaderProgramFromFile(const std::string id, const std::string& fileShaderVertex, const std::string& fileFragmentVertex);

protected:
	virtual GLuint getIDFromElement(const ShaderProgram* element) const {
		return element->getShaderProgram();
	}	
};
