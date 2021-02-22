//
//  main.cpp
//  CohenSutherlandLineClipping
//
//  Created by Rafiul Islam on 2/22/21.
//

#include<iostream>
#include<GLUT/GLUT.h>

using namespace::std;

double xmin=50,ymin=50,xmax=100,ymax=100;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;

const int Right=8;
const int Left=2;
const int Top=4;
const int Bottom=1;

int xstart, ystart, xend, yend;

int compute(double x,double y)
{
    int code=0;
    
    if(y>ymax)
    {
        code|=Top;
    }
    else if(y<ymin)
    {
        code|=Bottom;
    }
    if(x>xmax)
    {
        code|=Bottom;
    }
    if(y<ymin)
    {
        code|=Left;
    }
    return code;
}

void cohenSutherland(double x0,double y0,double x1,double y1)
{
    int outcode0,outcode1,outcodeout;
    int accept=0,done=0;
    outcode0=compute(x0,y0);
    outcode1=compute(x1,y1);
    do
    {
        if(!(outcode0|outcode1))
        {
            accept=1;
            done=1;
        }
        else if( outcode0 &  outcode1)
        {
            done = 1;
        }
        else
        {
            double x,y;
            outcodeout=outcode0?outcode0:outcode1;
            if(outcodeout & Top)
            {
                x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
                y=ymax;
            }
            else if(outcodeout & Bottom)
            {
                x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
                y=ymin;
            }
            
            else if(outcodeout & Right)
            {
                y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
                x=xmax;
            }
            else
            {
                y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
                x=xmin;
            }
            if(outcodeout==outcode0)
            {
                x0=x;
                y0=y;
                outcode0=compute(x0,y0);
            }
            else
            {
                x1=x;
                y1=y;
                outcode1=compute(x1,y1);
            }
        }
    }while(!done);
    if(accept)
    {
        double sx=(xvmax-xvmin)/(xmax-xmin);
        double sy=(yvmax-yvmin)/(ymax-ymin);
        double vx0=xvmin+(x0-xmin)*sx;
        double vy0=yvmin+(y0-ymin)*sy;
        double vx1=xvmin+(x1-xmin)*sx;
        double vy1=yvmin+(y1-ymin)*sy;
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
        glEnd();
        glColor3f(0,0,1);
        glBegin(GL_LINES);
        glVertex2d(vx0,vy0);
        glVertex2d(vx1,vy1);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2d(xstart,ystart);
    glVertex2d(xend,yend);
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();
    cohenSutherland(xstart,ystart,xend,yend);
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

int main(int argc, char **argv)
{
    takeInput();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Cohen-Sutherland Line Clipping Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
