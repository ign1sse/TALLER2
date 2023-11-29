#include <iostream>
#include <vector>

using namespace std;

// Implementamos el juego 'Conecta 4' en C++.

// Constantes para representar el tablero
const int FILAS = 6;
const int COLUMNAS = 7;
const char VACIO = ' ';
const char ROJO = 'X';
const char AMARILLO = 'O';

// Función para crear un tablero vacío
vector<vector<char>> crearTablero() {
    vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, VACIO));
    return tablero;
}

// Función para imprimir el tablero
void imprimirTablero(vector<vector<char>> tablero) {
    for (int i = 0; i < FILAS; i++) {
        cout << "|";
        for (int j = 0; j < COLUMNAS; j++) {
            cout << tablero[i][j] << "|";
        }
        cout << endl;
    }
    cout << "---------------" << endl;
}

// Función para insertar una ficha en el tablero
void insertarFicha(vector<vector<char>> &tablero, int columna, char ficha) {
    // Recorremos la columna de abajo hacia arriba
    for (int i = FILAS - 1; i >= 0; i--) {
        // Si encontramos una casilla vacía, insertamos la ficha
        if (tablero[i][columna] == VACIO) {
            tablero[i][columna] = ficha;
            break;
        }
    }
}

// Función principal
int main() {
    // Creamos el tablero
    vector<vector<char>> tablero = crearTablero();

    // Elección de la ficha
    char fichaMaquina;
    do {
        // Le preguntamos al usuario qué color de ficha quiere
        cout << "¿Qué ficha quieres? (X/O): ";
        char ficha;
        cin >> ficha;
        // Si el usuario introduce un color válido
        if (ficha == ROJO || ficha == AMARILLO) {
            // Asignamos la ficha de la maquina
            fichaMaquina = (ficha == ROJO) ? AMARILLO : ROJO;
            // Salimos del bucle
            break;
        } else {
            // Si el usuario introduce un color no válido, le avisamos
            cout << "Ficha no válida" << endl;
        }
    } while (true);

    // Elección de la dificultad
    do {
        // Le preguntamos al usuario qué dificultad quiere
        cout << "¿Qué dificultad quieres? (1/2/3): ";
        int dificultad;
        cin >> dificultad;
        if (dificultad == 1 || dificultad == 2 || dificultad == 3) {
            // Si el usuario introduce una dificultad válida, salimos del bucle
            break;
        } else {
            // Si el usuario introduce una dificultad no válida, le avisamos
            cout << "Dificultad no válida" << endl;
        }
    } while (true);

    // Variable para saber si el juego ha terminado
    bool gameOver = false;

    // Variable para saber de quién es el turno
    bool turnoJugador = true;

    // Bucle principal del juego
    while (!gameOver) {
        // Imprimimos el tablero
        imprimirTablero(tablero);

        // Si no es el turno de jugador
        if (!turnoJugador) {
            // Calculamos el movimiento de la máquina
            int movimiento = calcularMovimiento(tablero, dificultad);
            // Insertamos la ficha en el tablero
            insertarFicha(tablero, movimiento, AMARILLO);
        }

        // Variable para saber si se ha insertado la ficha
        bool fichaInsertada = false;

        // Bucle para insertar la ficha
        while (!fichaInsertada) {
            // Le preguntamos al usuario en qué columna quiere insertar la ficha
            cout << "¿En qué columna quieres insertar la ficha? (1-7): ";
            int columna;
            cin >> columna;
            columna--;

            // Si la columna es válida, insertamos la ficha
            if (columna >= 0 && columna < COLUMNAS) {
                // Si la columna está llena, le avisamos al usuario
                if (tablero[0][columna] != VACIO) {
                    cout << "Columna llena" << endl;
                } else {
                    // Si la columna no está llena, insertamos la ficha
                    if (turnoRojo) {
                        insertarFicha(tablero, columna, ROJO);
                    } else {
                        insertarFicha(tablero, columna, AMARILLO);
                    }
                    // Salimos del bucle
                    fichaInsertada = true;
                }
            } else {
                // Si la columna no es válida, le avisamos al usuario
                cout << "Columna no válida" << endl;
            }
        }
    }
}