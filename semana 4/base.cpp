#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void inicio(void);
void display(void);
void myreshape(int, int);
void abasico(int, int, int, int);
void ingresoDatos(void);

int px0, py0, px1, py1;

int main(int argc, char **argv)
{
    ingresoDatos();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(200, 200);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Algoritmos de primitivas graficas");
    inicio();
    glutDisplayFunc(display);
    glutReshapeFunc(myreshape);
    glutMainLoop();
    return 0;
}

void inicio(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // parametros: rojo, amarillo y azul, el cuarto es el parametro alpha
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();     // salva el estado actual de la matriz
    glColor3f(0, 0, 1); // Azul
    glPointSize(2);     // Fije el grosor de pixel = 2
    abasico(px0, py0, px1, py1);
    glPopMatrix(); // recupera el estado del matriz
    glFlush();
}

void myreshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void abasico(int x0, int y0, int x1, int y1)
{
    int x;
    float dx, dy, m, b, y;
    dx = x1 - x0;
    dy = y1 - y0;
    m = dy / dx;
    b = y0 - m * x0;
    y = y0;
    glBegin(GL_POINTS);
    for (x = x0; x <= x1; x++)
    {
        y = m * x + b;
        cout << x << " " << y << " " << (int)ceil(y - 0.5) << "\n";
        glVertex2f(x, (int)ceil(y - 0.5));
    }
    glEnd();
}

// opcional
void ingresoDatos(void)
{
    // lo que Ud desee
    cout << "\n leer px0=";
    cin >> px0;
    cout << "\n leer py0=";
    cin >> py0;
    cout << "\n leer px1=";
    cin >> px1;
    cout << "\n leer py1=";
    cin >> py1;
}
