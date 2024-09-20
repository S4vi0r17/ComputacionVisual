#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void init();
void display();
void reshape(int, int);

void background(void);
void caracol(void);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    background();
    caracol();

    glPopMatrix();

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void background(void)
{
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_LINE);
    glColor3f(1.0, 0.0, 0.0);
    gluDisk(quadric, 0.0, 7.0, 15, 4);
    // gluDisk(objeto, radio interior, radio exterior, numero de segmentos, numero de segmentos)
}

void caracol(void) {
    GLfloat ang, radio, x, y;
    glPushMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(2.0);

    glBegin(GL_LINE_LOOP);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2 * M_PI / 50)
    {
        radio = 2.0 + 4.0 * sin(ang);
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}
