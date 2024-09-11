#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
void circunferencia(int,int,int);
void init(void);
void display(void);
void reshape(int,int);
void modelo1(int,int,int);

void modelo3(int h,int k,int radio)
{
    glBegin(GL_POLYGON);
        circunferencia(h,k,radio);
    glEnd();
}

void modelo2(int h,int k,int radio)
{
    glBegin(GL_LINE_LOOP);
        circunferencia(h,k,radio);
    glEnd();
}

void modelo1(int h,int k,int radio)
{
    glBegin(GL_POINTS);
        circunferencia(h,k,radio);
    glEnd();
}

void circunferencia(int h,int k,int radio)
{ GLfloat ang,  x, y;
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/20)
    {
    x =h+ radio * cos(ang);
    y =k+ radio * sin(ang);
    glVertex2f(x,y);
    }
}


int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(1000,500);
//glutInitWindowPosition(500,500);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}
void init(void)
{
glClearColor(1.0,1.0,1.0,0.0);  //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
glShadeModel(GL_FLAT);
}

void display(void)
{
GLfloat ang, radio = 8.0f, x, y;
glClear(GL_COLOR_BUFFER_BIT);
glPushMatrix();
glColor3f(0,0,1);
glPointSize(4);


modelo1(-10,5,4);
modelo2(0,5,4);
modelo3(10,5,4);

modelo1(-10,-5,4);
glLineWidth(4);
modelo2(0,-5,4);
modelo3(10,-5,4);

glPopMatrix();      // reecupera el estado del matriz
glFlush();
}
void reshape(int w, int h)
{
glViewport(0,0,(GLsizei)w, (GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-20.0,20.0,-10.0,10,-10.0,10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}