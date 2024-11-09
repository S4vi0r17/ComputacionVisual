#include <GL/glut.h>
#include <vector>
#include <cmath>

// Variables globales
std::vector<std::pair<float, float>> controlPoints;
int windowWidth = 800;
int windowHeight = 600;
bool showPolyline = true;
bool showBSpline = true;
bool showAxes = true;
bool show3DRepresentation = false;
float curveColor[3] = { 0.0f, 0.0f, 1.0f }; // Color inicial: azul
float curveThickness = 2.0f;
float curve3DColor[3] = { 1.0f, 0.0f, 1.0f }; // Color inicial para la representación 3D: magenta
float curve3DThickness = 2.0f;
bool deleteMode = false; // Nueva variable para el modo de eliminación

// Variables para la rotación 3D
float angleX = 0.0f;
float angleY = 0.0f;
bool rotating = false;
int lastX = 0;
int lastY = 0;

// Prototipos de funciones
void initGL();
void drawGrid();
void drawAxes();
void drawPolyline();
void drawBSplineCurve();
float N(int i, int k, float t);
float knot(int i);
void drawLeftSection();
void drawRightSection();
void display();
void reshape(int width, int height);
void mouseClick(int button, int state, int x, int y);
void mouseDrag(int x, int y);
void menuEvents(int option);
void createMenus();
void draw3DRepresentation();
void drawBSplineCurve3D(); // Nuevo prototipo para dibujar la curva B-spline en 3D

// Funciones de inicialización
void initGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Fondo blanco
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST); // Habilitar prueba de profundidad para 3D
}

// Función para dibujar la cuadrícula
void drawGrid() {
    glColor3f(0.9f, 0.9f, 0.9f); // Color gris claro
    glBegin(GL_LINES);
    for (float i = -1.0f; i <= 1.0f; i += 0.1f) {
        glVertex2f(i, -1.0f);
        glVertex2f(i, 1.0f);
        glVertex2f(-1.0f, i);
        glVertex2f(1.0f, i);
    }
    glEnd();
}

