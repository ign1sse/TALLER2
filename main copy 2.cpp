// Implementación del juego 'Conecta 4' en C++.

// Librerías
#include <iostream> // Para usar cout y cin
#include <vector> // Para usar vectores
#include <random> // Para obtener números aleatorios
#include <windows.h> // Para usar SetConsoleTextAttribute() y cambiar el color de la consola

using namespace std;

// Constantes para representar el tablero
const int FILAS = 3;
const int COLUMNAS = 3;
const char VACIO = ' ';
const char ROJO = 'X';
const char AMARILLO = 'O';

// Crear un objeto de tipo random_device para obtener un valor aleatorio de la fuente de entropía del sistema
random_device rd;
// Crear un objeto de tipo mt19937 para usar el algoritmo Mersenne Twister como motor de generación de números pseudoaleatorios
mt19937 mt(rd());
// Crear un objeto de tipo uniform_int_distribution para usar una distribución uniforme de enteros en el rango [0, COLUMNAS - 1]
uniform_int_distribution<int> dist(0, COLUMNAS - 1);

// Obtener el manejador de la consola actual
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Función para crear un tablero vacío
vector<vector<char>> crearTablero() {
    vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, VACIO));
    return tablero;
}

// Función para imprimir el tablero
void imprimirTablero(vector<vector<char>> tablero) {
    // Imprimimos los números de las columnas
    for (int i = 0; i < COLUMNAS; i++) {
        cout << " " << i + 1;
    }
    cout << endl;
    for (int i = 0; i < FILAS; i++) {
        cout << "|";
        for (int j = 0; j < COLUMNAS; j++) {
            // Cambiamos el color de la consola
            if (tablero[i][j] == ROJO) {
                SetConsoleTextAttribute(hConsole, 12);
            } else if (tablero[i][j] == AMARILLO) {
                SetConsoleTextAttribute(hConsole, 14);
            }
            // Imprimimos la ficha
            cout << tablero[i][j];
            // Cambiamos el color de la consola al por defecto
            SetConsoleTextAttribute(hConsole, 7);
            cout << "|";
        }
        cout << endl;
    }
    for (int i = 0; i < COLUMNAS; i++) {
        cout << "---";
    }
    cout << endl << endl;
}

// Función para comprobar si un movimiento es válido
bool movimientoValido(vector<vector<char>> tablero, int columna) {
    if (columna >= 0 && columna < COLUMNAS) {
        if (tablero[0][columna] == VACIO) {
            return true;
        }
    }
    return false;
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

// Función para deshacer movimiento
void deshacerMovimiento(vector<vector<char>> &tablero, int columna) {
    // Recorremos la columna de arriba hacia abajo
    for (int i = 0; i < FILAS; i++) {
        // Si encontramos una casilla con una ficha, la eliminamos
        if (tablero[i][columna] != VACIO) {
            tablero[i][columna] = VACIO;
            break;
        }
    }
}

// Función para comprobar si un jugador ha ganado
// Si nadie ha ganado, devolvemos 0
// Si gana el jugador 1 (usuario), devolvemos 1
// Si gana el jugador 2 (maquina), devolvemos 2
// Si hay un empate, devolvemos 3
int comprobarGanador(vector<vector<char>> tablero) {
    // Variable para saber si hay un ganador
    int ganador = 0;
    // Comprobamos si hay un ganador en las filas
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] != VACIO && tablero[i][j] == tablero[i][j + 1] && tablero[i][j] == tablero[i][j + 2] && tablero[i][j] == tablero[i][j + 3]) {
                ganador = (tablero[i][j] == ROJO) ? 1 : 2;
            }
        }
    }
    // Comprobamos si hay un ganador en las columnas
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] != VACIO && tablero[i][j] == tablero[i + 1][j] && tablero[i][j] == tablero[i + 2][j] && tablero[i][j] == tablero[i + 3][j]) {
                ganador = (tablero[i][j] == ROJO) ? 1 : 2;
            }
        }
    }
    // Comprobamos si hay un ganador en las diagonales (de izquierda a derecha)
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] != VACIO && tablero[i][j] == tablero[i + 1][j + 1] && tablero[i][j] == tablero[i + 2][j + 2] && tablero[i][j] == tablero[i + 3][j + 3]) {
                ganador = (tablero[i][j] == ROJO) ? 1 : 2;
            }
        }
    }
    // Comprobamos si hay un ganador en las diagonales (de derecha a izquierda)
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 3; j < COLUMNAS; j++) {
            if (tablero[i][j] != VACIO && tablero[i][j] == tablero[i + 1][j - 1] && tablero[i][j] == tablero[i + 2][j - 2] && tablero[i][j] == tablero[i + 3][j - 3]) {
                ganador = (tablero[i][j] == ROJO) ? 1 : 2;
            }
        }
    }
    // Variable para saber si hay un empate
    bool hayEmpate = true;
    // Comprobamos si hay un empate
    for (int i = 0; i < COLUMNAS; i++) {
        if (tablero[0][i] == VACIO) {
            hayEmpate = false;
        }
    }
    if (!ganador && hayEmpate) {
        ganador = 3;
    }
    // Devolvemos el ganador
    return ganador;
}

