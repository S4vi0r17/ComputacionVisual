#include <stdlib.h>
#include <gl/glut.h>

// Declaración de variables
static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // Ángulos iniciales en los 3 ejes
static GLint eje = 2; // Eje inicial (Z)

// Función para construir la cara de un cubo
void cara()
{
    glBegin(GL_POLYGON);
    // Definir los vértices del polígono (cara del cubo)
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();
}

// Construye el cubo utilizando caras
void cubo(void)
{
    glPushMatrix();

    // Cara trasera
    glTranslatef(0.0, 0.0, -1.0);
    cara();

    // Cara frontal
    glTranslatef(0.0, 0.0, 2.0);
    cara();

    // Resto de caras del cubo (puedes definirlas si es necesario)

    glPopMatrix();
}

// Dibuja la escena
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Aplicar rotaciones en los ejes X, Y, Z
    glRotatef(theta[0], 1.0, 0.0, 0.0); // Rotación en el eje X
    glRotatef(theta[1], 0.0, 1.0, 0.0); // Rotación en el eje Y
    glRotatef(theta[2], 0.0, 0.0, 1.0); // Rotación en el eje Z

    cubo(); // Dibuja el cubo

    glFlush();
    glutSwapBuffers(); // Intercambiar buffers
}

// Controla el ángulo de rotación según el eje de giro
void girar_objeto_geometrico()
{
    theta[eje] += 2.0; // Aumenta el ángulo en el eje actual
    if (theta[eje] > 360.0)
        theta[eje] -= 360.0;
    display(); // Vuelve a dibujar la escena
}

// Control del teclado para cambiar el eje de rotación
void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla) {
    case 'a': eje = 0; break; // Cambia al eje X
    case 's': eje = 1; break; // Cambia al eje Y
    case 'd': eje = 2; break; // Cambia al eje Z
    case 'f': exit(0); break; // Salir del programa
    }
}

// Control de la ventana y el volumen de visualización
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
            2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
            2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

// Función principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mi objeto bajo rotaciones");

    glutReshapeFunc(myReshape);   // Ajusta la ventana
    glutDisplayFunc(display);     // Dibuja la escena
    glutIdleFunc(girar_objeto_geometrico); // Gira continuamente
    glutKeyboardFunc(teclado);    // Control del teclado

    glEnable(GL_DEPTH_TEST);      // Habilita el test de profundidad

    glutMainLoop(); // Inicia el loop de eventos
    return 0;
}
