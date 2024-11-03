#include <GL/glut.h>
#include <iostream>

float Ax = 0.0f, Ay = 0.5f; // Coordenadas del vértice A
float Bx = 0.5f, By = 0.0f; // Coordenadas del vértice B
float Cx = 0.0f, Cy = -0.5f; // Coordenadas del vértice C
float Dx = -0.5f, Dy = 0.0f; // Coordenadas del vértice D
float center_x = 0.0f, center_y = 0.0f; // Coordenadas del centro


int N = 10;  // Número de puntos a calcular en cada arista

void interpola(float x1, float y1, float x2, float y2, float t, float& x, float& y) {
	if (0.0 < t && t < 1.0) {
		x = (1 - t) * x1 + t * x2;
		y = (1 - t) * y1 + t * y2;
	}
}

// Función para dibujar el triángulo y los puntos interpolados
void dibujaCurvaParabolica() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar los puntos interpolados entre AB, BC y CA y conectarlos
    for (int i = 0; i <= N; i++) {
        float t = (float)i / N;

        // Variables para los puntos interpolados
		float PaCenter_x, PaCenter_y;
		float PCenter_xb, PCenter_yb;
		float PbCenter_x, PbCenter_y;
		float PCenter_xc, PCenter_yc;
		float PcCenter_x, PcCenter_y;
		float PCenter_xd, PCenter_yd;
		float PdCenter_x, PdCenter_y;
		float PCenter_xa, PCenter_ya;


		// Interpolaciones en las 4 aristas
		interpola(Ax, Ay, center_x, center_y, t, PaCenter_x, PaCenter_y);
		interpola(center_x, center_y, Bx, By, t, PCenter_xb, PCenter_yb);
		interpola(Bx, By, center_x, center_y, t, PbCenter_x, PbCenter_y);
		interpola(center_x, center_y, Cx, Cy, t, PCenter_xc, PCenter_yc);
		interpola(Cx, Cy, center_x, center_y, t, PcCenter_x, PcCenter_y);
		interpola(center_x, center_y, Dx, Dy, t, PCenter_xd, PCenter_yd);
		interpola(Dx, Dy, center_x, center_y, t, PdCenter_x, PdCenter_y);
		interpola(center_x, center_y, Ax, Ay, t, PCenter_xa, PCenter_ya);

        // Conexión entre los puntos
        glBegin(GL_LINES);

		// Línea entre PaCenter y PCentera
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(PaCenter_x, PaCenter_y);
        glVertex2f(PCenter_xb, PCenter_yb);

		// Línea entre PCenterb y PbCenter
		glVertex2f(PbCenter_x, PbCenter_y);
		glVertex2f(PCenter_xc, PCenter_yc);

		// Línea entre PCenterc y PcCenter
		glVertex2f(PcCenter_x, PcCenter_y);
		glVertex2f(PCenter_xd, PCenter_yd);

		// Línea entre PCenterd y PdCenter
		glVertex2f(PdCenter_x, PdCenter_y);
		glVertex2f(PCenter_xa, PCenter_ya);


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
