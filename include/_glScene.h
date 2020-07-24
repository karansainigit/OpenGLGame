#ifndef _GLSCENE_H
#define _GLSCENE_H

#include <windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

class _glScene
{
    public:
        _glScene();                               //constructor
        virtual ~_glScene();                      //destructor
        GLint initGL();                           //initialize OpenGL
        GLint drawScene();                        //renderer
        GLvoid reSizeScene(GLsizei, GLsizei);     //screen size changes
        int winMsg (HWND, UINT, WPARAM, LPARAM);  //callback of inputs
};

#endif // _GLSCENE_H
