//
//  main.cpp
//  BresenhamsLineDrawing
//
//  Created by Rafiul Islam on 2/17/21.
//


#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<GLUT/GLUT.h>

using namespace::std;

int xstart, ystart, xend, yend;

void init()
{
    gluOrtho2D(0, 500, 0, 500);
}

void drawPixelOnPoint(int x, int y)
{
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void brasenhamLine(int xstart, int ystart, int xend, int yend)
{
    int dx = fabs(xend - xstart);
    int dy = fabs(yend - ystart);
    int twody = 2 * dy;
    int twodyminusdx = 2 * (dy - dx);
    int p = 2 * dy - dx;
    int x, y;
    if (xstart > xend)
    {
        x = xend;
        y = yend;
        xend = xstart;
    }
    else
    {
        x = xstart;
        y = ystart;
    }
    drawPixelOnPoint(x, y);
    while (x < xend)
    {
        x++;
        if (p < 0)
            p += twody;
        else
        {
            y++;
            p += twodyminusdx;
        }
        drawPixelOnPoint(x, y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    brasenhamLine(xstart, ystart, xend, yend);
    glEnd();
    glFlush();
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
    glutCreateWindow("Bresenham Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
