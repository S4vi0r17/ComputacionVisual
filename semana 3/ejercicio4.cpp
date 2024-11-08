#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void circunferencia_punto_medio(int, int, int);
void recta_punto_medio(int, int, int, int);
void ejes(void);
void inicio(void);
void display(void);
void myreshape(int, int);
void TrianguloEquilatero(int, int, int);
void TrianguloInscritoCircu(int);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Algoritmos de primitivas graficas");

    inicio();
    glutDisplayFunc(display);
    glutReshapeFunc(myreshape);
    glutMainLoop();
    return 0;
}

void ejes(void)
{
    float e = 195;
    glBegin(GL_LINES);
    glVertex2f(-e, 0);
    glVertex2f(e, 0);
    glVertex2f(0, -e);
    glVertex2f(0, e);
    glEnd();
}

void circunferencia_punto_medio(int h, int k, int R)
{
    int x = 0;
    int y = R, d = 1 - R;
    glBegin(GL_POINTS);
    while (x < y)
    {
        glVertex2f(x + h, y + k);
        glVertex2f(-x + h, y + k);
        glVertex2f(-y + h, x + k);
        glVertex2f(-y + h, -x + k);
        glVertex2f(-x + h, -y + k);
        glVertex2f(x + h, -y + k);
        glVertex2f(y + h, -x + k);
        glVertex2f(y + h, x + k);

        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    glEnd();
}

void recta_punto_medio(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true)
    {
        glVertex2i(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
    glEnd();
}

void inicio(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // Fondo blanco
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();     // Guarda el estado actual de la matriz
    glColor3f(1, 0, 0); // Rojo para los ejes
    glPointSize(2);     // Tamaño de los puntos
    ejes();

    // Dibujo del triángulo equilátero y las circunferencias inscritas
    glColor3f(0, 0, 1); // Azul para el triángulo
    TrianguloEquilatero(100, 0, 0);

    glColor3f(1, 0, 0); // Rojo para las circunferencias
    TrianguloInscritoCircu(100);

    glPopMatrix(); // Restaura el estado de la matriz
    glFlush();
}

void myreshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TrianguloEquilatero(int L, int h, int k) {
    glColor3f(0.0, 0.0, 1.0); // Azul para el triángulo

    // Coordenadas de los vértices del triángulo equilátero
    int x0 = h;
    int y0 = round(L * sqrt(3) / 3) + k;

    int x1 = round(L / 2) + h;
    int y1 = -round(L * sqrt(3) / 6) + k;

    int x2 = -round(L / 2) + h;
    int y2 = -round(L * sqrt(3) / 6) + k;

    // Dibujo de las líneas del triángulo utilizando el algoritmo de punto medio
    recta_punto_medio(x0, y0, x1, y1);
    recta_punto_medio(x1, y1, x2, y2);
    recta_punto_medio(x2, y2, x0, y0);
}

void TrianguloInscritoCircu(int L) {
    // Circunferencia mayor inscrita en el triángulo equilátero
    int radioGrande = round(L / sqrt(3));
    circunferencia_punto_medio(0, 0, radioGrande);

    int nuevocentro = round(L / (sqrt(3) + 1));
    int nuevoradio = round(L / ((sqrt(3) + 1) * 2));

    int x0 = 0;
    int y0 = round(nuevocentro * sqrt(3) / 3);

    int x1 = round(nuevocentro / 2);
    int y1 = -round(nuevocentro * sqrt(3) / 6);

    int x2 = -round(nuevocentro / 2);
    int y2 = -round(nuevocentro * sqrt(3) / 6);


    // Dibujar las tres circunferencias pequeñas
    circunferencia_punto_medio(x0, y0, nuevoradio);
    circunferencia_punto_medio(x1, y1, nuevoradio);
    circunferencia_punto_medio(x2, y2, nuevoradio);
}
