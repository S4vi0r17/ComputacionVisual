#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <cmath>

// Variables para controlar el ángulo y el estado del gancho
float angle = 0.0f;
float targetAngle = 0.0f;
bool hookCompressed = false;

// Dimensiones del brazo
const float armLength1 = 0.5f;
const float armLength2 = 0.3f;
float hookSize = 0.1f;
float hookTargetSize = 0.1f;

// Suavidad del movimiento del brazo
const float rotationSpeed = 2.0f;  // Velocidad para suavizar la rotación

// Función para dibujar un círculo (para articulaciones)
void drawCircle(float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // Centro del círculo
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * M_PI * i / 100.0f;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

// Función para dibujar el gancho
void drawHook() {
    glColor3f(0.8f, 0.8f, 0.8f);  // Color metálico claro
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, -hookSize);  // Tamaño dinámico del gancho
    glEnd();
}

// Función para dibujar el brazo mecánico
void drawArm() {
    // Primer segmento del brazo
    glColor3f(0.5f, 0.5f, 0.5f);  // Color metálico
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(armLength1, 0.0f);
    glEnd();

    // Articulación del primer segmento
    glPushMatrix();
    glTranslatef(armLength1, 0.0f, 0.0f);
    glColor3f(0.7f, 0.7f, 0.7f);  // Color de la articulación
    drawCircle(0.03f);  // Tamaño de la articulación

    // Segundo segmento del brazo
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(armLength2, 0.0f);
    glEnd();

    // Articulación del segundo segmento
    glTranslatef(armLength2, 0.0f, 0.0f);
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(0.02f);

    // Dibujar el gancho
    drawHook();
    glPopMatrix();
}

// Función de visualización
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Configurar la matriz de proyección
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Mover el brazo al centro de la ventana
    glTranslatef(0.0f, 0.0f, 0.0f);

    // Suavizar la rotación del brazo hacia el cursor
    angle += (targetAngle - angle) * 0.1f;
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // Suavizar el movimiento del gancho
    hookSize += (hookTargetSize - hookSize) * 0.1f;

    // Dibujar el brazo mecánico
    drawArm();

    glutSwapBuffers();
}

// Función para actualizar el ángulo del brazo con el movimiento del mouse
void mouseMotion(int x, int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Convertir coordenadas del mouse a coordenadas del sistema
    float mouseX = (x - 250) / 250.0f;  // Convertir a [-1, 1] en X
    float mouseY = ((windowHeight - y) - 250) / 250.0f;  // Convertir a [-1, 1] en Y

    // Calcular el ángulo para que el brazo apunte al cursor
    targetAngle = atan2f(mouseY, mouseX) * 180.0f / M_PI;

    glutPostRedisplay();
}

// Función para manejar el clic del mouse
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Comprimir el gancho al hacer clic
        hookTargetSize = 0.05f;  // Gancho comprimido
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // Volver a abrir el gancho cuando se suelte el clic
        hookTargetSize = 0.1f;  // Gancho abierto
    }

    glutPostRedisplay();
}

// Función para actualizar el estado (animaciones)
void update(int value) {
    glutPostRedisplay();  // Forzar redisplay para animaciones
    glutTimerFunc(16, update, 0);  // Actualizar cada ~60 FPS
}

int main(int argc, char** argv) {
    // Inicialización de GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Brazo Mecanico Realista");

    // Configurar el modo de proyección ortogonal
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Establecer funciones de devolución de llamada
    glutDisplayFunc(display);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseClick);
    glutTimerFunc(16, update, 0);  // Animación

    // Color de fondo
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Iniciar el bucle principal
    glutMainLoop();
    return 0;
}
