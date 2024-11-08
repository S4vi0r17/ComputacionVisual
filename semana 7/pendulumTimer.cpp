#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>
#include <cstring>
#include <cmath>

using namespace std;

const int ms_per_frame = 16;  // ~60 fps
int time_step_counter = 0, pause_flag = 0;
double* times, * thetas, * vs;

// pendulum parameters
const int l = 10, N = 2500;
const double g = 9.8, theta0 = M_PI / 4, v0 = 0, ti = 0, tf = 20, alpha = 0.5, m = 1;

void initgLOptions() {
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void timer(int id) {
    if (pause_flag == 0) {
        time_step_counter++;
        if (time_step_counter >= N) {
            time_step_counter = 0;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(ms_per_frame, timer, 0);
}

void rk4_sys_integrator(double g, int l, double alpha, double m, double theta0, double v0, int N, double ti, double tf, double** times, double** thetas, double** vs) {
    double h = (tf - ti) / N;
    double t = ti;
    double theta = theta0;
    double v = v0;

    *times = new double[N];
    *thetas = new double[N];
    *vs = new double[N];

    (*times)[0] = t;
    (*thetas)[0] = theta;
    (*vs)[0] = v;

    for (int i = 1; i < N; i++) {
        double k1_theta = h * v;
        double k1_v = h * (-g / l * sin(theta) - alpha / m * v);

        double k2_theta = h * (v + 0.5 * k1_v);
        double k2_v = h * (-g / l * sin(theta + 0.5 * k1_theta) - alpha / m * (v + 0.5 * k1_v));

        double k3_theta = h * (v + 0.5 * k2_v);
        double k3_v = h * (-g / l * sin(theta + 0.5 * k2_theta) - alpha / m * (v + 0.5 * k2_v));

        double k4_theta = h * (v + k3_v);
        double k4_v = h * (-g / l * sin(theta + k3_theta) - alpha / m * (v + k3_v));

        theta += (k1_theta + 2 * k2_theta + 2 * k3_theta + k4_theta) / 6.0;
        v += (k1_v + 2 * k2_v + 2 * k3_v + k4_v) / 6.0;
        t += h;

        (*times)[i] = t;
        (*thetas)[i] = theta;
        (*vs)[i] = v;
    }
}

void printString(const char* str, float x, float y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRasterPos2f(x, y);
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawPendulum(double time, double theta, double v) {
    // The pendulum support anchor block
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glVertex2d(-0.8, 0.0);
    glVertex2d(0.8, 0.0);
    glVertex2d(0.8, 0.8);
    glVertex2d(-0.8, 0.8);
    glEnd();

    // The pendulum rod and bob
    double x = l * sin(theta);
    double y = -l * cos(theta);

    glLineWidth(2);
    glColor3f(0.8, 0.25, 0.4);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(x, y);
    glEnd();

    glColor3f(0.2, 0.65, 0.4);
    glPushMatrix();
    glTranslated(x, y, 0.0);
    glutSolidSphere(0.5, 30, 30);
    glPopMatrix();

    char mystr[100];
    snprintf(mystr, sizeof(mystr), "Time: %.2f  Theta: %.2f  v: %.2f", time, theta, v);
    glColor3f(1.0, 1.0, 1.0);  // Set text color to white
    printString(mystr, 10, glutGet(GLUT_WINDOW_HEIGHT) - 30);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);

    drawPendulum(times[time_step_counter], thetas[time_step_counter], vs[time_step_counter]);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // Escape key
        exit(0);
        break;
    case ' ': // Space bar
        pause_flag = !pause_flag;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pendulum Simulation");

    rk4_sys_integrator(g, l, alpha, m, theta0, v0, N, ti, tf, &times, &thetas, &vs);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    initgLOptions();

    glutMainLoop();

    delete[] times;
    delete[] thetas;
    delete[] vs;

    return 0;
}