// Función para dibujar los ejes coordenados
void drawAxes() {
    // Dibujar los ejes
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    // Eje X (rojo)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    // Eje Y (verde)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    // Eje Z (azul)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();

    // Dibujar las etiquetas
    glPushMatrix();

    // Etiqueta X
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo
    glRasterPos3f(1.1f, 0.0f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');

    // Etiqueta Y
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glRasterPos3f(0.0f, 1.1f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');

    // Etiqueta Z
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    glRasterPos3f(0.0f, 0.0f, 1.1f);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Z');

    glPopMatrix();

    // Dibujar pequeñas marcas en los ejes
    glBegin(GL_LINES);
    // Marcas en X
    glColor3f(1.0f, 0.0f, 0.0f);
    for (float i = -1.0f; i <= 1.0f; i += 0.2f) {
        glVertex3f(i, -0.02f, 0.0f);
        glVertex3f(i, 0.02f, 0.0f);
    }
    // Marcas en Y
    glColor3f(0.0f, 1.0f, 0.0f);
    for (float i = -1.0f; i <= 1.0f; i += 0.2f) {
        glVertex3f(-0.02f, i, 0.0f);
        glVertex3f(0.02f, i, 0.0f);
    }
    // Marcas en Z
    glColor3f(0.0f, 0.0f, 1.0f);
    for (float i = -1.0f; i <= 1.0f; i += 0.2f) {
        glVertex3f(0.0f, -0.02f, i);
        glVertex3f(0.0f, 0.02f, i);
    }
    glEnd();
}

// Función para dibujar la polilínea
void drawPolyline() {
    if (controlPoints.size() < 2) return;
    glColor3f(0.0f, 1.0f, 0.0f); // Color verde
    glLineWidth(1.0f);
    glBegin(GL_LINE_STRIP);
    for (auto& point : controlPoints) {
        glVertex2f(point.first, point.second);
    }
    glEnd();
}

// Función de base B-spline recursiva
float N(int i, int k, float t) {
    if (k == 1) {
        return (t >= knot(i) && t < knot(i + 1)) ? 1.0f : 0.0f;
    }
    else {
        float denom1 = knot(i + k - 1) - knot(i);
        float denom2 = knot(i + k) - knot(i + 1);
        float term1 = 0.0f;
        float term2 = 0.0f;

        if (denom1 != 0.0f) {
            term1 = ((t - knot(i)) / denom1) * N(i, k - 1, t);
        }
        if (denom2 != 0.0f) {
            term2 = ((knot(i + k) - t) / denom2) * N(i + 1, k - 1, t);
        }
        return term1 + term2;
    }
}

// Función para generar el vector de nudos
float knot(int i) {
    int n = controlPoints.size() - 1;
    int k = 4; // Orden de la B-spline (grado + 1)
    int m = n + k;
    if (i < k) return 0.0f;
    else if (i > m - k) return 1.0f;
    else return (float)(i - k + 1) / (m - 2 * k + 2);
}

// Función para calcular y dibujar la curva B-spline en 2D
void drawBSplineCurve() {
    if (controlPoints.size() < 4) return;
    glColor3fv(curveColor);
    glLineWidth(curveThickness);
    glBegin(GL_LINE_STRIP);
    for (float u = 0.0f; u <= 1.0f; u += 0.001f) {
        float x = 0.0f;
        float y = 0.0f;
        int n = controlPoints.size() - 1;
        for (int i = 0; i <= n; ++i) {
            float b = N(i, 4, u); // Grado cúbico
            x += b * controlPoints[i].first;
            y += b * controlPoints[i].second;
        }
        glVertex2f(x, y);
    }
    glEnd();
}

// Función para dibujar la curva B-spline en 3D
void drawBSplineCurve3D() {
    if (controlPoints.size() < 4) return;
    glColor3fv(curve3DColor);
    glLineWidth(curve3DThickness);
    glBegin(GL_LINE_STRIP);
    for (float u = 0.0f; u <= 1.0f; u += 0.001f) {
        float x = 0.0f;
        float y = 0.0f;
        int n = controlPoints.size() - 1;
        for (int i = 0; i <= n; ++i) {
            float b = N(i, 4, u); // Grado cúbico
            x += b * controlPoints[i].first;
            y += b * controlPoints[i].second;
        }
        glVertex3f(x, y, 0.0f); // Z = 0 para una línea plana en XY
    }
    glEnd();
}

// Función para dibujar la sección izquierda
void drawLeftSection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawGrid();

    // Dibujar puntos de control
    glPointSize(8.0f);
    if (deleteMode) {
        glColor3f(1.0f, 0.0f, 0.0f); // Rojo en modo eliminación
    }
    else {
        glColor3f(0.0f, 0.0f, 1.0f); // Azul en modo normal
    }
    glBegin(GL_POINTS);
    for (auto& point : controlPoints) {
        glVertex2f(point.first, point.second);
    }
    glEnd();

    if (showPolyline) {
        drawPolyline();
    }

    if (showBSpline) {
        drawBSplineCurve();
    }
}

// Función para dibujar la sección derecha
void drawRightSection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)(windowWidth / 2) / windowHeight, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 3.0, 3.0,   // Posición de la cámara
        0.0, 0.0, 0.0,   // Punto de referencia
        0.0, 1.0, 0.0);  // Vector arriba

    // Aplicar rotaciones
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    if (showAxes) {
        drawAxes();
    }

    if (show3DRepresentation) {
        draw3DRepresentation();
    }
}

// Función para dibujar la representación 3D
void draw3DRepresentation() {
    if (controlPoints.size() < 4) return;
    drawBSplineCurve3D();
}

