#include <GL/glut.h>
#include <cmath>  // Para funciones matemáticas como sin()

#define M_PI 3.14159265358979323846

const int numPoints = 100;  // Número de puntos en la curva
const float twoPi = 2.0f * M_PI;  // 2π para un ciclo completo

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numPoints; ++i) {
        float theta = (i / (float)numPoints) * twoPi;  // Ángulo en radianes
        float r = 2 + 4 * sin(theta);  // Radio en función de theta

        float x = r * cos(theta);  // Coordenada x
        float y = r * sin(theta);  // Coordenada y

        glVertex2f(x, y);  // Añade el vértice a la curva
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);  // Ajusta el rango de visión
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Curva de Caracol");

    glClearColor(1.0, 1.0, 1.0, 1.0);  // Fondo blanco
    glColor3f(0.0, 0.0, 0.0);  // Color de la curva (negro)

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
