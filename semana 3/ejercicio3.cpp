#include <GL/glut.h>
#include <iostream>
#include <vector>

// Definición de los vértices del triángulo
struct Punto {
    float x, y;
};

Punto A = { -0.5f, -0.5f }; // Vértice A
Punto B = { 0.5f, -0.5f };  // Vértice B
Punto C = { 0.0f, 0.5f };   // Vértice C

int N = 10; // Número de puntos a calcular en cada arista

// Función para interpolar entre dos puntos
Punto interpola(const Punto& p1, const Punto& p2, float t) {
    Punto p;
    p.x = (1 - t) * p1.x + t * p2.x;
    p.y = (1 - t) * p1.y + t * p2.y;
    return p;
}

// Función para dibujar el triángulo y los puntos interpolados
void dibujaTriangulo() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar el triángulo principal
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f); // Blanco
    glVertex2f(A.x, A.y);
    glVertex2f(B.x, B.y);
    glVertex2f(C.x, C.y);
    glEnd();

    // Dibujar los puntos interpolados entre AB, BC y CA y conectarlos
    for (int i = 0; i <= N; i++) {
        float t = (float)i / N;

        // Interpolaciones en las tres aristas
        Punto Pab = interpola(A, B, t); // Puntos entre A y B
        Punto Pbc = interpola(B, C, t); // Puntos entre B y C
        Punto Pca = interpola(C, A, t); // Puntos entre C y A

        // Conexión entre los puntos
        glBegin(GL_LINES);

        // Línea entre Pab y Pbc
        glColor3f(1.0f, 0.0f, 0.0f); // Rojo para AB -> BC
        glVertex2f(Pab.x, Pab.y);
        glVertex2f(Pbc.x, Pbc.y);

        // Línea entre Pbc y Pca
        glColor3f(0.0f, 1.0f, 0.0f); // Verde para BC -> CA
        glVertex2f(Pbc.x, Pbc.y);
        glVertex2f(Pca.x, Pca.y);

        // Línea entre Pca y Pab
        glColor3f(0.0f, 0.0f, 1.0f); // Azul para CA -> AB
        glVertex2f(Pca.x, Pca.y);
        glVertex2f(Pab.x, Pab.y);

        glEnd();
    }

    glFlush();
}

// Configuración inicial de OpenGL
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fondo negro
    glColor3f(1.0f, 1.0f, 1.0f);          // Color blanco
    glPointSize(5.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);     // Rango de coordenadas
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Triángulo Parabólico");

    initGL();
    glutDisplayFunc(dibujaTriangulo); // Función de dibujo
    glutMainLoop();

    return 0;
}