// Función para manejar el evento de dibujo
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Dibujar la sección izquierda
    glViewport(0, 0, windowWidth / 2, windowHeight);
    drawLeftSection();

    // Dibujar la sección derecha
    glViewport(windowWidth / 2, 0, windowWidth / 2, windowHeight);
    drawRightSection();

    glutSwapBuffers();
}

// Función para manejar el redimensionamiento de la ventana
void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glutPostRedisplay();
}

// Variables para mover puntos de control
bool dragging = false;
int selectedPoint = -1;

// Función para manejar clic del ratón
void mouseClick(int button, int state, int x, int y) {
    if (x <= windowWidth / 2) {
        float worldX = ((float)x / (windowWidth / 2)) * 2 - 1;
        float worldY = 1 - ((float)y / windowHeight) * 2;

        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            // Verificar si se ha seleccionado un punto existente
            for (int i = 0; i < (int)controlPoints.size(); ++i) {
                float dx = worldX - controlPoints[i].first;
                float dy = worldY - controlPoints[i].second;
                if (sqrt(dx * dx + dy * dy) < 0.05f) {
                    if (deleteMode) {
                        // Eliminar el punto de control
                        controlPoints.erase(controlPoints.begin() + i);
                        glutPostRedisplay();
                        return;
                    }
                    else {
                        // Iniciar arrastre
                        dragging = true;
                        selectedPoint = i;
                        return;
                    }
                }
            }
            if (!deleteMode) {
                // Agregar nuevo punto de control
                controlPoints.push_back(std::make_pair(worldX, worldY));
                glutPostRedisplay();
            }
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
            dragging = false;
            selectedPoint = -1;
        }
    }
    else {
        // Manejo de la rotación en la sección derecha
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                rotating = true;
                lastX = x;
                lastY = y;
            }
            else {
                rotating = false;
            }
        }
    }

}

// Función para manejar el arrastre del ratón
void mouseDrag(int x, int y) {
    if (x <= windowWidth / 2) {
        // Código existente para la sección izquierda
        if (dragging && selectedPoint != -1) {
            float worldX = ((float)x / (windowWidth / 2)) * 2 - 1;
            float worldY = 1 - ((float)y / windowHeight) * 2;
            controlPoints[selectedPoint].first = worldX;
            controlPoints[selectedPoint].second = worldY;
            glutPostRedisplay();
        }
    }
    else {
        // Manejo de la rotación en la sección derecha
        if (rotating) {
            angleY += (x - lastX) * 0.5f;
            angleX += (y - lastY) * 0.5f;

            // Normalizar ángulos
            if (angleY > 360.0f) angleY -= 360.0f;
            if (angleY < -360.0f) angleY += 360.0f;
            if (angleX > 360.0f) angleX -= 360.0f;
            if (angleX < -360.0f) angleX += 360.0f;

            lastX = x;
            lastY = y;
            glutPostRedisplay();
        }
    }
}

