#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "function.h"
#include "keyboard.h"

// Variáveis globais definidas em outro arquivo
extern int raqueteEsquerda;
extern int raqueteDireita;

void exibirMenu();
void exibirAjuda();
void exibirHistorico();

int main() {
    int escolha;
    int jogando = 0;

    while (1) {
        LimparTelaCompleta();
        exibirMenu();

        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: // Iniciar jogo
                jogando = 1;
                LimparTelaCompleta();
                keyboardInit();

                while (jogando) {
                    if (keyhit()) {
                        char tecla = readch();
                        if (tecla == 'q' || tecla == 'Q') {
                            jogando = 0;
                            break;
                        }
                        // Controles para ambas as raquetes com os novos nomes das variáveis
                        if (tecla == 'w' && raqueteEsquerda > 3) raqueteEsquerda -= 2;
                        else if (tecla == 's' && raqueteEsquerda < altura - 4) raqueteEsquerda += 2;
                        else if (tecla == 'i' && raqueteDireita > 0) raqueteDireita -= 2;
                        else if (tecla == 'k' && raqueteDireita < altura - 4) raqueteDireita += 2;
                    }
                    MostraJogo();
                    MoverBola();
                }

                keyboardDestroy();
                break;

            case 2: // Ajuda
                exibirAjuda();
                break;

            case 3: // Histórico de Pontuação
                exibirHistorico();
                break;

            case 4:
                exit(0);

            default:
                printf("Opcao invalida! Tente novamente.\n");
                sleep(1);
                break;
        }
    }
    return 0;
}

void exibirMenu() {
    printf("=== Menu Principal ===\n");
    printf("1 - Jogar\n");
    printf("2 - Ajuda\n");
    printf("3 - Historico de Pontuacao\n");
    printf("4 - Sair\n\n");
}

void exibirAjuda() {
    LimparTelaCompleta();
    printf("Controles:\n\n");
    printf("Jogador 1: W - Cima | S - Baixo\n");
    printf("Jogador 2: I - Cima | K - Baixo\n\n");
    printf("Pressione 'Q' a qualquer momento para sair do jogo.\n\n");
    printf("Pressione Enter para voltar ao menu.\n");

    keyboardInit();
    while (!keyhit() || readch() != '\n') {
        // Aguarda Enter
    }
    keyboardDestroy();
}

void exibirHistorico() {
    LimparTelaCompleta();
    printf("==== Historico de Pontuacao ====\n\n");
    MostrarArquivo();
    printf("\nPressione Enter para voltar ao menu.\n");

    keyboardInit();
    while (!keyhit() || readch() != '\n') {
        // Aguarda Enter
    }
    keyboardDestroy();
}
