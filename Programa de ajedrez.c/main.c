#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM 8

typedef enum
{
    VACIO,
    PEON_BLANCO, TORRE_BLANCO, CABALLO_BLANCO, ALFIL_BLANCO, REINA_BLANCO, REY_BLANCO,
    PEON_NEGRO, TORRE_NEGRO, CABALLO_NEGRO, ALFIL_NEGRO, REINA_NEGRO, REY_NEGRO
} Pieza;

typedef enum
{
    BLANCO,
    NEGRO
} Color;

const char* pieza_a_char(Pieza p)
 {
    switch(p) {
        case PEON_BLANCO: return "\033[1;37mP\033[0m";
        case TORRE_BLANCO: return "\033[1;37mT\033[0m";
        case CABALLO_BLANCO: return "\033[1;37mC\033[0m";
        case ALFIL_BLANCO: return "\033[1;37mA\033[0m";
        case REINA_BLANCO: return "\033[1;37mQ\033[0m";
        case REY_BLANCO: return "\033[1;37mK\033[0m";

        case PEON_NEGRO: return "\033[30mP\033[0m";
        case TORRE_NEGRO: return "\033[30mT\033[0m";
        case CABALLO_NEGRO: return "\033[30mC\033[0m";
        case ALFIL_NEGRO: return "\033[30mA\033[0m";
        case REINA_NEGRO: return "\033[30mQ\033[0m";
        case REY_NEGRO: return "\033[30mK\033[0m";

        default: return " ";
    }
}

Color obtener_color(Pieza p)
 {
    if (p >= PEON_BLANCO && p <= REY_BLANCO) return BLANCO;
    if (p >= PEON_NEGRO && p <= REY_NEGRO) return NEGRO;
    return BLANCO; // Para VACIO
}

bool es_pieza_blanca(Pieza p)
{
    return (p >= PEON_BLANCO && p <= REY_BLANCO);
}

bool es_pieza_negra(Pieza p)
{
    return (p >= PEON_NEGRO && p <= REY_NEGRO);
}

void inicializar_tablero(Pieza tablero[TAM][TAM])
 {
    Pieza fila_blanca[] = {TORRE_BLANCO, CABALLO_BLANCO, ALFIL_BLANCO, REINA_BLANCO,
                           REY_BLANCO, ALFIL_BLANCO, CABALLO_BLANCO, TORRE_BLANCO};
    Pieza fila_negra[] = {TORRE_NEGRO, CABALLO_NEGRO, ALFIL_NEGRO, REINA_NEGRO,
                          REY_NEGRO, ALFIL_NEGRO, CABALLO_NEGRO, TORRE_NEGRO};

    for (int i = 0; i < TAM; i++)
        {
        tablero[1][i] = PEON_NEGRO;
        tablero[6][i] = PEON_BLANCO;
        tablero[0][i] = fila_negra[i];
        tablero[7][i] = fila_blanca[i];
    }

    for (int i = 2; i < 6; i++)
        for (int j = 0; j < TAM; j++)
            tablero[i][j] = VACIO;
}

void imprimir_tablero(Pieza tablero[TAM][TAM])
{
    printf("\n  a b c d e f g h\n");
    for (int i = 0; i < TAM; i++)
        {
        printf("%d ", 8 - i);
        for (int j = 0; j < TAM; j++)
        {
            if ((i + j) % 2 == 0)
                printf("\033[47m"); // blanco
            else
                printf("\033[100m"); // gris oscuro

            printf(" %s", pieza_a_char(tablero[i][j]));
            printf("\033[0m"); // reset
        }
        printf(" %d\n", 8 - i);
    }
    printf("  a b c d e f g h\n\n");
}

bool movimiento_valido(char* mov)
{
    return strlen(mov) == 4 &&
           mov[0] >= 'a' && mov[0] <= 'h' &&
           mov[2] >= 'a' && mov[2] <= 'h' &&
           mov[1] >= '1' && mov[1] <= '8' &&
           mov[3] >= '1' && mov[3] <= '8';
}

// Función para validar movimiento de peón
bool validar_movimiento_peon(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest)
{
    Pieza pieza = tablero[fila_orig][col_orig];

    bool es_blanco = es_pieza_blanca(pieza);
    int direccion = es_blanco ? -1 : 1;
    int fila_inicio = es_blanco ? 6 : 1;

    // Movimiento hacia adelante
    if(col_orig == col_dest)
        {
        // Un paso adelante

        if(fila_dest == fila_orig + direccion && tablero[fila_dest][col_dest] == VACIO)
        {
            return true;
        }
        // Dos pasos desde posición inicial
        if(fila_orig == fila_inicio && fila_dest == fila_orig + 2*direccion &&
           tablero[fila_orig + direccion][col_dest] == VACIO && tablero[fila_dest][col_dest] == VACIO)
           {
            return true;
        }
    }

    // Captura diagonal
    if(abs(col_dest - col_orig) == 1 && fila_dest == fila_orig + direccion &&
       tablero[fila_dest][col_dest] != VACIO &&
       es_pieza_blanca(pieza) != es_pieza_blanca(tablero[fila_dest][col_dest])) {
        return true;
    }

    return false;
}

