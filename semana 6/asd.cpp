#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>

const int NUM_BALLS = 5;
const float BALL_RADIUS = 0.1f;
const float ROPE_LENGTH = 1.0f;
const float MAX_DISPLACEMENT = 0.3f;
const float GRAVITY = 9.8f;
const float DAMPING = 0.9999f; // Ajustado para conservar más energía
const float COLLISION_DAMPING = 0.95f;
const float EPSILON = 0.001f;

struct Ball {
    float x, y;
    float velocity;
};

std::vector<Ball> balls(NUM_BALLS);

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

    float spacing = BALL_RADIUS * 2.1f;
    for (int i = 0; i < NUM_BALLS; i++) {
        balls[i].x = (i - (NUM_BALLS - 1) / 2.0f) * spacing;
        balls[i].y = -ROPE_LENGTH;
        balls[i].velocity = 0.0f;
    }

    // Iniciar el movimiento del primer balón
    balls[0].x -= MAX_DISPLACEMENT; // Posición inicial desplazada
    balls[0].velocity = 0; // Velocidad inicial
}

void drawBall(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);

    glutSolidSphere(BALL_RADIUS, 32, 32);
    glPopMatrix();
}

void drawRope(float x1, float y1, float x2, float y2) {
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0);
    glVertex3f(x2, y2, 0);
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawAxis() {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -2.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    glEnd();
    glEnable(GL_LIGHTING);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    drawAxis();

    for (int i = 0; i < NUM_BALLS; i++) {
        float ropeX = (i - (NUM_BALLS - 1) / 2.0f) * (BALL_RADIUS * 2.1f);
        drawRope(ropeX, 0, balls[i].x, balls[i].y);
        drawBall(balls[i].x, balls[i].y);
    }

    glutSwapBuffers();
}

void update(int value) {
    const float dt = 0.001f;
    const int steps = 16;

    for (int step = 0; step < steps; step++) {
        for (int i = 0; i < NUM_BALLS; i++) {
            float ropeX = (i - (NUM_BALLS - 1) / 2.0f) * (BALL_RADIUS * 2.1f);
            float displacement = balls[i].x - ropeX;
            float angle = asin(displacement / ROPE_LENGTH);

            float acceleration = -GRAVITY * sin(angle);
            balls[i].velocity += acceleration * dt;
            balls[i].x += balls[i].velocity * dt;

            balls[i].y = -sqrt(ROPE_LENGTH * ROPE_LENGTH - displacement * displacement);

            balls[i].velocity *= DAMPING; // Ajuste para mantener la energía
        }

        for (int i = 0; i < NUM_BALLS - 1; i++) {
            if (balls[i].x + BALL_RADIUS > balls[i + 1].x - BALL_RADIUS) {
                float temp = balls[i].velocity;
                balls[i].velocity = balls[i + 1].velocity * COLLISION_DAMPING;
                balls[i + 1].velocity = temp * COLLISION_DAMPING;

                // Separar las bolas para evitar que se peguen
                float midpoint = (balls[i].x + balls[i + 1].x) / 2;
                balls[i].x = midpoint - BALL_RADIUS;
                balls[i + 1].x = midpoint + BALL_RADIUS;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Péndulo de Newton");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);

    std::cout << "Programa iniciado. El péndulo se mueve de forma continua." << std::endl;

    glutMainLoop();
    return 0;
}