// Función minimax para calcular el movimiento de la máquina
int minimax(vector<vector<char>> tablero, int profundidad, bool turnoMaquina) {
    // Comprobamos si hay un ganador
    int ganador = comprobarGanador(tablero);
    // Si el jugador ha ganado, devolvemos -10
    if (ganador == 1) {
        return -10;
    // Si la máquina ha ganado, devolvemos 10
    } else if (ganador == 2) {
        return 10;
    // Si hay un empate, devolvemos 0
    } else if (ganador == 3) {
        return 0;
    }
    // Si no hay ganador, calculamos el valor de la función minimax
    if (turnoMaquina) {
        // Variable para saber el mejor valor
        int mejorValor = -1000;
        // Recorremos las columnas
        for (int i = 0; i < COLUMNAS; i++) {
            // Si el movimiento es válido
            if (movimientoValido(tablero, i)) {
                // Insertamos la ficha en el tablero
                insertarFicha(tablero, i, AMARILLO);
                // Calculamos el valor de la función minimax
                int valor = minimax(tablero, profundidad + 1, false);
                // Deshacemos el movimiento
                deshacerMovimiento(tablero, i);
                // Si el valor es mayor que el mejor valor
                if (valor > mejorValor) {
                    // Actualizamos el mejor valor
                    mejorValor = valor;
                }
            }
        }
        // Devolvemos el mejor valor
        return mejorValor;
    } else {
        // Variable para saber el mejor valor
        int mejorValor = 1000;
        // Recorremos las columnas
        for (int i = 0; i < COLUMNAS; i++) {
            // Si el movimiento es válido
            if (movimientoValido(tablero, i)) {
                // Insertamos la ficha en el tablero
                insertarFicha(tablero, i, ROJO);
                // Calculamos el valor de la función minimax
                int valor = minimax(tablero, profundidad + 1, true);
                // Deshacemos el movimiento
                deshacerMovimiento(tablero, i);
                // Si el valor es menor que el mejor valor
                if (valor < mejorValor) {
                    // Actualizamos el mejor valor
                    mejorValor = valor;
                }
            }
        }
        // Devolvemos el mejor valor
        return mejorValor;
    }
}

// Función para calcular el movimiento de la máquina
int calcularMovimiento(vector<vector<char>> tablero, int dificultad) {
    // Variable para saber en qué columna insertar la ficha
    int columna = 0;
    // Si la dificultad es 1 la maquina hará un movimiento aleatorio
    if (dificultad == 1) {
        do {
            // Obtenemos un número aleatorio entre 0 y COLUMNAS - 1
            columna = dist(mt);
        } while (!movimientoValido(tablero, columna));
    // Si la dificultad es 2 la maquina hará un movimiento inteligente (si puede ganar, ganará; si no, evitará que el usuario gane)
    } else if (dificultad == 2) {
        // Ignorar
    // Si la dificultad es 3 la maquina hará un movimiento utilizando el algoritmo minimax
    } else if (dificultad == 3) {
        // Variable para saber el mejor valor
        int mejorValor = -1000;
        // Recorremos las columnas
        for (int i = 0; i < COLUMNAS; i++) {
            // Si el movimiento es válido
            if (movimientoValido(tablero, i)) {
                // Insertamos la ficha en el tablero
                insertarFicha(tablero, i, AMARILLO);
                // Calculamos el valor de la función minimax
                int valor = minimax(tablero, 0, false);
                // Deshacemos el movimiento
                deshacerMovimiento(tablero, i);
                // Si el valor es mayor que el mejor valor
                if (valor > mejorValor) {
                    // Actualizamos el mejor valor
                    mejorValor = valor;
                    // Actualizamos la columna
                    columna = i;
                }
            }
        }
    }
    // Devolvemos la columna
    return columna;
}

