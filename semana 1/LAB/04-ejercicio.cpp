/*
    Hacer un programa en OpenGL para dibujar los ejes coordenados (bidimensional) etiquetando ambos ejes:
*/

#include <GL/glut.h>
#include <cstdio>
#include <cstring>
#include <math.h>

void reshape(int, int);
void dibujarDecagono(float centerX, float centerY, float radius, GLenum mode);

void dibujarTexto(float x, float y, const char* string)
{
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

void dibujar()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Color negro para los ejes y etiquetas

    // Dibujar eje X
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();

    // Dibujar eje Y
    glBegin(GL_LINES);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    // Etiquetar eje X
    dibujarTexto(0.9, -0.05, "X"); // [-1,1]

    // Etiquetar eje Y
    dibujarTexto(-0.05, 0.9, "Y"); // [-1,1]

    // Dibujar un decágono lleno
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    dibujarDecagono(-0.65, 0.5, 0.3, GL_POINTS);

    // Dibujar un decágono de contorno
    glColor3f(1.0, 0.0, 0.0);
    dibujarDecagono(0.0, 0.5, 0.3, GL_LINE_LOOP);

    // Dibujar un decágono de puntos
    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(5.0);
    dibujarDecagono(0.65, 0.5, 0.3, GL_LINE_LOOP);

    glColor3f(0.0, 0.0, 1.0);
    dibujarDecagono(-0.65, -0.5, 0.3, GL_POLYGON);

    glColor3f(0.0, 0.0, 1.0);
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(2.0);
    dibujarDecagono(0.0, -0.5, 0.3, GL_LINE_LOOP);
	glDisable(GL_LINE_STIPPLE);

    glColor3f(0.0, 1.0, 0.0);
	dibujarDecagono(0.65, -0.5, 0.3, GL_POLYGON);

    glColor3f(0.0, 0.0, 1.0);
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(2.0);
    dibujarDecagono(0.65, -0.5, 0.3, GL_LINE_LOOP);
    glDisable(GL_LINE_STIPPLE);

    glFlush(); // 

}

void inicializar()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // Color blanco para el fondo
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ejes Coordenados");
    inicializar();
    glutDisplayFunc(dibujar);
	glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void dibujarDecagono(float centerX, float centerY, float radius, GLenum mode) {
    glBegin(mode);
    for (int i = 0; i < 10; i++)
    {
        float angulo = 2.0f * 3.14159f * float(i) / 10.0f;
        float x = centerX + radius * cos(angulo);
        float y = centerY + radius * sin(angulo);
        glVertex2f(x, y);
    }
    glEnd();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // define el viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-10.0, 10.0, -10.0, 10, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
