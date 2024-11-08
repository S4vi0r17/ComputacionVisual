#include <GL/glut.h>
#include <vector>
#include <iostream>

// Estructura para representar un punto
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

std::vector<Point> points;  // Vector para almacenar los puntos
bool needRedraw = false;    // Flag para indicar si se necesita redibujar

// Función LINEA (como se definió anteriormente)
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
    for (const auto& point : points) {
        glVertex2i(point.x, point.y);
    }
    glEnd();

    // Dibujar líneas
    glPointSize(1.0f);
    for (size_t i = 1; i < points.size(); i++) {
        LINEA(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        points.emplace_back(x, windowHeight - y);  // Invertir coordenada y
        needRedraw = true;
        std::cout << "Punto añadido: (" << x << ", " << windowHeight - y << ")" << std::endl;
        glutPostRedisplay();
    }
}

void idle() {
    if (needRedraw) {
        glutPostRedisplay();
        needRedraw = false;
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
    glutIdleFunc(idle);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Fondo blanco

    glutMainLoop();
    return 0;
}
