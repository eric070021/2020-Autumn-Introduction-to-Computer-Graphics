#define GLM_ENABLE_EXPERIMENTAL

#include <bits/stdc++.h>
#include "Object.h"
#include "FreeImage.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"
#include <stb_image.h>

using namespace std;

void shaderInit();
void bindbufferInit();
void textureInit();
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void DrawLightPoint();
void DrawEevee();
void LoadTexture(unsigned int&, const char*);

GLuint program, Phongprogram, Toonprogram, Edgeprogram;
GLuint VAO, VBO[3];
unsigned int ToonTexture, modeltexture;
float windowSize[2] = { 600, 600 };
float angle = 0.0f;
glm::vec3 WorldLightPos = glm::vec3(2, 5, 5);
glm::vec3 WorldCamPos = glm::vec3(7.5, 5.0, 7.5);
glm::vec3 Ka = glm::vec3(1, 1, 1);
glm::vec3 Kd = glm::vec3(1, 1, 1);
glm::vec3 Ks = glm::vec3(1, 1, 1);
glm::vec3 La = glm::vec3(0.2, 0.2, 0.2);
glm::vec3 Ld = glm::vec3(0.8, 0.8, 0.8);
glm::vec3 Ls = glm::vec3(0.5, 0.5, 0.5);
float gloss = 25.0;


Object* model = new Object("../resources/Eevee/Eevee.obj");

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("hw3");

	glewInit();
	shaderInit();
	bindbufferInit();
	textureInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void shaderInit() {
	GLuint vert = createShader("../shaders/Phongshading.vert", "vertex");
	GLuint frag = createShader("../shaders/Phongshading.frag", "fragment");
	Phongprogram = createProgram(vert, frag);

	GLuint vert_Toon = createShader("../shaders/Toonshading.vert", "vertex");
	GLuint frag_Toon = createShader("../shaders/Toonshading.frag", "fragment");
	Toonprogram = createProgram(vert_Toon, frag_Toon);

	GLuint vert_Edge = createShader("../shaders/Edgeshading.vert", "vertex");
	GLuint frag_Edge = createShader("../shaders/Edgeshading.frag", "fragment");
	Edgeprogram = createProgram(vert_Edge, frag_Edge);

	program = Phongprogram;
}

void bindbufferInit() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->positions[0]) * model->positions.size(), &model->positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->normals[0]) * model->normals.size(), &model->normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->texcoords[0]) * model->texcoords.size(), &model->texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void textureInit() {
	LoadTexture(modeltexture, "../resources/Eevee/Eevee.jpg");
}

glm::mat4 getV()
{
	// set camera position and configuration
	return glm::lookAt(glm::vec3(WorldCamPos.x, WorldCamPos.y, WorldCamPos.z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

glm::mat4 getP()
{
	// set perspective view
	float fov = 45.0f;
	float aspect = windowSize[0] / windowSize[1];
	float nearDistance = 1.0f;
	float farDistance = 1000.0f;
	return glm::perspective(glm::radians(fov), aspect, nearDistance, farDistance);
}

void display() {
	//Clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawLightPoint();
	DrawEevee();
	angle += 0.03;
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	windowSize[0] = w;
	windowSize[1] = h;
}

void LoadTexture(unsigned int& texture, const char* tFileName) {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(tFileName, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	{
		glm::vec3 Zoomin = -WorldLightPos;
		glm::vec3 Left = glm::cross(glm::vec3(0, 1, 0), Zoomin);
		Left = glm::normalize(Left);
		WorldLightPos += Left;
		break;
	}
	case 's':
	{
		glm::vec3 Zoomin = -WorldLightPos;
		glm::vec3 Right = glm::cross(Zoomin, glm::vec3(0, 1, 0));
		Right = glm::normalize(Right);
		WorldLightPos += Right;
		break;
	}
	case 'z':
	{
		glm::vec3 Zoomin = -WorldLightPos;
		Zoomin = glm::normalize(Zoomin);
		WorldLightPos += Zoomin;
		break;
	}
	case 'x':
	{
		glm::vec3 Zoomout = WorldLightPos;
		Zoomout = glm::normalize(Zoomout);
		WorldLightPos += Zoomout;
		break;
	}
	case 'r':
	{
		WorldLightPos = glm::vec3(2, 5, 5);
		break;
	}
	case '1':
	{
		program = Phongprogram;
		break;
	}
	case '2':
	{
		program = Toonprogram;
		break;
	}
	case '3':
	{
		program = Edgeprogram;
		break;
	}
	default:
	{
		break;
	}
	}
}

void idle() {
	glutPostRedisplay();
}

void DrawEevee()
{
	glUseProgram(program);

	glm::mat4 M(1.0f);
	M = glm::rotate(M, glm::radians(angle), glm::vec3(0, 1, 0));
	M = glm::rotate(M, glm::radians(90.0f), glm::vec3(1, 0, 0));
	M = glm::scale (M, glm::vec3(0.3, 0.3, 0.3));

	GLuint ModelMatrixID = glGetUniformLocation(program, "M");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &M[0][0]);

	glm::mat4 V = getV();
	ModelMatrixID = glGetUniformLocation(program, "V");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &V[0][0]);

	glm::mat4 P = getP();
	ModelMatrixID = glGetUniformLocation(program, "P");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &P[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, modeltexture);
	glUniform1i(glGetUniformLocation(program, "texture"), 0);

	///// TODO: ////
	// Pass all variable to shaders and trigger by Uniform (like:WorldLightPos, WorldCamPos, Ka, La ......etc)
	ModelMatrixID = glGetUniformLocation(program, "WorldLightPos");
	glUniform3fv(ModelMatrixID, 1, &WorldLightPos[0]);

	ModelMatrixID = glGetUniformLocation(program, "WorldCamPos");
	glUniform3fv(ModelMatrixID, 1, &WorldCamPos[0]);

	ModelMatrixID = glGetUniformLocation(program, "Ka");
	glUniform3fv(ModelMatrixID, 1, &Ka[0]);
	ModelMatrixID = glGetUniformLocation(program, "Kd");
	glUniform3fv(ModelMatrixID, 1, &Kd[0]);
	ModelMatrixID = glGetUniformLocation(program, "Ks");
	glUniform3fv(ModelMatrixID, 1, &Ks[0]);

	ModelMatrixID = glGetUniformLocation(program, "La");
	glUniform3fv(ModelMatrixID, 1, &La[0]);
	ModelMatrixID = glGetUniformLocation(program, "Ld");
	glUniform3fv(ModelMatrixID, 1, &Ld[0]);
	ModelMatrixID = glGetUniformLocation(program, "Ls");
	glUniform3fv(ModelMatrixID, 1, &Ls[0]);

	ModelMatrixID = glGetUniformLocation(program, "gloss");
	glUniform1f(ModelMatrixID, gloss);


	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3 * model->fNum);
	glBindVertexArray(0);
	glActiveTexture(0);
	glUseProgram(0);
}

void DrawLightPoint() {
	// viewport transformation
	glViewport(0, 0, windowSize[0], windowSize[1]);

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)windowSize[0] / (GLfloat)windowSize[1], 1.0, 1000.0);

	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(WorldCamPos.x, WorldCamPos.y, WorldCamPos.z,// eye
		0.0, 0.0, 0.0,     // center
		0.0, 1.0, 0.0);    // up
	glPushMatrix();
	glTranslatef(WorldLightPos.x, WorldLightPos.y, WorldLightPos.z);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(0.5f, 50.0f, 50.0f);
	glPopMatrix();
}