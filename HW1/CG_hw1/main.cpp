
#include <GL/freeglut.h>
#include "Object.h"
#include <math.h>

int windowSize[2];
int speed=1;
void light();
void display();
void reshape(GLsizei, GLsizei);
void LoadModel(Object*);
void DrawBasis();
void keyboard(unsigned char key, int x, int y);
GLfloat angle=0;

Object* elephant = new Object("../object/elephant.obj");
Object* cube = new Object("../object/cube.obj");
Object* teapot = new Object("../object/teapot.obj");
GLUquadric* twenty=gluNewQuadric();


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("風火輪");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void light()
{
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = { 50.0, 75.0, 80.0, 1.0 };
	glShadeModel(GL_SMOOTH);
	// z buffer enable
	glEnable(GL_DEPTH_TEST);
	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.6, 0.9);

	///TO DO Enable DepthTest
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	///
	
	///TO DO: add lighting, Viewport Matrix, Projection Matrix, ModelView Matrix
	//Viewport Matrix
	glViewport(0, 0, windowSize[0], windowSize[1]);
	//Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,(GLfloat)windowSize[0]/windowSize[1],1,1000);
	//Modelview Matrix
	//glPushMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20,20,20,0,0,0,0,1,0);
	//glPopMatrix();
	///TO DO: add model, translate, rotate, scale
	light();
	glRotated(angle*speed,0,1,0);
	glPushMatrix();
	glTranslated(-3,0,3);
	LoadModel(teapot);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0.5,0);
	glTranslated(3,0,-3);
	glRotated(3*angle,0,1,0);
	glTranslated(-2,0,-2);
	glScaled(0.5,0.5,0.5);
	LoadModel(cube);
	glPopMatrix();

	glPushMatrix();
	glTranslated(3,0,-3);
	glRotated(3*angle,0,1,0);
	LoadModel(elephant);
	glPopMatrix();

	glPushMatrix();
	glRotated(270,1,0,0);
	gluDisk(twenty, 0, 10, 20, 1);
	glPopMatrix();
	glRotated(90,1,0,0);
	gluCylinder(twenty, 10, 10, 5, 20, 1);
	
	angle+=1;
	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

void LoadModel(Object* Model)
{
	for (size_t i = 0; i < Model->fNum; ++i)
	{
		glBegin(GL_TRIANGLES);
		for (size_t j = 0; j < 3; ++j)
		{
			glNormal3fv(Model->nList[Model->faceList[i][j].nIndex].ptr);
			glVertex3fv(Model->vList[Model->faceList[i][j].vIndex].ptr);
		}
		glEnd();
	}
}

void DrawBasis()
{
	///TO DO: draw basis
	///
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == ' '){
		if(speed<=1000) speed+=100;
		else speed=1;
	}
}