//
//  main.cpp
//  MinecraftCpp
//
//  Created by florian on 04.10.14.
//  Copyright (c) 2014 florian. All rights reserved.
//

#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

static int win = 0;
GLuint Texture;
GLfloat rotate_x;

GLuint loadBMP_custom(const char * imagepath)
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath, "rb");
	if (!file)                              { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54){ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M'){
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}

void CreateGlutWindow()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition (10, 10);
    glutInitWindowSize (512, 512);
    win = glutCreateWindow ("");
}

void idle()
{
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, Texture);
	
	glRotatef( rotate_x, 1.0, 0.0, 0.0);
    glRotatef( 45, 0.0, 1.0, 0.0 );
    
    //Multi-colored side - FRONT
    glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.0);
    /*glColor3f( 1.0, 0.0, 0.0 );*/     glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
	glTexCoord2f(0.25, 0.25);
    /*glColor3f( 0.0, 1.0, 0.0 );*/     glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
	glTexCoord2f(0.0, 0.25);
    /*glColor3f( 0.0, 0.0, 1.0 );*/     glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
	glTexCoord2f(0.0, 0.0);
    /*glColor3f( 1.0, 0.0, 1.0 );*/     glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple
    glEnd();
    
    // White side - BACK
    glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 0.25);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    
    // Purple side - RIGHT
    glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0, 0.25);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5, -0.5, 0.5);
    glEnd();
    
    // Green side - LEFT
    glBegin(GL_POLYGON);
    //glColor3f(   0.0,  1.0,  0.0 );
	glTexCoord2f(0.25, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 0.25);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
    
    // Blue side - TOP
    glBegin(GL_POLYGON);
	//glColor3f(   0.0,  0.0,  1.0 );
	glTexCoord2f(0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.5, 0.25);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.25, 0.0);
	glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    
    // Red side - BOTTOM
    glBegin(GL_POLYGON);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.25, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 0.25);
	glVertex3f(-0.5, -0.5, -0.5);
    glEnd();
    
    glFlush();
    glutSwapBuffers();
}

void rotate(int)
{
	rotate_x += 2;
	glutPostRedisplay();
	glutTimerFunc(10, rotate, 0);
}

void CreateGlutCallbacks()
{
    glutDisplayFunc(display);
    glutIdleFunc(idle);
}

void setupFog()
{
    glEnable(GL_FOG);
    // Set the fog color.
    const GLfloat a[] = {0.5, 0.69, 1.0, 1};
    glFogfv(GL_FOG_COLOR, a);
    // Say we have no preference between rendering speed and quality.
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    // Specify the equation used to compute the blending factor.
    glFogi(GL_FOG_MODE, GL_LINEAR);
    // How close and far away fog starts and ends. The closer the start and end,
    // the denser the fog in the fog range.
    glFogf(GL_FOG_START, 20.0);
    glFogf(GL_FOG_END, 60.0);
}

void InitOpenGL()
{
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(90.0, 1.0, 0.1, 100);
//    glMatrixMode(GL_MODELVIEW);
//    
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_TEXTURE_2D);
////    loadTextures();
//    
//    glEnable(GL_NORMALIZE);
//    glShadeModel(GL_SMOOTH);
//    glEnable(GL_LIGHTING);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
//    glEnable(GL_LIGHT0);
    
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
    
//    glEnable(GL_CULL_FACE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glClearColor(0.5, 0.69, 1.0, 1);

	Texture = loadBMP_custom("texture.bmp");
	rotate_x = 0;
	rotate(0);
    
//    setupFog();
}

void ExitGlut()
{
    glutDestroyWindow(win);
    exit(0);
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    
    CreateGlutWindow();
    CreateGlutCallbacks();
    InitOpenGL();
    
    glutMainLoop();
    
    ExitGlut();
    
    return 0;
}
