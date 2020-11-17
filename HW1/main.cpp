#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "Object.h"
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>

int windowSize[2];

void light();
void display();
void reshape(GLsizei, GLsizei);
void LoadModel(Object*);
void DrawBasis(int n);
void keyboard(unsigned char key, int x, int y);

//mod, ../=>./
// use ../ when building the first time..?
Object* elephant = new Object("../object/elephant.obj");
Object* cube = new Object("../object/cube.obj");
Object* teapot = new Object("../object/teapot.obj");

//view params
float position[3] = {20.0, 20.0, 20.0};
float center[3] = {0.0, 0.0, 0.0};
float upf[3] = {0.0, 1.0, 0.0};

int angle1, angle2;
int d1 = 1, d2 = 3;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //mac mod
	glutCreateWindow("HW1");
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
	//for(int i = 0; i < 4; i++) light_specular[i] *=5;
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
	///TO DO Enable DepthTest
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	///
	///TO DO: add lighting, Viewport Matrix, Projection Matrix, ModelView Matrix
	//vierport
	glViewport(0, 0, windowSize[0], windowSize[1]);
	// perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, GLfloat(windowSize[0]*1.0/windowSize[1]), 1.0, 1000.0);
	//viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		position[0], position[1], position[2],//eye
		center[0], center[1], center[2],//center
		upf[0], upf[1], upf[2]//up
	);
	// lighting
	light();
	// no normalization
	///TO DO: add model, translate, rotate, scale
	glPushMatrix();
	glRotatef(angle1, 0, 1, 0);

	glPushMatrix();
	//glTranslatef(0,0,0);
	DrawBasis(20); //20 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3,0,-3);
	glRotatef(angle2, 0, 1, 0);
	LoadModel(elephant);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,0,-2);
	glScalef(0.5, 0.5, 0.5);
	LoadModel(cube);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3,0,3);
	glRotatef(angle2, 0, 1, 0);
	LoadModel(teapot);
	glPopMatrix();

	glPopMatrix();

	angle1 += d1;
	angle2 += d2;

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

void DrawBasis(int n)
{
	///TO DO: draw basis

	//declare
	const double PI = atan(1.0)*4;
	/// top
	glBegin(GL_POLYGON);
	//glNormal3f(0, 1, 0);
	for(int i = 0; i < n; i++)
	{
		glNormal3f(0, 1, 0);
		glVertex3f(10*cos(2*PI*i/double(n)), 0, 10*sin(2*PI*i/double(n)));
	}
	glEnd();
	// btm
	glBegin(GL_POLYGON);
	//glNormal3f(0, -0.5, 0);
	for(int i = 0; i < n; i++)
	{
		glNormal3f(0, -1, 0); //per point normal
		glVertex3f(10*cos(2*PI*i/double(n)), -5, 10*sin(2*PI*i/double(n)));
	}
	glEnd();

	/// quad strip for side
	/*
	glBegin(GL_QUAD_STRIP);
	for(int i = 0; i <= n; i++) // <= instead of = because is not loop
	{
		glNormal3f(10*cos(2*PI*i/double(n)), 0, 10*sin(2*PI*i/double(n)));
		glVertex3f(10*cos(2*PI*i/double(n)), 0, 10*sin(2*PI*i/double(n)));
		glNormal3f(10*cos(2*PI*i/double(n)), 0, 10*sin(2*PI*i/double(n)));
		glVertex3f(10*cos(2*PI*i/double(n)), -5, 10*sin(2*PI*i/double(n)));
	}
	glEnd();
	*/
	glBegin(GL_QUADS);
	for(int i = 0; i < n; i++)
	{
		//0
		glNormal3f(10*cos(2*PI*i/double(n)), .5, 10*sin(2*PI*i/double(n)));
		glVertex3f(10*cos(2*PI*i/double(n)), 0, 10*sin(2*PI*i/double(n)));
		//1
		i++;
		glNormal3f(10*cos(2*PI*i/double(n)), .5, 10*sin(2*PI*i/double(n)));
		glVertex3f(10*cos(2*PI*i/double(n)), 0, 10*sin(2*PI*i/double(n)));
		//2
		glNormal3f(10*cos(2*PI*i/double(n)), .5, 10*sin(2*PI*i/double(n)));
		glVertex3f(10*cos(2*PI*i/double(n)), -5, 10*sin(2*PI*i/double(n)));
		//3
		i--;
		glNormal3f(10*cos(2*PI*i/double(n)), .5, 10*sin(2*PI*i/double(n)));
		glVertex3f(10*cos(2*PI*i/double(n)), -5, 10*sin(2*PI*i/double(n)));
	}
	glEnd();

}

void keyboard(unsigned char key, int x, int y)
{
	/// TO DO: Set the keyboard control
	///	
}