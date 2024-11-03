#include <GL/glut.h>
#include <cmath>
#include <iostream>

const float PI = 3.14159265359;

void drawStarPolygon(int sides, int skip) {
    float angleStep = 2 * PI / sides;  // Ángulo entre los vértices del polígono
    float radius = 0.5;  // Radio del polígono

    // Calcula las coordenadas de los vértices del polígono regular
    float vertices[100][2]; // Suponemos que el máximo N es 100
    for (int i = 0; i < sides; ++i) {
        float angle = i * angleStep;
        vertices[i][0] = radius * cos(angle); // x
        vertices[i][1] = radius * sin(angle); // y
    }

    // Dibuja el polígono estrellado
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < sides; ++i) {
        int nextVertex = (i * skip) % sides;  // Salta vértices para formar la estrella
        glVertex2f(vertices[nextVertex][0], vertices[nextVertex][1]);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibuja diferentes estrellas para probar
    glColor3f(1.0, 0.0, 0.0);  // Color rojo
    drawStarPolygon(7, 2);     // Estrella 7/2 (heptágono estrellado)

    glColor3f(0.0, 1.0, 0.0);  // Color verde
    drawStarPolygon(7, 3);     // Estrella 7/3 (otra versión del heptágono estrellado)

    glColor3f(0.0, 0.0, 1.0);  // Color azul
    drawStarPolygon(9, 2);     // Estrella 9/2 (eneágono estrellado)

    glColor3f(1.0, 1.0, 0.0);  // Color amarillo
    drawStarPolygon(9, 4);     // Estrella 9/4 (otra versión del eneágono estrellado)

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Fondo blanco
    glOrtho(-1, 1, -1, 1, -1, 1);      // Proyección ortogonal
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Polígono Estrellado OpenGL");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
