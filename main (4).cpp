#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream.h>

// Funciones del juego
void draw(char main[][75], int score); // Función para dibujar el mapa y el puntaje
void reset(char main[][75]); // Función para resetear el mapa
void move(char main[][75], int &parts, int pastCounter, int past[][2], int &apples, int &score, int &quit); // Función para mover la serpiente
void check(int &direction); // Función para revisar la entrada del teclado
void directionn(int direction, int &pastCounter, int past[][2]); // Función para actualizar la dirección
void apple(int &apples, char main[][75]); // Función para generar manzanas
void quitGame(int score); // Función para terminar el juego

int main()
{
    int past[1000][2]; // Matriz para almacenar las posiciones de los segmentos de la serpiente
    int parts = 3; // Número de partes iniciales de la serpiente
    char main[23][75]; // Mapa del juego de 23x75
    int pastCounter = 6; // Contador de las posiciones de la serpiente
    int direction = 0; // Dirección inicial de la serpiente (0: derecha, 1: izquierda, 2: arriba, 3: abajo)
    int apples = 0; // Contador de manzanas
    int score = 0; // Puntaje inicial
    int quit = 0; // Variable para verificar si el juego debe terminar
    int playAgain = 1; // Control de reinicio del juego
    unsigned time;
    srand(time); // Inicializa la semilla para la generación de números aleatorios

    // Inicialización de la matriz de posiciones de la serpiente
    for (int x = 0; x < 1000; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            past[x][y] = 0; // Inicializa las posiciones a 0
        }
    }

    // Inicializa la posición de la cabeza de la serpiente
    past[pastCounter][0] = 1;
    past[pastCounter][1] = 1;

    // Bucle principal del juego
    while (quit == 0)
    {
        draw(main, score); // Dibuja el mapa y el puntaje
        check(direction); // Revisa la entrada del teclado
        directionn(direction, pastCounter, past); // Actualiza la dirección de la serpiente
        reset(main); // Resetea el mapa
        move(main, parts, pastCounter, past, apples, score, quit); // Mueve la serpiente y actualiza el mapa

        // Si no hay manzanas, genera una nueva
        if (apples == 0)
        {
            apple(apples, main);
        }
    }

    quitGame(score); // Termina el juego y muestra el puntaje final
}

void draw(char main[][75], int score)
{
    system("cls"); // Limpia la pantalla
    cout << "Score : " << score << endl; // Muestra el puntaje
    for (int x = 0; x < 23; x++) // Dibuja las filas del mapa
    {
        for (int y = 0; y < 75; y++) // Dibuja las columnas
        {
            cout << main[x][y]; // Imprime el contenido de cada celda del mapa
        }
        cout << endl;
    }
}

void reset(char main[][75])
{
    // Resetea el mapa, dibujando bordes y espacios vacíos
    for (int x = 0; x < 23; x++)
    {
        for (int y = 0; y < 75; y++)
        {
            if (main[x][y] == '@') // Si es parte de la serpiente, mantiene el '@'
            {
                main[x][y] == '@';
            }
            else
            {
                // Dibuja los bordes del mapa
                if (x == 0 || x == 22 || y == 0 || y == 74)
                {
                    main[x][y] = 177; // Carácter para dibujar el borde
                }
                else
                {
                    main[x][y] = ' '; // Espacios vacíos en el centro
                }
            }
        }
    }
}

void move(char main[][75], int &parts, int pastCounter, int past[][2], int &apples, int &score, int &quit)
{
    // Verifica si la serpiente ha chocado con los bordes
    if (past[pastCounter][0] == 22 || past[pastCounter][0] == 0)
    {
        quit = 1; // Termina el juego si choca con los bordes
    }
    if (past[pastCounter][1] == 74 || past[pastCounter][1] == 0)
    {
        quit = 1; // Termina el juego si choca con los bordes
    }

    // Recorre los segmentos de la serpiente
    for (int x = 0; x < parts; x++)
    {
        // Si la serpiente come una manzana
        if (main[past[pastCounter - x][0]][past[pastCounter - x][1]] == '@')
        {
            apples--; // Disminuye el contador de manzanas
            parts++; // Aumenta el tamaño de la serpiente
            score += 10; // Incrementa el puntaje
        }
        // Si la serpiente choca consigo misma
        if (main[past[pastCounter - x][0]][past[pastCounter - x][1]] == 'o')
        {
            quit = 1; // Termina el juego
        }
        else
        {
            main[past[pastCounter - x][0]][past[pastCounter - x][1]] = 'o'; // Marca la posición de la serpiente
        }
    }
}

void check(int &direction)
{
    int key = 0;
    if (kbhit()) // Si se presiona una tecla
    {
        key = -getch(); // Captura la tecla
        switch (key) // Cambia la dirección según la tecla presionada
        {
        case -72: // Flecha hacia arriba
            direction = 2;
            break;
        case -77: // Flecha hacia la derecha
            direction = 0;
            break;
        case -80: // Flecha hacia abajo
            direction = 3;
            break;
        case -75: // Flecha hacia la izquierda
            direction = 1;
            break;
        }
    }
}

void directionn(int direction, int &pastCounter, int past[][2])
{
    int down;
    int right;
    right = past[pastCounter][1]; // Coordenada horizontal
    down = past[pastCounter][0];  // Coordenada vertical

    // Actualiza la dirección de la serpiente
    switch (direction)
    {
    case 0: // Movimiento hacia la derecha
        right++;
        break;
    case 1: // Movimiento hacia la izquierda
        right--;
        break;
    case 2: // Movimiento hacia arriba
        down--;
        break;
    case 3: // Movimiento hacia abajo
        down++;
    }

    pastCounter++; // Incrementa el contador de la posición
    past[pastCounter][0] = down; // Actualiza la coordenada vertical
    past[pastCounter][1] = right; // Actualiza la coordenada horizontal
}

void apple(int &apples, char main[][75])
{
    int up = 0;
    int left = 0;
    apples = 3; // Número inicial de manzanas

    for (int x = 0; x < apples; x++) // Genera manzanas
    {
        up = (rand() % 22); // Genera una posición aleatoria para la fila
        left = (rand() % 74); // Genera una posición aleatoria para la columna

        // Si la posición está ocupada por la serpiente, genera otra manzana
        if (main[up][left] == 'o' || main[up][left] == '@')
        {
            apple(apples, main);
        }
        else
        {
            main[up][left] = '@'; // Coloca una manzana en la posición aleatoria
        }
    }
}

void quitGame(int score)
{
    int quit = 0;
    system("cls"); // Limpia la pantalla
    cout << "GAME OVER!!!!\n\n"; // Mensaje de fin de juego
    cout << "You got a score of " << score << endl; // Muestra el puntaje final
}
