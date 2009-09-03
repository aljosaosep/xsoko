/*
 * codename: xSoko
 * Copyright (C) Aljosa Osep, Jernej Skrabec, Jernej Halozan 2008 <aljosa.osep@gmail.com, jernej.skrabec@gmail.com, jernej.halozan@gmail.com>
 * 
 * xSoko project is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * xSoko project is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * File:   test.cpp
 * Author: martin
 *
 * Test program for Md2model class.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#include <GL/gl.h>
#include <GL/glut.h>

#include "md2model.h"

using namespace PacGame::Md2Format;

double last_time = 0;
double current_time = 0;
double current_frame = 0;

double angle_x = 0, angle_y = -90, dist = 100;

Md2Model* model;

void Display();
void Keyboard(unsigned char key, int x, int y);
void Reshape (int w, int h);

int main(int argc, char** args)
{
	// read the file and print out file information
	if(argc != 2)
	{
		cout<<"Pass md2 file name as argument."<<endl;
		return 1;
	}
	ifstream file(args[1], ios_base::in | ios_base::binary);
	model = new Md2Model(file);
	model->FileInformation(cout);
	
	// init glut and openGL
	glutInit (&argc, args);
  	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  	glutInitWindowSize (640, 480);
  	glutCreateWindow ("MD2 Model");

	GLfloat lightpos[] = { 5.0f, 10.0f, 0.0f, 1.0f };

	/* Initialize OpenGL context */
	glClearColor (0, 0, 0, 1.0f);
	glShadeModel (GL_SMOOTH);

	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);

	glLightfv (GL_LIGHT0, GL_POSITION, lightpos);
	
	glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glutReshapeFunc (Reshape);
	glutDisplayFunc (Display);
	glutKeyboardFunc (Keyboard);

	glutMainLoop ();

	
	return 0;
}

void Keyboard(unsigned char key, int x, int y)
{
  /* Escape */
  	if (key == 27)
  	{
  	delete model;
    	exit (0);
	}else
	if(key == 'a')
	{
		angle_x += 1;
	}else
	if(key == 'd')
	{
		angle_x -= 1;
	}else
	if(key == 'w')
	{
		angle_y += 1;
	}else
	if(key == 's')
	{
		angle_y -= 1;
	}else
	if(key == 'q')
	{
		dist += 1;
	}else
	if(key == 'e')
	{
		dist -= 1;
	}
}

void Display()
{
  	last_time = current_time;
	current_time = (double)glutGet (GLUT_ELAPSED_TIME) / 1000.0;
  	double diff_time = current_time - last_time;
  	
  	current_frame += diff_time*10;
  	
  	/*if(diff_time > 0.1)
  	{
  		last_time = current_time;
  		current_frame += 1;
	}*/
  		
  	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glLoadIdentity ();
  	
	if(current_frame > double(model->GetNumberOfFrames()-1))
		current_frame -= model->GetNumberOfFrames()-1;
		
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glTranslatef(0,0,-dist);
  	glRotatef (-90.0f, 0.0, 0.0, 1.0);
	glRotatef(angle_x, 1,0,0);
	glRotatef(angle_y, 0,1,0);
	//gluLookAt(50,50,0,0,0,0,0,1,0);
	
	//glTranslatef(0,0,3);
  	//glRotatef (-90.0f, 1.0, 0.0, 0.0);
	
	glColor3f(1,0,0);
	//glutSolidCube(1);
	model->DrawFrame(current_frame);
	glPopMatrix();
	
	glutSwapBuffers ();
	glutPostRedisplay();
}

void Reshape (int w, int h)
{
  if (h == 0)
    h = 1;

  glViewport (0, 0, (GLsizei)w, (GLsizei)h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (45.0, w/(GLdouble)h, 0.1, 1000.0);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}
