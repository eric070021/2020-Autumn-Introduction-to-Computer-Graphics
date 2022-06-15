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
void bindbufferInit_Umbreon(Object* model);
void bindbufferInit_Eevee(Object* model);
void textureInit();
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void DrawUmbreon(GLuint);
void DrawEevee(GLuint);
void LoadTexture(unsigned int&, const char*);

GLuint Explosionprogram, Umbreonprogram, Heartbeatprogram, Eeveeprogram;
GLuint VAO_U, VBO_U[3], VAO_E, VBO_E[3];
unsigned int Umbreon_texture, Eevee_texture;
float windowSize[2] = { 600, 600 };
float angle = 0.0f;
float front_Eevee = 0.0f, back_Eevee = 0.0f, up_Eevee = 0.0f, down_Eevee =0.0f;
float front_Umbreon = 0.0f, back_Umbreon = 0.0f;
float camera_angle = 0.0f, camera_in = 0.0f;
glm::vec3 WorldLightPos = glm::vec3(2, 5, 5);
glm::vec3 WorldCamPos = glm::vec3(7.5, 5.0, 7.5);
float counter=0, explode=0;

Object* Umbreon = new Object("../resources/Umbreon.obj");
Object* Eevee = new Object("../resources/Eevee/Eevee.obj");

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("hw4");

	glewInit();
	shaderInit();
	bindbufferInit_Umbreon(Umbreon);
	bindbufferInit_Eevee(Eevee);
	textureInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void shaderInit() {
	GLuint vert = createShader("../shaders/explosion.vert", "vertex");
	GLuint goem = createShader("../shaders/explosion.geom", "geometry");
	GLuint frag = createShader("../shaders/explosion.frag", "fragment");
	Explosionprogram = createProgram(vert, goem,frag);

	vert = createShader("../shaders/heartbeat.vert", "vertex");
	goem = createShader("../shaders/heartbeat.geom", "geometry");
	frag = createShader("../shaders/heartbeat.frag", "fragment");
	Heartbeatprogram = createProgram(vert, goem, frag);

	vert = createShader("../shaders/Umbreon.vert", "vertex");
	frag = createShader("../shaders/Umbreon.frag", "fragment");
	Umbreonprogram = createProgram(vert, 0, frag);
	
	vert = createShader("../shaders/Eevee.vert", "vertex");
	frag = createShader("../shaders/Eevee.frag", "fragment");
	Eeveeprogram = createProgram(vert, 0, frag);
}

