//
//  main.cpp
//  MidPointCircle
//
//  Created by Rafiul Islam on 2/17/21.
//

#include <iostream>
#include <math.h>
#include <GLUT/GLUT.h>

using namespace::std;

int x_center, y_center, r;

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + x_center, y + y_center);
    glEnd();
}

void plotEightWay(int x,int y)
{
    plot(x, y);
    plot(x, -y);
    plot(-x, y);
    plot(-x, -y);
    plot(y, x);
    plot(-y, x);
    plot(y, -x);
    plot(-y, -x);
}

void midPointCircle()
{
    int x = 0;
    int y = r;
    float decision = 5/4 - r;
    plot(x, y);
    while (y > x)
    {
        if (decision < 0)
        {
            x++;
            decision += 2*x+1;
        }
        else
        {
            y--;
            x++;
            decision += 2*(x-y)+1;
        }
        plotEightWay(x, y);
    }
}

void display(void)
{
    midPointCircle();
    glFlush();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // multiply the current matrix by identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void takeInput()
{
    cout << "Enter Center Co-Ordinates (space separated int): ";
    cin >> x_center >> y_center;
    cout << "Enter Radius: ";
    cin >> r;
}

int main(int argc, char** argv) {
    takeInput();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Mid Point Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
