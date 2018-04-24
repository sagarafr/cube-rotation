#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "debug.hpp"
#include "shaderProgramManager.hpp"
#include "fileUtility.hpp"

static unsigned int gVAOCube;
static float gSpin;
static constexpr float gVelocity = 0.5f;

void cube(void) {
	constexpr float vertices[] = {
		// position				//color
		-0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,

		-0.5f,	-0.5f,	0.5f,	1.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,	0.5f,	1.0f,	1.0f,	0.0f,
		0.5f,	0.5f,	0.5f,	1.0f,	1.0f,	0.0f,
		0.5f,	0.5f,	0.5f,	1.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,	0.5f,	1.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,	0.5f,	1.0f,	1.0f,	0.0f,

		-0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,	0.5f,	0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	0.0f,

		0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	1.0f,
		0.5f,	0.5f,	-0.5f,	0.0f,	1.0f,	1.0f,
		0.5f,	-0.5f,	-0.5f,	0.0f,	1.0f,	1.0f,
		0.5f,	-0.5f,	-0.5f,	0.0f,	1.0f,	1.0f,
		0.5f,	-0.5f,	0.5f,	0.0f,	1.0f,	1.0f,
		0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	1.0f,

		-0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,
		0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,
		0.5f,	-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,
		0.5f,	-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,
		-0.5f,	-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,
		-0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,

		-0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	1.0f,
		0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	1.0f,
		0.5f,	0.5f,	0.5f,	1.0f,	0.0f,	1.0f,
		0.5f,	0.5f,	0.5f,	1.0f,	0.0f,	1.0f,
		-0.5f,	0.5f,	0.5f,	1.0f,	0.0f,	1.0f,
		-0.5f,	0.5f,	-0.5f,	1.0f,	0.0f,	1.0f
	};

	try {
		ShaderProgramManager::instance()->addShaderProgramFromFile("cube", getRessourceFile("cube.vert"), getRessourceFile("cube.frag"));
	}
	catch (const std::runtime_error &exception) {
		std::cerr << exception.what() << std::endl;
		return;
	}

	unsigned int VBO;

	glGenVertexArrays(1, &gVAOCube);
	glGenBuffers(1, &VBO);

	glBindVertexArray(gVAOCube);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void displayCallback(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint programID(ShaderProgramManager::instance()->getID("cube"));
	glUseProgram(programID);
	glBindVertexArray(gVAOCube);

	// TODO make a camera
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -20.0f));
	glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(2.0f, 4.0f, 5.0f));
	model = glm::rotate(model, glm::radians(gSpin), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glutSwapBuffers();
}

void reshapeCallback(int width, int heigth) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, heigth);
	glMatrixMode(GL_MODELVIEW);
}

void timerCallback(int id) {
	glutPostRedisplay();
	gSpin += gVelocity;
	if (gSpin > 360.0f) {
		gSpin -= 360.0f;
	}
	glutTimerFunc(0, timerCallback, id);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitContextVersion(4, 3);

	glutCreateWindow("cube rotation");

	glewExperimental = GL_TRUE;
	GLenum err(glewInit());
	if (GLEW_OK != err) {
		std::cerr << glewGetErrorString(err) << std::endl;

	}
	debugCallback();

	cube();

	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutTimerFunc(0, timerCallback, 0);
	glutMainLoop();

	return 0;
}
