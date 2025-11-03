/* Declarações das funções, structs, e constantes do jogo.*/

#ifndef PONG_H
#define PONG_H


#include <stdbool.h> /* Biblioteca que faz com que possa utilizar o tipo boolean (true or false)*/

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
/* Dimensões da tela do jogo */

typedef struct {
    int x, y;
    int dx, dy;
} Ball;

typedef struct {
    int x, y;
    int height;
} Paddle;

void iniciar_game(void);
void atualizar_game(void);
void desenhar_game(void);
bool fim_game(void);
/* Funções que precisam ser definidas*/

#endif