// Función para validar movimiento de torre
bool validar_movimiento_torre(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest)
{
    // Movimiento en línea recta
    if(fila_orig != fila_dest && col_orig != col_dest)
        {
        return false;
    }

    // Verificar camino despejado
    int paso_fila = (fila_dest > fila_orig) ? 1 : (fila_dest < fila_orig) ? -1 : 0;
    int paso_col = (col_dest > col_orig) ? 1 : (col_dest < col_orig) ? -1 : 0;

    int f = fila_orig + paso_fila;
    int c = col_orig + paso_col;

    while(f != fila_dest || c != col_dest) {
        if(tablero[f][c] != VACIO)
            {
            return false;
        }
        f += paso_fila;
        c += paso_col;
    }

    return true;
}

// Función para validar movimiento de caballo
bool validar_movimiento_caballo(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest) {
    int diff_fila = abs(fila_dest - fila_orig);
    int diff_col = abs(col_dest - col_orig);

    return (diff_fila == 2 && diff_col == 1) || (diff_fila == 1 && diff_col == 2);
}

// Función para validar movimiento de alfil
bool validar_movimiento_alfil(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest) {
    // Movimiento diagonal
    if(abs(fila_dest - fila_orig) != abs(col_dest - col_orig)) {
        return false;
    }

    // Verificar camino despejado
    int paso_fila = (fila_dest > fila_orig) ? 1 : -1;
    int paso_col = (col_dest > col_orig) ? 1 : -1;

    int f = fila_orig + paso_fila;
    int c = col_orig + paso_col;

    while(f != fila_dest && c != col_dest) {
        if(tablero[f][c] != VACIO) {
            return false;
        }
        f += paso_fila;
        c += paso_col;
    }

    return true;
}

// Función para validar movimiento de reina
bool validar_movimiento_reina(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest) {
    return validar_movimiento_torre(tablero, fila_orig, col_orig, fila_dest, col_dest) ||
           validar_movimiento_alfil(tablero, fila_orig, col_orig, fila_dest, col_dest);
}

// Función para validar movimiento de rey
bool validar_movimiento_rey(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest) {
    int diff_fila = abs(fila_dest - fila_orig);
    int diff_col = abs(col_dest - col_orig);

    return diff_fila <= 1 && diff_col <= 1 && (diff_fila + diff_col > 0);
}

// Función para validar movimiento general
bool validar_movimiento(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest) {
    // Verificar que la posición de destino no sea la misma que la de origen
    if(fila_orig == fila_dest && col_orig == col_dest) {
        return false;
    }

    // Verificar que la posición de origen tenga una pieza
    if(tablero[fila_orig][col_orig] == VACIO) {
        return false;
    }

    Pieza pieza = tablero[fila_orig][col_orig];

    // Verificar que no capture una pieza del mismo color
    if(tablero[fila_dest][col_dest] != VACIO) {
        if((es_pieza_blanca(pieza) && es_pieza_blanca(tablero[fila_dest][col_dest])) ||
           (es_pieza_negra(pieza) && es_pieza_negra(tablero[fila_dest][col_dest]))) {
            return false;
        }
    }

    switch(pieza) {
        case PEON_BLANCO:
        case PEON_NEGRO:
            return validar_movimiento_peon(tablero, fila_orig, col_orig, fila_dest, col_dest);
        case TORRE_BLANCO:
        case TORRE_NEGRO:
            return validar_movimiento_torre(tablero, fila_orig, col_orig, fila_dest, col_dest);
        case CABALLO_BLANCO:
        case CABALLO_NEGRO:
            return validar_movimiento_caballo(tablero, fila_orig, col_orig, fila_dest, col_dest);
        case ALFIL_BLANCO:
        case ALFIL_NEGRO:
            return validar_movimiento_alfil(tablero, fila_orig, col_orig, fila_dest, col_dest);
        case REINA_BLANCO:
        case REINA_NEGRO:
            return validar_movimiento_reina(tablero, fila_orig, col_orig, fila_dest, col_dest);
        case REY_BLANCO:
        case REY_NEGRO:
            return validar_movimiento_rey(tablero, fila_orig, col_orig, fila_dest, col_dest);
        default:
            return false;
    }
}

// Función para encontrar la posición del rey
bool encontrar_rey(Pieza tablero[TAM][TAM], Color color, int* fila_rey, int* col_rey) {
    Pieza rey_buscado = (color == BLANCO) ? REY_BLANCO : REY_NEGRO;

    for(int i = 0; i < TAM; i++)
        {
        for(int j = 0; j < TAM; j++)
         {
            if(tablero[i][j] == rey_buscado)
            {
                *fila_rey = i;
                *col_rey = j;
                return true;
            }
        }
    }
    return false;
}

