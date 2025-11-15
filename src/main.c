#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "function.h"
#include "keyboard.h"

int posBarraEsquerda = 10;
int posBarraDireita = 10;

void mostrarMenu();
void exibirAjuda();
void mostrarHistorico();

int main() {
    int opcao;
    int estaJogando = 0;

    keyboardInit();

    while (1) {
        LimparTela();
        mostrarMenu();

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Iniciar jogo
                estaJogando = 1;

                while (estaJogando) {
                    if (keyhit()) {
                        char tecla = readch();
                        if (tecla == 'w' && posBarraEsquerda > 3) posBarraEsquerda--;
                        else if (tecla == 's' && posBarraEsquerda < altura - 4) posBarraEsquerda++;
                        else if (tecla == 'i' && posBarraDireita > 0) posBarraDireita--;
                        else if (tecla == 'k' && posBarraDireita < altura - 4) posBarraDireita++;
                    }
                    Tela();
                    Tempo();
                    AtualizarBola();
                }
                break;

            case 2: // Ajuda
                exibirAjuda();
                break;

            case 3: // Histórico de Pontuação
                mostrarHistorico();
                break;

            case 4: // Sair
                keyboardDestroy();
                exit(0);

            default:
                printf("Opcao invalida! Tente novamente.\n");
                sleep(1);
                break;
        }
    }

    keyboardDestroy();
    return 0;
}

void mostrarMenu() {
    printf("=== Menu Principal ===\n");
    printf("1 - Jogar\n");
    printf("2 - Ajuda\n");
    printf("3 - Historico de Pontuacao\n");
    printf("4 - Sair\n\n");
}

void exibirAjuda() {
    LimparTela();
    printf("Controles:\n\n");
    printf("Jogador 1: W - Cima | S - Baixo\n");
    printf("Jogador 2: I - Cima | K - Baixo\n\n");
    printf("Eventos:\nA cada 30 segundos, eventos especiais podem acontecer:\n");
    printf("- Bola dupla\n- Pontos duplicados\n- Velocidade dobrada\n\n");
    printf("Pressione Enter para voltar ao menu.\n");

    keyboardInit();
    while (!keyhit() || readch() != '\n') {
        // Aguarda Enter
    }
    keyboardDestroy();
}

void mostrarHistorico() {
    LimparTela();
    printf("==== Historico de Pontuacao ====\n\n");
    PrintArquivo();
    printf("\nPressione Enter para voltar ao menu.\n");

    keyboardInit();
    while (!keyhit() || readch() != '\n') {
        // Aguarda Enter
    }
    keyboardDestroy();
}