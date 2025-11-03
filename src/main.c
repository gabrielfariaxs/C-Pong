/* 
 Arquivo principal que contém o loop do jogo e a lógica de controle.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pong.h"
#include "cli-lib.h"  // Ajuste conforme o nome verdadeiro da biblioteca CLI-lib

Ball ball;
Paddle player1, player2;

int main() {
    iniciar_game();

    while (!fim_game()) {
        atualizar_game();
        desenhar_game();
        usleep(50000);  // Delay para controle de velocidade (50ms)
    }

    printf("Fim de jogo!\n");
    return 0;
}
