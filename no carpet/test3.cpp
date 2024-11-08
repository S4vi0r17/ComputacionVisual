#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

void menu_principal(int);
void menu_modelo(int);
void menu_color(int);
void menu_grosor(int);
void menu_coordenadas(int);
void menu_figuras3D(int);

GLdouble angulo = 0;
GLint modelo = 0;
GLint sistema_coordenadas = 0; // 0 = cartesiano, 1 = polar
GLfloat grosor_linea = 2.0f;   // Grosor inicial de la línea

// Funciones para dibujar figuras 2D
void Circunferencia(void) {
    float ang, radio = 8.0f, x, y;
    glBegin(GL_LINE_LOOP);
    for (ang = 0.0; ang < 2 * M_PI; ang += 2 * M_PI / 50) {
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}
void menu_principal(int opcion) {
    // Implementación vacía o acciones adicionales si es necesario
}

void Caracol(void) {
    float ang, radio, x, y;
    glBegin(GL_LINE_LOOP);
    for (ang = 0.0; ang < 2 * M_PI; ang += 2 * M_PI / 50) {
        radio = 4 + 4 * sin(ang);
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}

void Rosal(void) {
    float ang, radio, x, y;
    glBegin(GL_LINE_LOOP);
    for (ang = 0.0; ang < 2 * M_PI; ang += 2 * M_PI / 50) {
        radio = 6 * cos(2 * ang);
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}

void Estrella(void) {
    float ang, radio;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; i++) {
        ang = i * M_PI / 5;
        radio = (i % 2 == 0) ? 8.0f : 4.0f;
        glVertex2f(radio * cos(ang), radio * sin(ang));
    }
    glEnd();
}

void Espiral(void) {
    float ang, radio = 0.5f, x, y;
    glBegin(GL_LINE_STRIP);
    for (ang = 0.0; ang < 4 * M_PI; ang += 0.1) {
        radio += 0.1f;
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();
}

void Triangulo(void) {
    glBegin(GL_TRIANGLES);
    glVertex2f(-5.0, -5.0);
    glVertex2f(5.0, -5.0);
    glVertex2f(0.0, 5.0);
    glEnd();
}

// Función para el cubo en 3D
void cubo(void) {
    glutWireCube(2);
}

void iniciar(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(grosor_linea);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    switch (modelo) {
    case 1: Circunferencia(); break;
    case 2: Caracol(); break;
    case 3: Rosal(); break;
    case 4: Estrella(); break;
    case 5: Espiral(); break;
    case 6: Triangulo(); break;
    case 7: cubo(); break;
    }

    glFlush();
    glutSwapBuffers();
}

void ajustarSistemaCoordenadas() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (sistema_coordenadas == 0) {
        glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    }
    else {
        gluPerspective(60, 1, 1.0, 30.0);
        glTranslatef(0.0, 0.0, -20.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}

void myReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    ajustarSistemaCoordenadas();
}

void menu_color(int opcion) {
    switch (opcion) {
    case 1: glColor3f(1.0, 0.0, 0.0); break;
    case 2: glColor3f(0.0, 1.0, 0.0); break;
    case 3: glColor3f(0.0, 0.0, 1.0); break;
    case 4: glColor3f(0.0, 0.0, 0.0); break;
    }
    glutPostRedisplay();
}

void menu_grosor(int opcion) {
    switch (opcion) {
    case 1: grosor_linea = 1.0f; break;
    case 2: grosor_linea = 3.0f; break;
    case 3: grosor_linea = 5.0f; break;
    }
    glLineWidth(grosor_linea);
    glutPostRedisplay();
}

void menu_modelo(int opcion) {
    modelo = opcion;
    glutPostRedisplay();
}

void menu_coordenadas(int opcion) {
    sistema_coordenadas = opcion;
    ajustarSistemaCoordenadas();
}

void menu_figuras3D(int opcion) {
    if (opcion == 1) {
        modelo = 7;
    }
    else if (opcion == 4) {
        exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Modelos 2D y 3D con control de color y grosor");

    int submenu_color = glutCreateMenu(menu_color);
    glutAddMenuEntry("Rojo", 1);
    glutAddMenuEntry("Verde", 2);
    glutAddMenuEntry("Azul", 3);
    glutAddMenuEntry("Negro", 4);

    int submenu_grosor = glutCreateMenu(menu_grosor);
    glutAddMenuEntry("Fino", 1);
    glutAddMenuEntry("Medio", 2);
    glutAddMenuEntry("Grueso", 3);

    int submenu_modelo = glutCreateMenu(menu_modelo);
    glutAddMenuEntry("Circunferencia", 1);
    glutAddMenuEntry("Caracol", 2);
    glutAddMenuEntry("Rosal", 3);
    glutAddMenuEntry("Estrella", 4);
    glutAddMenuEntry("Espiral", 5);
    glutAddMenuEntry("Triangulo", 6);

    int submenu_coordenadas = glutCreateMenu(menu_coordenadas);
    glutAddMenuEntry("Cartesianas", 0);
    glutAddMenuEntry("Polares", 1);

    int submenu_figuras3D = glutCreateMenu(menu_figuras3D);
    glutAddMenuEntry("Cubo", 1);
    glutAddMenuEntry("Salir", 4);

    int menu = glutCreateMenu(menu_principal);
    glutAddSubMenu("Color", submenu_color);
    glutAddSubMenu("Grosor", submenu_grosor);
    glutAddSubMenu("Modelo", submenu_modelo);
    glutAddSubMenu("Sistema de Coordenadas", submenu_coordenadas);
    glutAddSubMenu("Figuras 3D", submenu_figuras3D);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
