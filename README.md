# Conecta 4

## Descripción

Este popular juego de estrategia por turnos consiste en insertar y dejar caer fichas en un tablero vertical (normalmente de 6x7) con el propósito de conectar 4 fichas de forma consecutiva, ya sea en una fila, en una columna o de forma diagonal. El primero que logre lo mencionado anteriormente gana el juego.

## Instalación

Para ejecutar este programa se necesita tener instalado el compilador de C++ y el editor de código de su preferencia. Los pasos son los siguientes:

- Clonar o descargar el repositorio de GitHub donde se encuentra el código fuente del programa.
- Abrir la terminal y ejecutar el siguiente comando: g++ -o main.exe main.cpp
- Ejecutar el archivo 'main.exe' generado por el compilador.

## Uso

Al iniciar el programa, se le pedirá al usuario que ingrese el tipo de ficha que desee usar (X/Rojo o O/amarillo). A continuación, se le pedirá que elija la dificultad del juego (1/2/3). La dificultad 1 será la más fácil ya que la IA siempre hará movimientos aleatorios. La dificultad 2 será medianamente dificil ya que la IA hará movimientos aleatorios pero evitará que el usuario gane o ganará de ser posible. Y por último la dificultad 3 es la más dificil ya que utilizará el algoritmo Minimax con PODA alfa-beta para calcular siempre el mejor movimiento posible. El usuario podrá editar el código para cambiar las variables globales al inicio y modificar el funcionamiento del programa, como por ejemplo las dimensiones del tablero, el númeo de conexiones para ganar, la profundidad máxima del algoritmo Minimax, etc. A mayores dimensiones del tablero, se recomienda disminuir la profundidad máxima del algoritmo para mantener la consistencia y rendimiento del programa.

Por otro lado, el usuario debe seguir las instrucciones que aparezcan por pantalla durante la ejecución del programa. Para seleccionar una opción, el usuario debe ingresar el número o texto correspondiente y presionar enter. 

## Licencia

Este proyecto está bajo la licencia MIT.

## Contribuidores

Este proyecto fue creado por Ignacio Hernández.