// Función para verificar si una posición está bajo ataque
bool posicion_bajo_ataque(Pieza tablero[TAM][TAM], int fila, int col, Color color_atacante) {
    for(int i = 0; i < TAM; i++)
        {
        for(int j = 0; j < TAM; j++)
            {
            Pieza pieza = tablero[i][j];

            // Verificar si la pieza es del color atacante
            if(pieza != VACIO && obtener_color(pieza) == color_atacante) {
                // Temporalmente validar movimiento hacia la posición objetivo
                if(validar_movimiento(tablero, i, j, fila, col)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Función para verificar si el rey está en jaque
bool rey_en_jaque(Pieza tablero[TAM][TAM], Color color_rey)
{
    int fila_rey, col_rey;

    if(!encontrar_rey(tablero, color_rey, &fila_rey, &col_rey))
        {
        return false;
    }

    Color color_atacante = (color_rey == BLANCO) ? NEGRO : BLANCO;
    return posicion_bajo_ataque(tablero, fila_rey, col_rey, color_atacante);
}

// Función para hacer un movimiento temporal (para verificar jaque)
void hacer_movimiento_temporal(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest, Pieza* pieza_capturada)
 {
    *pieza_capturada = tablero[fila_dest][col_dest];
    tablero[fila_dest][col_dest] = tablero[fila_orig][col_orig];
    tablero[fila_orig][col_orig] = VACIO;
}

// Función para deshacer un movimiento temporal
void deshacer_movimiento_temporal(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest, Pieza pieza_capturada)
 {
    tablero[fila_orig][col_orig] = tablero[fila_dest][col_dest];
    tablero[fila_dest][col_dest] = pieza_capturada;
}

// Función para verificar si un movimiento deja al propio rey en jaque
bool movimiento_deja_rey_en_jaque(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest)
 {
    Pieza pieza_capturada;
    Color color_jugador = obtener_color(tablero[fila_orig][col_orig]);

    // Hacer movimiento temporal
    hacer_movimiento_temporal(tablero, fila_orig, col_orig, fila_dest, col_dest, &pieza_capturada);

    // Verificar si el rey queda en jaque
    bool en_jaque = rey_en_jaque(tablero, color_jugador);

    // Deshacer movimiento
    deshacer_movimiento_temporal(tablero, fila_orig, col_orig, fila_dest, col_dest, pieza_capturada);

    return en_jaque;
}

// Función para mover pieza con validación completa
bool mover_pieza_validado(Pieza tablero[TAM][TAM], int fila_orig, int col_orig, int fila_dest, int col_dest)
{
    // Primero validar movimiento básico
    if(!validar_movimiento(tablero, fila_orig, col_orig, fila_dest, col_dest))
        {
        return false;
    }

    // Verificar que el movimiento no deje al propio rey en jaque
    if(movimiento_deja_rey_en_jaque(tablero, fila_orig, col_orig, fila_dest, col_dest))
        {
        return false;
    }

    // Realizar el movimiento
    tablero[fila_dest][col_dest] = tablero[fila_orig][col_orig];
    tablero[fila_orig][col_orig] = VACIO;
    return true;
}

void mover_pieza(Pieza tablero[TAM][TAM], char* mov)
 {
    int origen_col = mov[0] - 'a';
    int origen_fil = 8 - (mov[1] - '0');
    int dest_col = mov[2] - 'a';
    int dest_fil = 8 - (mov[3] - '0');

    tablero[dest_fil][dest_col] = tablero[origen_fil][origen_col];
    tablero[origen_fil][origen_col] = VACIO;
}

int main()
{
    Pieza tablero[TAM][TAM];
    char movimiento[10];

    inicializar_tablero(tablero);

    while (1) {
        imprimir_tablero(tablero);

        // Verificar jaque
        if(rey_en_jaque(tablero, BLANCO))
            {
            printf("\033[31m¡Rey blanco en jaque!\033[0m\n");
        }
        if(rey_en_jaque(tablero, NEGRO))
        {
            printf("\033[31m¡Rey negro en jaque!\033[0m\n");
        }

        printf("Introduce tu movimiento (ej. e2e4 o 'salir'): ");
        fgets(movimiento, sizeof(movimiento), stdin);
        movimiento[strcspn(movimiento, "\n")] = 0;

        if (strcmp(movimiento, "salir") == 0)
            break;

        if (movimiento_valido(movimiento))
            {
            int origen_col = movimiento[0] - 'a';
            int origen_fil = 8 - (movimiento[1] - '0');
            int dest_col = movimiento[2] - 'a';
            int dest_fil = 8 - (movimiento[3] - '0');

            if(mover_pieza_validado(tablero, origen_fil, origen_col, dest_fil, dest_col))
                {
                printf("Movimiento válido\n");
            } else
            {
                printf("Movimiento inválido (deja al rey en jaque o movimiento ilegal)\n");
            }
        } else
         {
            printf("Movimiento inválido. Usa formato como 'e2e4'.\n");
        }
    }

    return 0;
}
