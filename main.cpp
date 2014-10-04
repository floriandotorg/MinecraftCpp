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
//static GLfloat whiteLight[3] = {1.0f, 1.0f, 1.0f};

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
    
    glRotatef( 10, 1.0, 0.0, 0.0 );
    glRotatef( 10, 0.0, 1.0, 0.0 );
    
    //Multi-colored side - FRONT
    glBegin(GL_POLYGON);
    
    glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
    glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
    glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
    glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple
    
    glEnd();
    
    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 1.0 );
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
    
    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
    
    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    
    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
    
    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    
    glFlush();
    glutSwapBuffers();
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
    
    glEnable(GL_DEPTH_TEST);
    
//    glEnable(GL_CULL_FACE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glClearColor(0.5, 0.69, 1.0, 1);
    
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
