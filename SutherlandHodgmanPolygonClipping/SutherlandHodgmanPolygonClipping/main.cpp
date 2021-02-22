//
//  main.cpp
//  SutherlandHodgmanPolygonClipping
//
//  Created by Rafiul Islam on 2/22/21.
//

// Polygon clipping.cpp: Define the entry point of the console application.
//

#include<GLUT/GLUT.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace::std;

typedef struct
{
    float x, y;
}wcPt2D;

typedef enum
{
    Left, Right, Bottom, Top
}Boundary;

int inside(wcPt2D p, Boundary b, wcPt2D wMin, wcPt2D wMax)
{
    switch (b)
    {
    case Left:
        if (p.x<wMin.x) return (false);
        break;
    case Right:
        if (p.x>wMax.x) return (false);
        break;
    case Bottom:
        if (p.y<wMin.y) return (false);
        break;
    case Top:
        if (p.y>wMax.y) return (false);
        break;
    }
    return true;
}

int cross(wcPt2D p1, wcPt2D p2, Boundary b, wcPt2D wMin, wcPt2D wMax)
{
    if (inside(p1, b, wMin, wMax) == inside(p2, b, wMin, wMax))
        return (false);
    else
        return true;
}

wcPt2D intersect(wcPt2D p1, wcPt2D p2, Boundary b, wcPt2D    wMin, wcPt2D wMax)
{
    wcPt2D iPt;
    float m;
    if (p1.x != p2.x) m = (p2.y - p1.y) / (p2.x - p1.x);
    switch (b){
    case Left:
        iPt.x = wMin.x;
        iPt.y = p2.y + (wMin.x - p2.x)*m;
        break;
    case Right:
        iPt.x = wMax.x;
        iPt.y = p2.y + (wMax.x - p2.x)*m;
        break;
    case Bottom:
        iPt.y = wMin.y;
        if (p1.x != p2.x)iPt.x = p2.x + (wMin.y - p2.y) / m;
        else iPt.x = p2.x;
        break;
    case Top:
        iPt.y = wMax.y;
        if (p1.x != p2.x) iPt.x = p2.x + (wMax.y - p2.y) / m;
        else iPt.x = p2.x;
        break;
    }
    return iPt;
}
int edgeCliper(Boundary b, wcPt2D wMin, wcPt2D wMax, wcPt2D *pIn, int cnt, wcPt2D *pOut)
{
    wcPt2D s;
    int i, Outcnt = 0;
    s = pIn[0];
    for (i = 1; i <= cnt; i++)
    {
        if (!inside(s, b, wMin, wMax) && inside(pIn[i], b, wMin, wMax))
        {
            pOut[Outcnt] = intersect(s, pIn[i], b, wMin, wMax);
            Outcnt++;
            pOut[Outcnt] = pIn[i];
            Outcnt++;
        }
        else if (inside(s, b, wMin, wMax) && inside(pIn[i], b, wMin, wMax))
        {
            pOut[Outcnt] = pIn[i];
            Outcnt++;
        }
        else if (inside(s, b, wMin, wMax) && (!inside(pIn[i], b, wMin, wMax)))
        {
            pOut[Outcnt] = intersect(s, pIn[i], b, wMin, wMax);
            Outcnt++;
        }
        s = pIn[i];
    }
    return (Outcnt);
}

void ClipPolygonSuthHodg(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    int i, cnt, Outcnt, b;
    wcPt2D points[7] = { { -300, -100 },{ -300, 150 }, { -100, 150 }, { 100, 100 }, { 100, 0 }, { 0, -100 },{ -300, -100 }};
    cnt = 7;
    wcPt2D pOut[28], pIn[28];
    wcPt2D wMin = { -200, 0 }, wMax = { 50, 200 };
    for (i = 0; i<4 * cnt; i++)
    {
        pIn[i].x = 0.0;
        pIn[i].y = 0.0;
        pOut[i].x = 0.0;
        pOut[i].y = 0.0;
    }
    for (i = 0; i <= cnt; i++) pIn[i] = points[i];
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(wMin.x, wMin.y);
    glVertex2f(wMax.x, wMin.y);
    glVertex2f(wMax.x, wMax.y);
    glVertex2f(wMin.x, wMax.y);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i<cnt; i++)
        glVertex2f(pIn[i].x, pIn[i].y);
    glEnd();
    for (b = 0; b<4; b++)
    {
        Outcnt = edgeCliper(Boundary(b), wMin, wMax, pIn, cnt, pOut);
        for (i = 0; i<Outcnt; i++)
            pIn[i] = pOut[i];
        pIn[Outcnt] = pOut[0];
        cnt = Outcnt;
    }
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i<cnt; i++)
        glVertex2f(pOut[i].x, pOut[i].y);
    glEnd();
    glFlush();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400.0, 400.0, -300.0, 300.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping Algorithm");
    init();
    glutDisplayFunc(ClipPolygonSuthHodg);
    glutMainLoop();
    return 0;
}
