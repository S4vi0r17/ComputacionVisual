/*
Desarrollar un programa basado en OpenGL para generar una polilínea dentada cerrada a
partir de 𝑁 = 4𝑘 vértices, considere su construcción entre dos circunferencias
concéntricas. (ver gráfica referencial, los trazos punteados deben ignorarse
*/

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define M_PI 3.14159265358979323846

void init(void);
void display(void);
void reshape(int, int);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                       // inicializa la libreria GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // modo de visualizacion
    glutInitWindowSize(700, 700);
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
    glShadeModel(GL_FLAT); // modelo de sombreado
}

void display(void)
{
    GLfloat ang, radio=5.0, x, y;
	int N = 24; // numero de vertices
	bool flag = false;
    glClear(GL_COLOR_BUFFER_BIT); // borra el buffer de color
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(5.0); // tamaño de los puntos
    glPushMatrix(); // salva el estado actual de la matriz
    glBegin(GL_LINE_LOOP);
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2 * M_PI / N)
    {
        if (flag) {
			radio = 8.0;
			flag = false;
        }
        else
        {
			radio = 5.0;
			flag = true;
        }

        x = radio * sin(ang);
        y = radio * cos(ang);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix(); // reecupera el estado del matriz
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // define el viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
