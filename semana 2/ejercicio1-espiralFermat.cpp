#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <cmath>  // Para funciones matemáticas como sin() y cos()

const int numPoints = 500;  // Número de puntos en la espiral
const float maxTheta = 4.0f * M_PI;  // Ángulo máximo (en radianes) para la espiral

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < numPoints; ++i) {
        float theta = (i / (float)numPoints) * maxTheta;  // Ángulo en radianes
        float r = theta;  // Radio en función de theta

        float x = r * cos(theta);  // Coordenada x
        float y = r * sin(theta);  // Coordenada y

        glVertex2f(x, y);  // Añade el vértice a la espiral
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15, 15, -15, 15);  // Ajusta el rango de visión según la espiral
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Espiral de Fermat");

    glClearColor(1.0, 1.0, 1.0, 1.0);  // Fondo blanco
    glColor3f(0.0, 0.0, 0.0);  // Color de la espiral (negro)

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

