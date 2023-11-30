#include <random> // Para usar la librería <random>
#include <iostream> // Para usar cout

using namespace std;

const int COLUMNAS = 7;

int main() {
    // Crear un objeto de tipo random_device para obtener un valor aleatorio de la fuente de entropía del sistema
    random_device rd;

    // Crear un objeto de tipo mt19937 para usar el algoritmo Mersenne Twister como motor de generación de números pseudoaleatorios
    mt19937 mt(rd());

    // Crear un objeto de tipo uniform_int_distribution para usar una distribución uniforme de enteros en el rango [0, COLUMNAS - 1]
    uniform_int_distribution<int> dist(0, COLUMNAS - 1);

    // Generar un número aleatorio usando el motor y la distribución creados
    int num = dist(mt);

    // Mostrar el número generado por pantalla
    cout << "El número aleatorio es: " << num << endl;

    num = dist(mt);

    cout << "El número aleatorio es: " << num << endl;

    return 0;
}
