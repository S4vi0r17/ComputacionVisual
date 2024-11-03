/**
 * Autor: Eder Gustavo Benites Pardavé
 * Práctica Calificada 1
 * Fecha: 21/09/2024
 *
 * Descripción:
 * Este programa utiliza OpenGL y GLUT para dibujar una "espiral falsa" con un cuadrado y sus prolongaciones.
 * Se dibuja un cuadrado en el centro de la ventana, y desde cada vértice del cuadrado se generan prolongaciones
 * y segmentos de arcos que simulan una espiral alrededor de los vértices.
 *
 * Parámetros principales:
 * - L: Longitud de la arista del cuadrado.
 * - N: Número de vueltas de la espiral falsa.
 * - windowWidth y windowHeight: Dimensiones de la ventana gráfica.
 * - lineWidth: Grosor de las líneas.
 * - vertexRadius: Radio de los vértices para dibujar las prolongaciones.
 */

#include <GL/glut.h>
#include <cmath>

const int L = 100;  // Longitud de la arista del cuadrado
const int N = 5;    // Número de vueltas
const int windowWidth = 800;
const int windowHeight = 800;
const float pi = 3.14159265358979323846;  // Valor de pi

float lineWidth = 2.0f;  // Grosor de las líneas
float vertexRadius = 5.0f;  // Radio de los vértices

// Función para dibujar un píxel en una posición (x, y)
void drawPixel(int x, int y) {
    glVertex2i(x, y);
}

/**
 * Función para dibujar un cuarto de circunferencia en un cuadrante específico.
 *
 * Parámetros:
 * - xc, yc: Coordenadas del centro de la circunferencia.
 * - r: Radio de la circunferencia.
 * - quadrant: Cuadrante en el que se dibujará el arco (1 a 4).
 */
void drawQuarterCircle(int xc, int yc, int r, int quadrant) {
    int x = 0, y = r;
    int d = 3 - 2 * r;  // Decisión inicial para el algoritmo de dibujado

    glBegin(GL_POINTS);  // Inicia el modo de dibujo por puntos
    while (y >= x) {
        // Dibujar el cuarto de circunferencia basado en el cuadrante seleccionado
        switch (quadrant) {
        case 1: drawPixel(xc + x, yc + y); drawPixel(xc + y, yc + x); break;
        case 2: drawPixel(xc - y, yc + x); drawPixel(xc - x, yc + y); break;
        case 3: drawPixel(xc - x, yc - y); drawPixel(xc - y, yc - x); break;
        case 4: drawPixel(xc + y, yc - x); drawPixel(xc + x, yc - y); break;
        }

        // Actualizar las coordenadas del punto según el algoritmo de Bresenham
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else {
            d = d + 4 * x + 6;
        }
    }
    glEnd();  // Termina el modo de dibujo por puntos
}

/**
 * Función para dibujar la espiral falsa.
 *
 * Esta función dibuja un cuadrado y prolonga sus lados hacia afuera. Además,
 * añade arcos de circunferencias que simulan una espiral alrededor de cada vértice del cuadrado.
 */
void drawFalseSpiral() {
    // Definir los vértices del cuadrado
    float vertices[4][2] = {
        {-L / 2.0f, -L / 2.0f},  // V1: Esquina inferior izquierda
        {L / 2.0f, -L / 2.0f},   // V2: Esquina inferior derecha
        {L / 2.0f, L / 2.0f},    // V3: Esquina superior derecha
        {-L / 2.0f, L / 2.0f}    // V4: Esquina superior izquierda
    };

    // Dibujar el cuadrado
    glColor3f(0.0f, 0.0f, 0.0f);  // Color negro para el cuadrado
    glLineWidth(lineWidth);  // Establecer el grosor de las líneas

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();

    // Dibujar las prolongaciones de los lados del cuadrado
    glBegin(GL_LINES);
    for (int i = 0; i < 4; i++) {
        int next = (i + 1) % 4;  // Obtener el siguiente vértice
        float dx = vertices[next][0] - vertices[i][0];
        float dy = vertices[next][1] - vertices[i][1];
        glVertex2f(vertices[i][0], vertices[i][1]);
        glVertex2f(vertices[i][0] + (N + 1) * dx, vertices[i][1] + (N + 1) * dy);
    }
    glEnd();

    // Dibujar la espiral falsa (arcos alrededor de los vértices)
    glColor3f(1.0f, 0.0f, 0.0f);  // Color rojo para los arcos
    glPointSize(2.0f);  // Tamaño del punto para los arcos

    for (int n = 0; n < N * 4; n++) {
        int i = n % 4;  // Determinar el vértice base
        int xc = vertices[i][0];  // Coordenada X del vértice
        int yc = vertices[i][1];  // Coordenada Y del vértice
        int r = L * (n / 4 + 1);  // Radio del arco
        drawQuarterCircle(xc, yc, r, ((i + 3) % 4) + 1);  // Dibujar cuarto de circunferencia
    }
}

// Función de visualización, donde se llama a la función para dibujar la espiral falsa
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpiar el buffer de color
    drawFalseSpiral();  // Dibujar la espiral falsa
    glFlush();  // Forzar la ejecución de los comandos de OpenGL
}

// Inicialización de OpenGL, configurando el fondo y el modo de proyección
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Fondo blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, windowHeight / 2);  // Configurar el área visible
}

// Función principal que inicia GLUT y la ventana de OpenGL
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);  // Establecer el tamaño de la ventana
    glutInitWindowPosition(100, 100);  // Posicionar la ventana
    glutCreateWindow("Espiral Falsa con Cuadrado y Prolongaciones");

    init();  // Inicializar OpenGL
    glutDisplayFunc(display);  // Asignar la función de dibujo

    glutMainLoop();  // Iniciar el loop principal de GLUT
    return 0;
}
