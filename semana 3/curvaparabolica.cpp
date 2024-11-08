#include <GL/glut.h>
#include <iostream>

float Ax = 0.0f, Ay = 0.5f; // Coordenadas del vértice A
float Bx = 0.5f, By = 0.0f; // Coordenadas del vértice B
float Cx = 0.0f, Cy = -0.5f; // Coordenadas del vértice C
float Dx = -0.5f, Dy = 0.0f; // Coordenadas del vértice D
float center_x = 0.0f, center_y = 0.0f; // Coordenadas del centro


int N = 10;  // Número de puntos a calcular en cada arista

void interpola(float x1, float y1, float x2, float y2, float t, float& x, float& y) {
    x = (1 - t) * x1 + t * x2;
    y = (1 - t) * y1 + t * y2;
}

// Función para dibujar el triángulo y los puntos interpolados
void dibujaCurvaParabolica() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f); // Blanco
    glVertex2f(Ax, Ay);
    glVertex2f(Bx, By);
    glVertex2f(Cx, Cy);
	glVertex2f(Dx, Dy);
    glEnd();

    // Dibujar los puntos interpolados entre AB, BC y CA y conectarlos
    for (int i = 0; i <= N; i++) {
        float t = (float)i / N;

        // Variables para los puntos interpolados
        float Pab_x, Pab_y;
		float Pbc_x, Pbc_y;
		float Pcd_x, Pcd_y;
		float Pda_x, Pda_y;

		// Interpolaciones en las 4 aristas
        interpola(Ax, Ay, Bx, By, t, Pab_x, Pab_y);
		interpola(Bx, By, Cx, Cy, t, Pbc_x, Pbc_y);
		interpola(Cx, Cy, Dx, Dy, t, Pcd_x, Pcd_y);
		interpola(Dx, Dy, Ax, Ay, t, Pda_x, Pda_y);

        // Conexión entre los puntos
        glBegin(GL_LINES);

        // Línea entre Pab y Pbc
        glColor3f(1.0f, 0.0f, 0.0f); // Rojo para AB -> BC
        glVertex2f(Pab_x, Pab_y);
        glVertex2f(Pbc_x, Pbc_y);

		// Línea entre Pbc y Pcd
		glColor3f(0.0f, 1.0f, 0.0f); // Verde para BC -> CD
		glVertex2f(Pbc_x, Pbc_y);
		glVertex2f(Pcd_x, Pcd_y);

		// Línea entre Pcd y Pda
		glColor3f(0.0f, 0.0f, 1.0f); // Azul para CD -> DA
		glVertex2f(Pcd_x, Pcd_y);
		glVertex2f(Pda_x, Pda_y);

		// Línea entre Pda y Pab
		glColor3f(1.0f, 1.0f, 0.0f); // Amarillo para DA -> AB
		glVertex2f(Pda_x, Pda_y);
		glVertex2f(Pab_x, Pab_y);

        glEnd();
    }

    glFlush();
}

// Configuración inicial de OpenGL
void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fondo negro
    glColor3f(1.0f, 1.0f, 1.0f);          // Color blanco
    glPointSize(5.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);     // Rango de coordenadas
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Curva Parabolica");

    initGL();
    glutDisplayFunc(dibujaCurvaParabolica); // Función de dibujo
    glutMainLoop();

    return 0;
}
