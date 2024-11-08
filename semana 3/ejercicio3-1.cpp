#include <GL/glut.h>
#include <iostream>

// Definición de los vértices del triángulo (sin usar struct)
float Ax = -0.5f, Ay = -0.5f;  // Coordenadas del vértice A
float Bx = 0.5f, By = -0.5f;   // Coordenadas del vértice B
float Cx = 0.0f, Cy = 0.5f;    // Coordenadas del vértice C

int N = 10;  // Número de puntos a calcular en cada arista

// Función para interpolar entre dos puntos dados por sus coordenadas
void interpola(float x1, float y1, float x2, float y2, float t, float& x, float& y) {
    x = (1 - t) * x1 + t * x2;
    y = (1 - t) * y1 + t * y2;
}

// Función para dibujar el triángulo y los puntos interpolados
void dibujaTriangulo() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar el triángulo principal
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f); // Blanco
    glVertex2f(Ax, Ay);
    glVertex2f(Bx, By);
    glVertex2f(Cx, Cy);
    glEnd();

    // Dibujar los puntos interpolados entre AB, BC y CA y conectarlos
    for (int i = 0; i <= N; i++) {
        float t = (float)i / N;

        // Variables para los puntos interpolados
        float Pab_x, Pab_y;
        float Pbc_x, Pbc_y;
        float Pca_x, Pca_y;

        // Interpolaciones en las tres aristas
        interpola(Ax, Ay, Bx, By, t, Pab_x, Pab_y); // Puntos entre A y B
        interpola(Bx, By, Cx, Cy, t, Pbc_x, Pbc_y); // Puntos entre B y C
        interpola(Cx, Cy, Ax, Ay, t, Pca_x, Pca_y); // Puntos entre C y A

        // Conexión entre los puntos
        glBegin(GL_LINES);

        // Línea entre Pab y Pbc
        glColor3f(1.0f, 0.0f, 0.0f); // Rojo para AB -> BC
        glVertex2f(Pab_x, Pab_y);
        glVertex2f(Pbc_x, Pbc_y);

        // Línea entre Pbc y Pca
        glColor3f(0.0f, 1.0f, 0.0f); // Verde para BC -> CA
        glVertex2f(Pbc_x, Pbc_y);
        glVertex2f(Pca_x, Pca_y);

        // Línea entre Pca y Pab
        glColor3f(0.0f, 0.0f, 1.0f); // Azul para CA -> AB
        glVertex2f(Pca_x, Pca_y);
        glVertex2f(Pab_x, Pab_y);

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
