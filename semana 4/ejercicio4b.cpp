#include <GL/glut.h>
#include <iostream>

#define MAX_POINTS 100

int pointsX[MAX_POINTS];
int pointsY[MAX_POINTS];
int pointCount = 0;

void LINEA(int x0, int y0, int xf, int yf) {
    int dx = abs(xf - x0);
    int dy = abs(yf - y0);
    int sx = (x0 < xf) ? 1 : -1;
    int sy = (y0 < yf) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x0, y0);
        if (x0 == xf && y0 == yf) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f);  // Color azul

    // Dibujar puntos
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < pointCount; i++) {
        glVertex2i(pointsX[i], pointsY[i]);
    }
    glEnd();

    // Dibujar líneas
    glPointSize(1.0f);
    for (int i = 1; i < pointCount; i++) {
        LINEA(pointsX[i-1], pointsY[i-1], pointsX[i], pointsY[i]);
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (pointCount < MAX_POINTS) {
            int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
            pointsX[pointCount] = x;
            pointsY[pointCount] = windowHeight - y;  // Invertir coordenada y
            pointCount++;
            std::cout << "Punto añadido: (" << x << ", " << windowHeight - y << ")" << std::endl;
            glutPostRedisplay();
        } else {
            std::cout << "Límite de puntos alcanzado" << std::endl;
        }
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Dibuja Líneas con Ratón");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Fondo blanco

    glutMainLoop();
    return 0;
}
