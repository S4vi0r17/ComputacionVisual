// by pepito jadjasdnjas
// algoritmo de punto medio basado en el texto
//  Principes and Practice by FGeiner nfsdfd
//  codigo basado en Gemini

#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void circunferencia_punto_medio(int, int, int);
void ejes(void);
void inicio(void);
void display(void);
void myreshape(int, int);
void abasico(int, int, int, int);
void ingresoDatos(void);
int px0 = 0, py0 = 0, px1 = 50, py1 = 20;

int main(int argc, char **argv)
{
    // ingresoDatos();
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
    {
        // discretizacion valida en el II octante
        int x = 0;
        int y = R, d = 1 - R;
        glBegin(GL_POINTS);
        glVertex2f(x + h, y + k);
        glVertex2f(-x + h, y + k);
        glVertex2f(-y + h, x + k);
        glVertex2f(-y + h, -x + k);
        glVertex2f(-x + h, -y + k);
        glVertex2f(x + h, -y + k);
        glVertex2f(y + h, -x + k);
        glVertex2f(y + h, x + k);
        while (x < y)
        {
            if (d < 0)
                d += 2 * x + 3;
            else
            {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
            glVertex2f(x + h, y + k);
            // aplico reflexiones para reprod las coord en los 7 octantes restantes
            glVertex2f(-x + h, y + k);
            glVertex2f(-y + h, x + k);
            glVertex2f(-y + h, -x + k);
            glVertex2f(-x + h, -y + k);
            glVertex2f(x + h, -y + k);
            glVertex2f(y + h, -x + k);
            glVertex2f(y + h, x + k);
        }
        glEnd();
    }
}

void inicio(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // parametros: rojo, amarillo y azul, el cuarto es el parametro      alpha
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();     // salva el estado actual de la matriz
    glColor3f(0, 0, 1); // Azul
    glPointSize(2);     // Fije el grosor de pixel = 2
    abasico(px0, py0, px1, py1);
    glColor3f(1, 0, 0);
    ejes();
    glColor3f(0, 1, 0);
    circunferencia_punto_medio(-10, 10, 50);
    circunferencia_punto_medio(200, 100, 50);
    circunferencia_punto_medio(-30, -40, 100);
    glPopMatrix(); // recupera el estado del matriz
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
        cout << x << "  " << y << "  " << (int)ceil(y - 0.5) << "\n";
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
