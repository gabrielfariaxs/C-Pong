#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "function.h"
#include "keyboard.h"

// usar as variáveis globais definidas em `src/globals.c`
extern int barraEsquerda;
extern int barraDireita;

void mostrarMenu();
void exibirAjuda();
void mostrarHistorico();

int main() {
    int opcao;
    int estaJogando = 0;

    // teclado será inicializado somente ao iniciar o jogo

    while (1) {
        /* quando mostrar o menu, limpar completamente para evitar
           que o último frame do jogo fique por baixo do texto */
        LimparTelaCompleta();
        mostrarMenu();

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Iniciar jogo
                estaJogando = 1;
                /* Limpa completamente a tela para remover o menu
                   (evita que linhas como "2 - Ajuda" fiquem visíveis
                   durante o jogo). */
                LimparTelaCompleta();
                keyboardInit();

                while (estaJogando) {
                    if (keyhit()) {
                        char tecla = readch();
                        /* sair do jogo pressionando 'q' */
                        if (tecla == 'q' || tecla == 'Q') {
                            estaJogando = 0;
                            break;
                        }
                        /* mover em passos de 2 para sensação de resposta mais rápida */
                        if (tecla == 'w' && barraEsquerda > 3) barraEsquerda -= 2;
                        else if (tecla == 's' && barraEsquerda < altura - 4) barraEsquerda += 2;
                        else if (tecla == 'i' && barraDireita > 0) barraDireita -= 2;
                        else if (tecla == 'k' && barraDireita < altura - 4) barraDireita += 2;
                    }
                    Tela();
                    AtualizarBola();
                }

                keyboardDestroy();
                break;

            case 2: // Ajuda
                exibirAjuda();
                break;

            case 3: // Histórico de Pontuação
                mostrarHistorico();
                break;

            case 4: // Sair
                exit(0);

            default:
                printf("Opcao invalida! Tente novamente.\n");
                sleep(1);
                break;
        }
    }

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
    LimparTelaCompleta();
    printf("Controles:\n\n");
    printf("Jogador 1: W - Cima | S - Baixo\n");
    printf("Jogador 2: I - Cima | K - Baixo\n\n");
    /* eventos removidos do jogo */
    printf("Pressione Enter para voltar ao menu.\n");

    keyboardInit();
    while (!keyhit() || readch() != '\n') {
        // Aguarda Enter
    }
    keyboardDestroy();
}

void mostrarHistorico() {
    LimparTelaCompleta();
    printf("==== Historico de Pontuacao ====\n\n");
    PrintArquivo();
    printf("\nPressione Enter para voltar ao menu.\n");

    keyboardInit();
    while (!keyhit() || readch() != '\n') {
        // Aguarda Enter
    }
    keyboardDestroy();
}