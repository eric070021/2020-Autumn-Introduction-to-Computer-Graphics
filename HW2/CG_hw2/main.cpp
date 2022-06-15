#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <FreeImage.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stb_image.h>
#include <shader.h>
#include <Object.h>

using namespace std;

void shaderInit();
void bindbufferInit();
void textureInit();
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void DrawBasis();
void DrawUmbreon();
void LoadTexture(unsigned int &, const char *);

GLuint vboName;
GLuint program;
GLuint VAO, VBO[3];
unsigned int basistexture, modeltexture;
int windowSize[2] = {600, 600};
float angle = 0.0f;
GLfloat scale = 1;
GLfloat bonus[16]={1,0,0,0,
                     0,1,0,0,
                     0,0,1,0,
                     0,0,0,1};

Object *model = new Object("../resources/UmbreonHighPoly.obj");

//Storing vertex datas that will be sent to shader
class VertexAttribute {
public:
	GLfloat position[3];
  GLfloat normal[3];
  GLfloat texcoord[2];
	void setPosition(float x, float y, float z) {
		position[0] = x;
		position[1] = y;
		position[2] = z;
	};
  void setNormal(float x, float y, float z) {
		normal[0] = x;
		normal[1] = y;
		normal[2] = z;
	};
  void setTexture(float x, float y) {
		texcoord[0] = x;
		texcoord[1] = y;
	};
};

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(windowSize[0], windowSize[1]);
  glutInitWindowPosition(0, 0);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("hw2");

  glewInit();
  shaderInit();
  bindbufferInit();
  textureInit();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}

void shaderInit() {
  //// TODO: ////
  GLuint vert = createShader("../shaders/vertexShader.vert", "vertex");
  GLuint frag = createShader("../shaders/fragmentShader.frag", "fragment");
  program = createProgram(vert, frag);
  
}

void bindbufferInit() {
  //// TODO: ////
  //
  //	 Hint:
  // 1. Setup VAO
  // 2. Setup VBO of vertex positions, normals, and texcoords
  //Generate a new buffer object
  int verticenum = (model->positions.size()/3);
	glGenBuffers(1, &vboName);
	glBindBuffer(GL_ARRAY_BUFFER, vboName);

	//Copy vertex data to the buffer object
	VertexAttribute vertices[verticenum];
  for(int i=0; i < verticenum ; i++){
	  vertices[i].setPosition(model->positions[i*3], model->positions[i*3 +1], model->positions[i*3 +2]);
  }
  for(int i=0; i < verticenum ; i++){
	  vertices[i].setNormal(model->normals[i*3], model->normals[i*3 +1], model->normals[i*3 +2]);
  }
  for(int i=0; i < verticenum ; i++){
	  vertices[i].setTexture(model->texcoords[i*2], model->texcoords[i*2 +1]);
  }
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * verticenum, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, position)));
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, normal)));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, texcoord)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void textureInit() {
  LoadTexture(basistexture, "../resources/basis.jpg");
  LoadTexture(modeltexture, "../resources/Umbreon.jpg");
}

void display() {
  //Clear the buffer
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // viewport transformation
  glViewport(0, 0, windowSize[0], windowSize[1]);

  // projection transformation
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) windowSize[0] / (GLfloat) windowSize[1], 1.0, 1000.0);

  // viewing and modeling transformation
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(7.5, 5.0, 7.5,// eye
            0.0, 0.0, 0.0,     // center
            0.0, 1.0, 0.0);    // up
  glRotated(angle, 0, 1, 0);
  /**************trsmit data to vert and fragment shader*********/

  glPushMatrix();
  glTranslated(0, 1.3, 0);
  GLfloat project_mat[16];
	GLfloat model_mat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, project_mat);
	glGetFloatv(GL_MODELVIEW_MATRIX, model_mat);
  glPopMatrix();

	glUseProgram(program);

  glBindBuffer(GL_ARRAY_BUFFER, vboName);

  GLint project_Loc = glGetUniformLocation(program, "Projection");
	GLint model_Loc = glGetUniformLocation(program, "ModelView");
  GLint bonus_Loc = glGetUniformLocation(program, "bonus");
	//input the modelview matrix into vertex shader
	glUniformMatrix4fv(project_Loc, 1, GL_FALSE, project_mat);
	//input the rotation matrix into vertex shader
	glUniformMatrix4fv(model_Loc, 1, GL_FALSE, model_mat);
  glUniformMatrix4fv(bonus_Loc, 1, GL_FALSE, bonus);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, modeltexture);
  GLint texLoc = glGetUniformLocation(program, "Texture");
  glUniform1i(texLoc, 0);
  /* draw objects */
  glDrawArrays(GL_QUADS, 0, 4 * model->fNum);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glActiveTexture(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glUseProgram(0);
  /*************************************************************/
  //DrawUmbreon();

  DrawBasis();
  angle += 0.03;
  glutPostRedisplay();
  glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
  windowSize[0] = w;
  windowSize[1] = h;
}

void keyboard(unsigned char key, int x, int y)
{
  int flag = (bonus[0] < 0 ?  -1 : 1);
	if(key == '1'){
		bonus[0] = flag*1;
    bonus[5] = flag*1;
    bonus[10] = flag*1;
	}
  else if(key == '2'){
		bonus[0] = flag*2;
    bonus[5] = flag*2;
    bonus[10] = flag*2;
  }
  else if(key == '3'){
		bonus[0] = flag*3;
    bonus[5] = flag*3;
    bonus[10] = flag*3;
  }
  else if(key == '4'){
		bonus[0] = flag*4;
    bonus[5] = flag*4;
    bonus[10] = flag*4;
  }
  else if(key == '5'){
		bonus[0] = flag*5;
    bonus[5] = flag*5;
    bonus[10] = flag*5;
  }
  else if(key == ' '){
		bonus[0] = -bonus[0];
    bonus[5] = -bonus[5];
    bonus[10] = -bonus[10];
  }
}

void LoadTexture(unsigned int &texture, const char *tFileName) {
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(tFileName, &width, &height, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);
}

void DrawBasis() {
  /* declaration of parameters */
  GLUquadricObj *disk = gluNewQuadric();
  float edge = 20;
  float radius = 4;
  float pi = 3.1415926;
  float height = 4;
  int tc = 0;

  /* start drawing cylinder */
  glActiveTexture(GL_TEXTURE0);
  glBindTexture (GL_TEXTURE_2D, basistexture);
    glBegin(GL_QUAD_STRIP);
        for (float i = 0; i <= 2 * pi; i += (2*pi/(float)edge)){
            glTexCoord2f(0.0, tc);
            glVertex3f(radius * cos(i), 0, radius * sin(i));
            glTexCoord2f(1.0, tc );
            glVertex3f(radius * cos(i), -height, radius * sin(i));
            tc = (tc == 0 ? 1 : 0);
        }      
        glTexCoord2f( 0.0, tc );
        glVertex3f(radius, 0, 0);
        glTexCoord2f(1.0, tc );
        glVertex3f(radius, -height, 0);
    glEnd();
  //glBindTexture (GL_TEXTURE_2D, 0);
  //glActiveTexture(0); 
  glPopMatrix();
  /* the lower disk*/
  glPushMatrix();
  glTranslated(0, -height, 0);
  glRotated(90,1,0,0);
	gluDisk(disk, 0, radius, 20, 1);
	glPopMatrix();
  /* the upper disk */
  glPushMatrix();
  //glTranslated(0, height/2, 0);
  glRotated(270,1,0,0);
	gluDisk(disk, 0, radius, 20, 1);
	glPopMatrix();
}
