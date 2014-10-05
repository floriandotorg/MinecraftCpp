#pragma once

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elif WIN32
#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#endif
