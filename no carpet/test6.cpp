#include <GL/glut.h>
#include <vector>
#include <iostream>

struct Point {
    float x, y;
};

std::vector<Point> controlPoints;
bool ingresoActivo = false;      // Activar/desactivar ingreso de puntos de control
bool mostrarBSpline = false;     // Activar/desactivar la curva B-Spline
bool moverPuntosActivo = false;  // Activar/desactivar movimiento de puntos de control
bool puntoSeleccionado = false;  // Indica si hay un punto seleccionado para mover
int puntoIndiceSeleccionado = -1; // Índice del punto seleccionado para mover

void drawControlPoints();
void drawBSplineCurve();
void draw3DAxes();
void drawBSplineCurve3D();

void mouse(int button, int state, int x, int y) {
    if (x < 500) { // Solo interactúa en la mitad izquierda
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH) / 2;
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        float posX = (float(x) / windowWidth) * 2 - 1;
        float posY = 1 - (float(y) / windowHeight) * 2;

        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            if (moverPuntosActivo) {
                // Buscar un punto cercano para mover
                for (int i = 0; i < controlPoints.size(); ++i) {
                    if (std::sqrt(std::pow(controlPoints[i].x - posX, 2) + std::pow(controlPoints[i].y - posY, 2)) < 0.05) {
                        puntoSeleccionado = true;
                        puntoIndiceSeleccionado = i;
                        break;
                    }
                }
            }
            else if (ingresoActivo) {
                // Agregar un nuevo punto de control
                controlPoints.push_back({ posX, posY });
            }
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
            puntoSeleccionado = false; // Soltar el punto seleccionado
        }
    }
    glutPostRedisplay();
}

void draw3DAxes() {
    // Draw X axis in red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    // Draw Y axis in green
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    // Draw Z axis in blue
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

void motion(int x, int y) {
    if (puntoSeleccionado && moverPuntosActivo && puntoIndiceSeleccionado != -1) {
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH) / 2;
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        float posX = (float(x) / windowWidth) * 2 - 1;
        float posY = 1 - (float(y) / windowHeight) * 2;

        // Mueve el punto seleccionado a la nueva posición del mouse
        controlPoints[puntoIndiceSeleccionado] = { posX, posY };
        glutPostRedisplay();
    }
}

