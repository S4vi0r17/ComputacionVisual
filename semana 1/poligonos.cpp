#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <string.h>

void display(void);
void drawPolygon(GLfloat radio, int sides, GLfloat xOffset, GLfloat yOffset, GLfloat r, GLfloat g, GLfloat b, GLboolean isDashed, GLboolean isFilled, GLfloat lineWidth);
void drawVerticesPoligon(GLfloat radio, int sides, GLfloat xOffset, GLfloat yOffset, GLfloat r, GLfloat g, GLfloat b);
void drawString(float x, float y, const char* string);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("App");
    glClearColor(1.0, 1.0, 1.0, 0.0); // Fondo blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar los ejes
    glColor3f(0.0, 0.0, 1.0); // Color azul para los ejes
    glDisable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
    // Eje X
    glVertex2f(-20.0, 0.0);
    glVertex2f(20.0, 0.0);
    // Eje Y
    glVertex2f(0.0, -20.0);
    glVertex2f(0.0, 20.0);
    glEnd();

    // Etiquetas para los ejes
    drawString(20.1, 0.1, "X");
    drawString(0.1, 20.1, "Y");

    // Pólígonos
    drawVerticesPoligon(5.0f, 8, -15.0f, 10.0f, 1.0f, 0.0f, 0.0f);
    drawPolygon(5.0f, 8, 0.0f, 10.0f, 1.0f, 0.0f, 0.0f, GL_FALSE, GL_FALSE, 1.0f);
    drawPolygon(5.0f, 8, 15.0f, 10.0f, 0.0f, 1.0f, 0.0f, GL_FALSE, GL_FALSE, 4.0f);

    drawPolygon(5.0f, 8, -15.0f, -10.0f, 0.0f, 0.0f, 1.0f, GL_FALSE, GL_TRUE, 1.0f);
    drawPolygon(5.0f, 8, 0.0f, -10.0f, 0.0f, 0.0f, 1.0f, GL_TRUE, GL_FALSE, 1.0f);
    drawPolygon(5.0f, 8, 15.0f, -10.0f, 0.0f, 1.0f, 0.0f, GL_TRUE, GL_TRUE, 1.0f);
    drawPolygon(5.0f, 8, 15.0f, -10.0f, 0.0f, 0.0f, 1.0f, GL_TRUE, GL_FALSE, 1.0f);

    glFlush();
}

void drawPolygon(GLfloat radio, int sides, GLfloat xOffset, GLfloat yOffset, GLfloat r, GLfloat g, GLfloat b, GLboolean isDashed, GLboolean isFilled, GLfloat lineWidth)
{
    GLfloat ang, x, y;

    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0.0f);
    glColor3f(r, g, b);

    if (isDashed)
    {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF); // Patrón de línea discontinua
    }
    else
    {
        glDisable(GL_LINE_STIPPLE);
    }

    glLineWidth(lineWidth); // Ajusta el grosor de la línea

    if (isFilled)
    {
        glBegin(GL_POLYGON); // Dibujar un polígono relleno
    }
    else
    {
        glBegin(GL_LINE_LOOP); // Dibujar solo el borde del polígono
    }

    for (int i = 0; i < sides; i++)
    {
        ang = 2 * M_PI * i / sides;
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}

void drawVerticesPoligon(GLfloat radio, int sides, GLfloat xOffset, GLfloat yOffset, GLfloat r, GLfloat g, GLfloat b)
{
    GLfloat ang, x, y;

    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0.0f);
    glColor3f(r, g, b);

    glBegin(GL_POINTS); // Dibujar los vértices del polígono
    for (int i = 0; i < sides; i++)
    {
        ang = 2 * M_PI * i / sides;
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}

void drawString(float x, float y, const char* string)
{
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(string); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}