void bindbufferInit_Umbreon(Object* model) {
	glGenVertexArrays(1, &VAO_U);
	glGenBuffers(3, VBO_U);

	glBindVertexArray(VAO_U);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_U[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->positions[0]) * model->positions.size(), &model->positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_U[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->normals[0]) * model->normals.size(), &model->normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_U[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->texcoords[0]) * model->texcoords.size(), &model->texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void bindbufferInit_Eevee(Object* model) {
	glGenVertexArrays(1, &VAO_E);
	glGenBuffers(3, VBO_E);

	glBindVertexArray(VAO_E);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_E[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->positions[0]) * model->positions.size(), &model->positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_E[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->normals[0]) * model->normals.size(), &model->normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_E[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->texcoords[0]) * model->texcoords.size(), &model->texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void textureInit() {
	LoadTexture(Umbreon_texture, "../resources/Umbreon.jpg");
	LoadTexture(Eevee_texture, "../resources/Eevee/Eevee.jpg");
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
	
	if(counter < 23) DrawUmbreon(Umbreonprogram);
	else if(counter>23 && counter<43) DrawUmbreon(Heartbeatprogram);
	else DrawUmbreon(Explosionprogram);
	DrawEevee(Eeveeprogram);
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

void idle() {
	glutPostRedisplay();
}

void DrawUmbreon(GLuint program)
{
	counter+=0.001;
	if(counter >43) explode+=0.001;
	glUseProgram(program);

	glUniform1f(glGetUniformLocation(program, "time"), counter);
	glUniform1f(glGetUniformLocation(program, "explode_time"), explode);
	
	glm::mat4 M(1.0f);

	if(counter>9){
		M = glm::translate(M, glm::vec3(2, 0, -2));
		M = glm::rotate(M, glm::radians(-30.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(-2, 0, 2));
	}

	if(counter>7){
		M = glm::translate(M, glm::vec3(back_Umbreon, 0, -back_Umbreon));
		if(back_Umbreon<=4) back_Umbreon+=0.01;
	}

	if(counter>5){
		M = glm::translate(M, glm::vec3(-front_Umbreon, 0, front_Umbreon));
		if(front_Umbreon<=4) front_Umbreon+=0.01;
	}

	if(counter>3){
		M = glm::translate(M, glm::vec3(2, 0, -2));
		M = glm::rotate(M, glm::radians(30.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(-2, 0, 2));
	}

	M = glm::translate(M, glm::vec3(2, 0, -2));
	M = glm::rotate(M, glm::radians(-30.0f), glm::vec3(0, 1, 0));
	GLuint ModelMatrixID = glGetUniformLocation(program, "M");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &M[0][0]);

	glm::mat4 V = getV();
	ModelMatrixID = glGetUniformLocation(program, "V");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &V[0][0]);

	glm::mat4 P = getP();
	ModelMatrixID = glGetUniformLocation(program, "P");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &P[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Umbreon_texture);
	glUniform1i(glGetUniformLocation(program, "texture"), 0);

	glBindVertexArray(VAO_U);
	glDrawArrays(GL_TRIANGLES, 0,  3*Umbreon->fNum);
	glBindVertexArray(0);
	glActiveTexture(0);
	glUseProgram(0);
}

void DrawEevee(GLuint program)
{
	counter+=0.001;
	if(counter >34) explode+=0.001;
	glUseProgram(program);

	glUniform1f(glGetUniformLocation(program, "time"), counter);
	glUniform1f(glGetUniformLocation(program, "explode_time"), explode);
	
	glm::mat4 M(1.0f);
	
	if(counter>80){
		M = glm::translate(M, glm::vec3(-2, 0, -2));
		M = glm::rotate(M, glm::radians(30.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(2, 0, 2));
	}

	if(counter>78){
		M = glm::translate(M, glm::vec3(-2, 0, -2));
		M = glm::rotate(M, glm::radians(-30.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(2, 0, 2));
	}

	if(counter>76){
		M = glm::translate(M, glm::vec3(-2, 0, -2));
		M = glm::rotate(M, glm::radians(30.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(2, 0, 2));
	}

	if(counter>74){
		M = glm::translate(M, glm::vec3(-2, 0, -2));
		M = glm::rotate(M, glm::radians(-30.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(2, 0, 2));
	}

	if(counter>72){
		M = glm::translate(M, glm::vec3(-2, 0, -2));
		M = glm::rotate(M, glm::radians(30.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(2, 0, 2));
	}

	if(counter>70){
		M = glm::translate(M, glm::vec3(-2, 0, -2));
		M = glm::rotate(M, glm::radians(-30.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(2, 0, 2));
	}

	if(counter>68){
		M = glm::translate(M, glm::vec3(-2, 0, -2));
		M = glm::rotate(M, glm::radians(15.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(2, 0, 2));
	}

	if(counter>21){
		M = glm::translate(M, glm::vec3(-2, -1, 2));
		M = glm::rotate(M, glm::radians(60.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(2, 1, -2));
	}

	if(counter>19){
		angle = 0;
		M = glm::translate(M, glm::vec3(-back_Eevee, -down_Eevee, back_Eevee));
		if(back_Eevee<=3) back_Eevee+=0.01;
		if(down_Eevee<=1) down_Eevee+=0.01;
	}

	if(counter>15){
		M = glm::translate(M, glm::vec3(2, -1, -2));
		M = glm::rotate(M, glm::radians(angle), glm::vec3(1, 0, -1));
		if(angle<2000) angle+=0.7;
		M = glm::translate(M, glm::vec3(-2, 1, 2));
	}

	if(counter>13){
		M = glm::translate(M, glm::vec3(front_Eevee, up_Eevee, -front_Eevee));
		if(front_Eevee<=3) front_Eevee+=0.01;
		if(up_Eevee<=1) up_Eevee+=0.01;
	}

	if(counter>11){
		M = glm::translate(M, glm::vec3(-2, -1, 2));
		M = glm::rotate(M, glm::radians(-60.0f), glm::vec3(1, 0, 1));
		M = glm::translate(M, glm::vec3(2, 1, -2));
	}
	
	M = glm::translate(M, glm::vec3(-2, -0.8, 2));
	M = glm::rotate(M, glm::radians(120.0f), glm::vec3(0, 1, 0));
	M = glm::rotate(M, glm::radians(90.0f), glm::vec3(1, 0, 0));
	M = glm::scale(M, glm::vec3(0.25, 0.25, 0.25));

	GLuint ModelMatrixID = glGetUniformLocation(program, "M");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &M[0][0]);

	glm::mat4 V = getV();

	if(counter>63){
		V = glm::translate(V, glm::vec3(camera_in, 0, camera_in));
		if(camera_in<=2) camera_in+=0.001;
	}

	if(counter>53){
		V = glm::rotate(V, glm::radians(-camera_angle), glm::vec3(0, 1, 0));
		if(camera_angle<80) camera_angle+=0.02;
	}
	ModelMatrixID = glGetUniformLocation(program, "V");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &V[0][0]);

	glm::mat4 P = getP();
	ModelMatrixID = glGetUniformLocation(program, "P");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &P[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Eevee_texture);
	glUniform1i(glGetUniformLocation(program, "texture"), 0);

	glBindVertexArray(VAO_E);
	glDrawArrays(GL_TRIANGLES, 0,  3*Eevee->fNum);
	glBindVertexArray(0);
	glActiveTexture(0);
	glUseProgram(0);
}

