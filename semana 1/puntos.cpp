#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define M_PI 3.14159265358979323846

void init(void);
void display(void);
void reshape(int, int);
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
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
	glClearColor(0.0, 0.0, 0.0, 0.0); //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
	glShadeModel(GL_FLAT);
}
/**
 * @brief Dibuja un pentágono utilizando puntos en una ventana OpenGL.
 *
 * La función `display` limpia el buffer de color, establece una matriz de transformación,
 * y dibuja un pentágono utilizando puntos. El pentágono se dibuja calculando las coordenadas
 * de sus vértices en base a un radio fijo y un ángulo que varía en incrementos de 2π/5.
 * Finalmente, se vacía la matriz de transformación y se fuerza el renderizado de los puntos.
 *
 * @param void No recibe parámetros.
 * @return void No retorna ningún valor.
 */
void display(void)
{
	GLfloat ang, radio = 8.0f, x, y;
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glBegin(GL_POINTS);
	for (ang = 0.0f; ang < 2 * M_PI; ang += 2 * M_PI / 5)
	{
		x = radio * sin(ang);
		y = radio * cos(ang);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