// Función principal
int main() {
    // Creamos el tablero
    vector<vector<char>> tablero = crearTablero();

    // Elección de la ficha
    char fichaMaquina;
    char ficha;
    do {
        // Le preguntamos al usuario qué color de ficha quiere
        cout << "Elige tu ficha (X/O): ";
        cin >> ficha;
        // Convertimos la ficha a mayúsculas
        ficha = toupper(ficha);
        // Si el usuario introduce un color válido
        if (ficha == ROJO || ficha == AMARILLO) {
            // Asignamos la ficha de la maquina
            fichaMaquina = (ficha == ROJO) ? AMARILLO : ROJO;
            // Salimos del bucle
            break;
        } else {
            // Si el usuario introduce un color no válido, le avisamos
            cout << "Ficha no valida" << endl;
        }
    } while (true);

    // Elección de la dificultad
    int dificultad;
    do {
        // Le preguntamos al usuario qué dificultad quiere
        cout << "Elige la dificultad (1/2/3): ";
        cin >> dificultad;
        if (dificultad == 1 || dificultad == 2 || dificultad == 3) {
            // Si el usuario introduce una dificultad válida, salimos del bucle
            break;
        } else {
            // Si el usuario introduce una dificultad no válida, le avisamos
            cout << "Dificultad no valida" << endl;
        }
    } while (true);

    // Variable para saber si el juego ha terminado
    bool gameOver = false;

    // Variable para saber de quién es el turno
    bool turnoJugador = true;

    // Variable para saber en qué columna quiere insertar el usuario o la maquina la ficha
    int columna;
    cout << "\nEmpieza el juego!" << endl << endl;
    // Bucle principal del juego
    while (!gameOver) {
        // Imprimimos el tablero
        imprimirTablero(tablero);

        // Comprobamos si hay un ganador
        int ganador = comprobarGanador(tablero);
        // Si el jugador ha ganado, mostramos el mensaje correspondiente
        if (ganador == 1) {
            cout << "Has ganado!" << endl;
            gameOver = true;
            continue;
        // Si la máquina ha ganado, mostramos el mensaje correspondiente
        } else if (ganador == 2) {
            cout << "Has perdido!" << endl;
            gameOver = true;
            continue;
        // Si hay un empate, mostramos el mensaje correspondiente
        } else if (ganador == 3) {
            cout << "Empate!" << endl;
            gameOver = true;
            continue;
        }

        // Si no es el turno de jugador
        if (!turnoJugador) {
            // Le avisamos al usuario de que es el turno de la máquina
            cout << "Turno de la maquina" << endl << endl;
            // Calculamos el movimiento de la máquina
            columna = calcularMovimiento(tablero, dificultad);
            // Insertamos la ficha en el tablero
            insertarFicha(tablero, columna, fichaMaquina);
            // Cambiamos el turno
            turnoJugador = !turnoJugador;
            continue;
        }

        // Si es el turno del jugador
        cout << "Tu turno" << endl;

        // Variable para saber si se ha insertado la ficha
        bool fichaInsertada = false;

        // Bucle para insertar la ficha
        while (!fichaInsertada) {
            // Le preguntamos al usuario en qué columna quiere insertar la ficha
            cout << "En que columna quieres insertar la ficha? (1-7): ";
            cin >> columna;
            columna--;
            // Si la columna es válida, insertamos la ficha
            if (movimientoValido(tablero, columna)) {
                // Insertamos la ficha en el tablero
                insertarFicha(tablero, columna, ficha);
                // Salimos del bucle
                fichaInsertada = true;
            } else {
                // Si la columna no es válida, le avisamos al usuario
                cout << "Columna no valida" << endl;
            }
        }

        // Cambiamos el turno
        turnoJugador = !turnoJugador;
    }
}