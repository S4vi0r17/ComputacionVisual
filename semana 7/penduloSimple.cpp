#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265358979323846;
float angle = PI / 4; // Inicializa el ángulo (45 grados)
float length = 1.0;   // Longitud del péndulo
float g = 9.81;       // Aceleración debido a la gravedad
float angularVelocity = 0.0; // Velocidad angular inicial
float damping = 0.01; // Factor de amortiguación

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Calcula la posición de la masa del péndulo
    float x = length * sin(angle);
    float y = -length * cos(angle);

    // Dibuja el péndulo
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(x, y);
    glEnd();

    // Dibuja la masa del péndulo
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glutSolidSphere(0.05, 20, 20);
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {
    // Actualiza la velocidad angular y el ángulo
    float dt = 0.01; // Paso de tiempo
    float alpha = -(g / length) * sin(angle) - damping * angularVelocity;
    angularVelocity += alpha * dt;
    angle += angularVelocity * dt;

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Péndulo Simple en Movimiento");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;
}
