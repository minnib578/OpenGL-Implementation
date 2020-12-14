#include "Reader.h"
#include <fstream>
#include <iostream>
#include "utils.h"
#include<vector>
#include "Vector3f.h"
#include "camera.h"
using namespace std;


string filePath = "cactus.obj";                             
Reader Model = Reader(filePath);                           
string primitive = "TRIANGLE";                              
string colors = "R";                                        
GLenum mode = GL_CCW;                                       
int old_x= 1;                                               
int old_y= 1;
bool stop = false;                             
GLfloat near_plane = 1.0;                                    
GLfloat far_plane = 50.0;                                   
bool reset = true;                                           
float w = 500;                                               
float h = 500;                                               
bool change = false;                                         
Camera CAM;

void NEW() {     
	string path = New_path();                                 	
	Model = Reader(path);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (colors == "R") {glColor3f(1.0f,0.0f,0.0f);}                                      // change model rendering color
	else if(colors == "G"){ glColor3f(0.0f, 1.0f, 0.0f); }
	else if (colors=="B"){ glColor3f(0.0f, 0.0f, 1.0f); }
	else{glColor3ub(rand() % 255, rand() % 255, rand() % 255);}
	  
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  
	float scale = Model.bounding;                                                      // choose propertive camera coordinate according to the new model dimension
	if (change==true||reset==true) {                                                   // reset the camera to original point when change file and reset 
		CAM.eye = vector3f(0, 0, scale);
		CAM.at = vector3f(0, 0, -1);
		CAM.up = vector3f(0, 1, 0);
		reset = false;
		change = false;
	}
	gluLookAt(CAM.eye.x, CAM.eye.y, CAM.eye.z, CAM.eye.x + CAM.at.x, CAM.eye.y + CAM.at.y, CAM.eye.z + CAM.at.z, CAM.up.x, CAM.up.y, CAM.up.z);
	
	if (primitive == "POINT") {                                                      // rendering the object using different kinds of primitives
		Model.Draw_POINT();
	}
	else if(primitive == "LINE") {
		Model.Draw_LINE();
	}
	else {
		Model.Draw_TRIANGLE();
	}     
	
	glEnable(GL_CULL_FACE);                                                         // rendering objects whose polygon vertices were defined using CW (clockwise) and CCW (counter-clockwise) orientation
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_FILL);
	glFrontFace(mode);
	glFlush();
	glutSwapBuffers();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, w/h, near_plane, far_plane);
	glMatrixMode(GL_MODELVIEW);
}

void MyReshape(int width, int height)                                            
{
	glViewport(0, 0, width, height);
	w = width;
	h = height;
	
}

void myIdle()
{
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)                                                              
{
	if (key == 'q' || key == 'Q') exit(0);

	// interactively read the model
	if (key == '0') Model = Reader("bunny.obj");
	if (key == '1') Model = Reader("cactus.obj");
	

	// movement
	if (key == 'z' || key == 'Z')   CAM.F_B(0.1f);      //near
	if (key == 'w' || key == 'W')   CAM.F_B(-0.1f);    // far
	if (key == 'A' || key == 'a')   CAM.R_L(0.1f);     //left
	if (key == 's' || key == 'S')   CAM.R_L(-0.1f);    //right
	if (key == 'u' || key == 'U')   CAM.U_D(-0.1f);       //UP
	if (key == 'd' || key == 'D')   CAM.U_D(0.1f);        //Down
	
	//Reset to original window
	if (key == 'r' || key == 'R')   reset = true;


	// the near and far clipping planes
	if (key == 'n')   near_plane += 0.2;
	if (key == 'N')
	{
		near_plane -= 0.2;
		if (near_plane <= 0.1) {
			near_plane = 0.1;
		}
	}
	if (key == 'f')   far_plane += 1;
	if (key == 'F') {
		far_plane -= 0.2;
		cout << far_plane << endl;
	    if (far_plane <= 0.1) {
		far_plane = 0.1;
		
	}
	}


	// change of colors (R, G, B)
	if (key == '6')  colors = "R";
	if (key == '7')  colors = "G";
	if (key == '8')  colors = "B";
	if (key == '9')  colors = "RANDOM";

	// CW (clockwise) and CCW
	if (key == 'c' || key == 'C')   mode = GL_CW;
	if (key == 'l' || key == 'L')   mode = GL_CCW;

	//primitives rendering:point,line,triangle

	if (key == '3')   primitive = "POINT";
	if (key == '4')   primitive = "LINE";
	if (key == '5')   primitive = "TRIANGLE";

	// new model file through the user interface 
	if (key == '2')  NEW();
	if (key == '0' || key == '1' || key == '2') change = true;

	
	if (key == ' ') stop = !stop;
	if (stop)
		glutIdleFunc(NULL);
	else
		glutIdleFunc(myIdle);
}

void Mouse(int button, int state, int x, int y)                                                              
{
	if (state == GLUT_DOWN) {
		old_x = x; 
		old_y = y;
	}
}


void Motion(int x, int y)
{
	float dx = x - old_x;
	float dy = y - old_y;
	CAM.Y_axis(dx / 100);
	CAM.X_axis(dy / 100);
	old_x = x;
	old_y = y;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitContextFlags(GLUT_COMPATIBILITY_PROFILE);
	glutCreateWindow("Read_3DModel");
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(display);
	glutIdleFunc(myIdle);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(keyboard);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