// Función para manejar las entradas del menú
void menuEvents(int option) {
    switch (option) {
    case 0: // Salir
        exit(0);
        break;
    case 1: // Ingresar puntos de control (no acción necesaria)
        break;
    case 2: // Mostrar polilínea
        showPolyline = !showPolyline;
        break;
    case 3: // Mostrar curva B-spline
        showBSpline = !showBSpline;
        break;
    case 4: // Mover puntos de control (no acción necesaria)
        break;
    case 5: // Mostrar ejes coordenados
        showAxes = !showAxes;
        break;
    case 6: // Mostrar representación 3D
        show3DRepresentation = !show3DRepresentation;
        break;
    case 7: // Eliminar puntos de control
        deleteMode = !deleteMode;
        break;
        // Opciones para cambiar el color de la curva
    case 10: // Rojo
        curveColor[0] = 1.0f; curveColor[1] = 0.0f; curveColor[2] = 0.0f;
        break;
    case 11: // Verde
        curveColor[0] = 0.0f; curveColor[1] = 1.0f; curveColor[2] = 0.0f;
        break;
    case 12: // Azul
        curveColor[0] = 0.0f; curveColor[1] = 0.0f; curveColor[2] = 1.0f;
        break;
        // Opciones para cambiar el grosor de la curva
    case 20:
        curveThickness = 1.0f;
        break;
    case 21:
        curveThickness = 2.0f;
        break;
    case 22:
        curveThickness = 3.0f;
        break;
        // Cambiar color de la superficie derecha (ejemplo simple)
    case 30: // Cambiar a color amarillo
        glClearColor(1.0, 1.0, 0.0, 1.0); // Fondo amarillo
        break;
    case 31: // Cambiar a color blanco
        glClearColor(1.0, 1.0, 1.0, 1.0); // Fondo blanco
        break;
        // Opciones para cambiar el color de la representación 3D
    case 40: // Rojo
        curve3DColor[0] = 1.0f; curve3DColor[1] = 0.0f; curve3DColor[2] = 0.0f;
        break;
    case 41: // Verde
        curve3DColor[0] = 0.0f; curve3DColor[1] = 1.0f; curve3DColor[2] = 0.0f;
        break;
    case 42: // Azul
        curve3DColor[0] = 0.0f; curve3DColor[1] = 0.0f; curve3DColor[2] = 1.0f;
        break;
        // Opciones para cambiar el grosor de la representación 3D
    case 50:
        curve3DThickness = 1.0f;
        break;
    case 51:
        curve3DThickness = 2.0f;
        break;
    case 52:
        curve3DThickness = 3.0f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

// Función para crear los menús
void createMenus() {
    int submenuColorCurve = glutCreateMenu(menuEvents);
    glutAddMenuEntry("Rojo", 10);
    glutAddMenuEntry("Verde", 11);
    glutAddMenuEntry("Azul", 12);

    int submenuThicknessCurve = glutCreateMenu(menuEvents);
    glutAddMenuEntry("Grosor 1", 20);
    glutAddMenuEntry("Grosor 2", 21);
    glutAddMenuEntry("Grosor 3", 22);

    int submenuColorSurface = glutCreateMenu(menuEvents);
    glutAddMenuEntry("Amarillo", 30);
    glutAddMenuEntry("Blanco", 31);

    int submenuColor3D = glutCreateMenu(menuEvents);
    glutAddMenuEntry("Rojo", 40);
    glutAddMenuEntry("Verde", 41);
    glutAddMenuEntry("Azul", 42);

    int submenuThickness3D = glutCreateMenu(menuEvents);
    glutAddMenuEntry("Grosor 1", 50);
    glutAddMenuEntry("Grosor 2", 51);
    glutAddMenuEntry("Grosor 3", 52);

    int mainMenu = glutCreateMenu(menuEvents);
    glutAddMenuEntry("Ingresar puntos de control", 1);
    glutAddMenuEntry("Mostrar/ocultar polilínea", 2);
    glutAddMenuEntry("Mostrar/ocultar curva B-spline", 3);
    glutAddMenuEntry("Mover puntos de control", 4);
    glutAddMenuEntry("Mostrar/ocultar ejes coordenados", 5);
    glutAddMenuEntry("Mostrar/ocultar representación 3D", 6);
    glutAddMenuEntry("Eliminar puntos de control", 7); // Nueva opción en el menú
    glutAddSubMenu("Cambiar color de la curva", submenuColorCurve);
    glutAddSubMenu("Cambiar grosor de la curva", submenuThicknessCurve);
    glutAddSubMenu("Cambiar color de la representación 3D", submenuColor3D);
    glutAddSubMenu("Cambiar grosor de la representación 3D", submenuThickness3D);
    glutAddSubMenu("Cambiar color de la superficie derecha", submenuColorSurface);
    glutAddMenuEntry("Salir de la aplicación", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Aplicación de Curvas B-spline");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseDrag);
    createMenus();

    glutMainLoop();
    return 0;
}
