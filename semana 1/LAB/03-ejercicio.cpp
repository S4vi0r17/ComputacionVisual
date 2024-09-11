/*
    Hacer un programa en OpenGL para dibujar los ejes coordenados (bidimensional) etiquetando ambos ejes:
*/

#include <GL/glut.h>
#include <cstdio>
#include <cstring>

void dibujarTexto(float x, float y, const char *string)
{
    glRasterPos2f(x, y);
    for (const char *c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

void dibujar()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Color negro para los ejes y etiquetas

    // Dibujar eje X
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();

    // Dibujar eje Y
    glBegin(GL_LINES);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    // Etiquetar eje X
    dibujarTexto(0.9, -0.05, "X"); // [-1,1]

    // Etiquetar eje Y
    dibujarTexto(-0.05, 0.9, "Y"); // [-1,1]

    glFlush();
}

void inicializar()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // Color blanco para el fondo
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ejes Coordenados");
    inicializar();
    glutDisplayFunc(dibujar);
    glutMainLoop();
    return 0;
}
