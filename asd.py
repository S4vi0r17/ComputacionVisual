import numpy as np

# Definir la matriz de reflexión respecto a la línea y = x
M_reflexion = np.array([[0, 1, 0],
                        [1, 0, 0],
                        [0, 0, 1]])

# Función para aplicar la transformación a un punto
def reflexionar_punto(punto):
    # Asegurar que el punto tenga coordenadas homogéneas (x, y, 1)
    punto_homogeneo = np.array([punto[0], punto[1], 1])
    
    # Aplicar la matriz de reflexión
    punto_reflejado = np.dot(M_reflexion, punto_homogeneo)
    
    # Retornar el resultado (sin la coordenada homogénea)
    return punto_reflejado[:2]

# Ejemplo de uso
punto_original = [2, 3]
punto_reflejado = reflexionar_punto(punto_original)

print("Punto original:", punto_original)
print("Punto reflejado respecto a y = x:", punto_reflejado)
