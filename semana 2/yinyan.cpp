#include <GL/glut.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void init(void);
void display(void);
void reshape(int, int);
void drawGrid();
void drawAxes();
void drawQuadrant(float, float, float, float, float, float);
void drawCircle(float, float, float, float, float, float);
void drawYinYang();

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Yin y Yang en cuadrícula");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Fondo blanco
    glLineWidth(2.0);  // Grosor de las líneas
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpiar la pantalla
    drawGrid();                     // Dibujar la cuadrícula
    drawAxes();                     // Dibujar los ejes
    drawYinYang();                  // Dibujar el Yin y Yang
    glFlush();                      // Enviar los comandos a la pantalla
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-7.0, 7.0, -7.0, 7.0, -1.0, 1.0);  // Coordenadas ortogonales
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawGrid() {
    glColor3f(0.7, 0.7, 0.7);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (float i = -6; i <= 6; i++) {
        glVertex2f(i, -6);
        glVertex2f(i, 6);
        glVertex2f(-6, i);
        glVertex2f(6, i);
    }
    glEnd();
}

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-6, 0);
    glVertex2f(6, 0);
    glVertex2f(0, -6);
    glVertex2f(0, 6);
    glEnd();
}

void drawQuadrant(float start_angle, float end_angle, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 100; i++) {
        float theta = start_angle + i * (end_angle - start_angle) / 100.0;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawCircle(float cx, float cy, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; i++) {
        float theta = i * 2.0 * M_PI / 100.0;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawYinYang() {
    float radius = 5.0;
    drawQuadrant(0, M_PI / 2, radius, 0.0, 0.0, 0.0);   // Primer cuadrante
    drawQuadrant(M_PI / 2, M_PI, radius, 1.0, 1.0, 1.0); // Segundo cuadrante
    drawQuadrant(M_PI, 3 * M_PI / 2, radius, 1.0, 1.0, 1.0); // Tercer cuadrante
    drawQuadrant(3 * M_PI / 2, 2 * M_PI, radius, 0.0, 0.0, 0.0); // Cuarto cuadrante

    (0.0, 2.5, radius / 6, 0.0, 0.0, 0.0);  // Círculo superior
    drawCircle(0.0, -2.5, radius / 6, 1.0, 1.0, 1.0);  // Círculo inferior
    // Dibujar el círculo negro en la mitad superior
    drawCircle(0.0, -2.5, radius / 2, 0.0, 0.0, 0.0);  // Círculo mediano superior (negro)

    // Dibujar el círculo blanco en la mitad inferior
    drawCircle(0.0, +2.5, radius / 2, 1.0, 1.0, 1.0);  // Círculo mediano inferior (blanco)
    drawCircle(0.0, 2.5, radius / 6, 0.0, 0.0, 0.0);  // Círculo superior
    drawCircle(0.0, -2.5, radius / 6, 1.0, 1.0, 1.0);  // Círculo inferior
    // Dibujar el círculo negro en la mitad superior

}
