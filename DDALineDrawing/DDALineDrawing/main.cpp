//
//  main.cpp
//  DDALineDrawing
//
//  Created by Rafiul Islam on 2/17/21.
//

#include <iostream>
#include <math.h>
#include <GLUT/GLUT.h>

using namespace::std;

double xstart, ystart, xend, yend;


void drawPixelOnPoint(int x, int y)
{
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void lineDrawWithDDA()
{
    double dx=(xend-xstart);
    double dy=(yend-ystart);
    double steps;
    float xInc,yInc,x=xstart,y=ystart;
    steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
    xInc=dx/(float)steps;
    yInc=dy/(float)steps;
    drawPixelOnPoint(x, y);
    int k;
    for(k=0;k<steps;k++)
    {
        x+=xInc;
        y+=yInc;
        drawPixelOnPoint(round(x), round(y));
    }
}

void display(void)
{
    lineDrawWithDDA();
    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // multiply the current matrix by identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void takeInput()
{
    cout << "Enter Start Point (space separated int): ";
    cin >> xstart >> ystart;
    cout << "Enter End Point (space separated int): ";
    cin >> xend >> yend;
}

int main(int argc, char** argv)
{
    takeInput();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("DDA Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