void drawControlPoints() {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (const auto& point : controlPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (const auto& point : controlPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

// Función para dibujar la curva B-Spline cúbica en 2D
void drawBSplineCurve() {
    if (controlPoints.size() < 4) return; // Se necesitan al menos 4 puntos para una B-Spline cúbica

    glColor3f(0.0, 0.0, 1.0); // Azul para la curva B-Spline
    glBegin(GL_LINE_STRIP);

    for (int i = 1; i < controlPoints.size() - 2; ++i) {
        for (float t = 0; t <= 1; t += 0.05f) {
            float t2 = t * t;
            float t3 = t2 * t;

            // Coeficientes de la B-Spline cúbica
            float b0 = (-t3 + 3 * t2 - 3 * t + 1) / 6.0;
            float b1 = (3 * t3 - 6 * t2 + 4) / 6.0;
            float b2 = (-3 * t3 + 3 * t2 + 3 * t + 1) / 6.0;
            float b3 = t3 / 6.0;

            // Calcular posición en la curva
            float x = b0 * controlPoints[i - 1].x +
                b1 * controlPoints[i].x +
                b2 * controlPoints[i + 1].x +
                b3 * controlPoints[i + 2].x;
            float y = b0 * controlPoints[i - 1].y +
                b1 * controlPoints[i].y +
                b2 * controlPoints[i + 1].y +
                b3 * controlPoints[i + 2].y;

            glVertex2f(x, y);
        }
    }

    glEnd();
}

void drawBSplineSurface3D() {
    if (controlPoints.size() < 4) return;

    glColor4f(1.0, 0.0, 1.0, 0.7); // Color para la superficie de la curva, con transparencia
    float height = 1.0; // Altura a la que se extiende la curva en el eje Y

    glBegin(GL_QUAD_STRIP); // Usa QUAD_STRIP para crear una superficie

    for (int i = 1; i < controlPoints.size() - 2; ++i) {
        for (float t = 0; t <= 1; t += 0.05f) {
            float t2 = t * t;
            float t3 = t2 * t;

            // Coeficientes de la B-Spline cúbica
            float b0 = (-t3 + 3 * t2 - 3 * t + 1) / 6.0;
            float b1 = (3 * t3 - 6 * t2 + 4) / 6.0;
            float b2 = (-3 * t3 + 3 * t2 + 3 * t + 1) / 6.0;
            float b3 = t3 / 6.0;

            // Calcular posición en la curva en el plano XZ
            float x = b0 * controlPoints[i - 1].x +
                b1 * controlPoints[i].x +
                b2 * controlPoints[i + 1].x +
                b3 * controlPoints[i + 2].x;
            float z = b0 * controlPoints[i - 1].y +
                b1 * controlPoints[i].y +
                b2 * controlPoints[i + 1].y +
                b3 * controlPoints[i + 2].y;

            // Dibuja dos puntos: uno en la base y otro en la altura para crear una superficie
            glVertex3f(x, 0.0, z);       // Punto en la base (altura 0)
            glVertex3f(x, height, z);    // Punto en la parte superior (altura 'height')
        }
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Viewport izquierdo para los puntos de control y la curva B-Spline en 2D
    glViewport(0, 0, 500, 500); // Vista en la mitad izquierda
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawControlPoints();
    if (mostrarBSpline) {
        drawBSplineCurve(); // Dibuja la curva B-Spline en el plano 2D si está activada
    }

    // Viewport derecho para los ejes 3D y la curva en el espacio 3D
    glViewport(500, 0, 500, 500); // Vista en la mitad derecha
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0); // Perspectiva para la vista 3D
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0); // Aleja la cámara para ver los ejes
    glRotatef(25, 1.0, 0.0, 0.0); // Rotación para ver los ejes en 3D
    glRotatef(45, 0.0, 1.0, 0.0);

    draw3DAxes();
    if (mostrarBSpline) {
        drawBSplineSurface3D(); // Dibuja la superficie en el espacio 3D
    }

    glFlush();
}

// Función para manejar el submenú de mostrar la curva B-Spline
void menuDisplay(int option) {
    if (option == 1) {
        mostrarBSpline = true; // Activar la curva B-Spline
    }
    else if (option == 2) {
        mostrarBSpline = false; // Desactivar la curva B-Spline
    }
    glutPostRedisplay();
}

void menuControlPoints(int option) {
    if (option == 1) {
        ingresoActivo = true; // Activar ingreso de puntos
    }
    else if (option == 2) {
        ingresoActivo = false; // Desactivar ingreso de puntos
    }
}

void menuColor(int option) {
    switch (option) {
    case 1: glColor3f(1.0, 0.0, 0.0); break; // Rojo
    case 2: glColor3f(0.0, 1.0, 0.0); break; // Verde
    case 3: glColor3f(0.0, 0.0, 1.0); break; // Azul
    }
    glutPostRedisplay();
}

void menuThickness(int option) {
    switch (option) {
    case 1: glLineWidth(1.0f); break;  // Fino
    case 2: glLineWidth(3.0f); break;  // Medio
    case 3: glLineWidth(5.0f); break;  // Grueso
    }
    glutPostRedisplay();
}

void mainMenu(int option) {
    if (option == 0) {
        exit(0); // Salir de la aplicación
    }
}

void menuMoverPuntos(int option) {
    if (option == 1) {
        moverPuntosActivo = true; // Activar mover puntos
        ingresoActivo = false;    // Desactivar ingreso de puntos
    }
    else if (option == 2) {
        moverPuntosActivo = false; // Desactivar mover puntos
    }
}

void createMenu() {
    int controlPointsToggleMenu = glutCreateMenu(menuControlPoints);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 2);

    int moverPuntosMenu = glutCreateMenu(menuMoverPuntos);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 2);

    int displayMenu = glutCreateMenu(menuDisplay);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 2);

    int colorMenu = glutCreateMenu(menuColor);
    glutAddMenuEntry("Rojo", 1);
    glutAddMenuEntry("Verde", 2);
    glutAddMenuEntry("Azul", 3);

    int thicknessMenu = glutCreateMenu(menuThickness);
    glutAddMenuEntry("Fino", 1);
    glutAddMenuEntry("Medio", 2);
    glutAddMenuEntry("Grueso", 3);

    int mainMenuID = glutCreateMenu(mainMenu);
    glutAddSubMenu("Ingresar puntos de control", controlPointsToggleMenu);
    glutAddSubMenu("Mover puntos de control", moverPuntosMenu);
    glutAddSubMenu("Mostrar curva B-Spline", displayMenu); // Cambiado a "Mostrar curva B-Spline"
    glutAddSubMenu("Cambiar color de la curva", colorMenu);
    glutAddSubMenu("Cambiar grosor de la curva", thicknessMenu);
    glutAddMenuEntry("Salir de la aplicación", 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 500);
    glutCreateWindow("Curva B-Spline y Ejes 3D con menú interactivo");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    createMenu();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
