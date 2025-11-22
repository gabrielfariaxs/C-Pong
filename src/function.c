#include "function.h"
#include "keyboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define COR_MAGENTA "\x1b[35m"
#define COR_RESET   "\x1b[0m"
#define COR_CIANO   "\x1b[36m"
#define COR_AMARELO "\x1b[33m"

int bolaPosX = 5;
int bolaPosY = 5;
int direcaoX = 1;
int direcaoY = 1;
int raqueteEsquerda = 10;
int raqueteDireita = 10;
int marcador = 0;
struct pontuacao status;
struct pontuacao *historico = NULL;

void MostraJogo() {
    LimparTela();
    ExibirPlacar();
    for (int lin = 0; lin < altura; lin++) {
        for (int col = 0; col < largura; col++) {
            if (col == 0 || col == largura - 1) {
                printf("%s█%s", COR_MAGENTA, COR_RESET);
            } else if ((lin == 0 || lin == altura - 1) && (col > 0 && col < largura - 1)) {
                printf("%s█%s", COR_MAGENTA, COR_RESET);
            } else if (col == 2 && (lin >= raqueteEsquerda - 2 && lin <= raqueteEsquerda + 2)) {
                printf("█");
            } else if (col == largura - 3 && (lin >= raqueteDireita - 2 && lin <= raqueteDireita + 2)) {
                printf("█");
            } else if (lin == (int)bolaPosY && col == (int)bolaPosX) {
                printf("%s●%s", COR_CIANO, COR_RESET);
            } else if (col == largura / 2) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    usleep(42000);
}

void GravarPonto(int j1, int j2) {
    struct pontuacao *novoPonto = (struct pontuacao *)malloc(sizeof(struct pontuacao));
    if (!novoPonto) return;
    novoPonto->player1 = j1;
    novoPonto->player2 = j2;
    novoPonto->next = historico;
    historico = novoPonto;
}

void LimparPlacar() {
    struct pontuacao *temp = historico, *prox;
    while (temp) {
        prox = temp->next;
        free(temp);
        temp = prox;
    }
    historico = NULL;
}

void SalvarEmArquivo() {
    FILE *arq = fopen("registros.txt", "a");
    if (arq == NULL) exit(1);
    fprintf(arq, "Jogador 1: %d | Jogador 2: %d\n", historico->player1, historico->player2);
    fclose(arq);
}

void MostrarArquivo() {
    FILE *arq = fopen("registros.txt", "r");
    if (arq == NULL) exit(1);
    char texto[100];
    while (fgets(texto, sizeof(texto), arq) != NULL) {
        printf("%s", texto);
    }
    fclose(arq);
}

void MoverBola() {
    bolaPosX += direcaoX;
    bolaPosY += direcaoY;

    if (bolaPosY <= 0) {
        bolaPosY = 0;
        direcaoY = -direcaoY;
    } else if (bolaPosY >= altura - 1) {
        bolaPosY = altura - 1;
        direcaoY = -direcaoY;
    }

    if (direcaoX < 0 && bolaPosX <= 2) {
        if (bolaPosY >= raqueteEsquerda - 2 && bolaPosY <= raqueteEsquerda + 2) {
            bolaPosX = 3;
            direcaoX = -direcaoX;
        }
    }
    if (direcaoX > 0 && bolaPosX >= largura - 3) {
        if (bolaPosY >= raqueteDireita - 2 && bolaPosY <= raqueteDireita + 2) {
            bolaPosX = largura - 4;
            direcaoX = -direcaoX;
        }
    }

    if (bolaPosX <= 0) {
        status.player2++;
        direcaoX = -direcaoX;
        if (status.player2 >= 15) {
            LimparTelaCompleta();
            printf("\n\n\t\tJogador 2 venceu! %d x %d\n", status.player1, status.player2);
            GravarPonto(status.player1, status.player2);
            SalvarEmArquivo();
            LimparPlacar();
            keyboardDestroy();
            exit(0);
        }
    }
    if (bolaPosX >= largura - 1) {
        status.player1++;
        direcaoX = -direcaoX;
        if (status.player1 >= 15) {
            LimparTelaCompleta();
            printf("\n\n\t\tJogador 1 venceu! %d x %d\n", status.player1, status.player2);
            GravarPonto(status.player1, status.player2);
            SalvarEmArquivo();
            LimparPlacar();
            keyboardDestroy();
            exit(0);
        }
    }
}

void LimparTela() {
    printf("\x1b[H");
    fflush(stdout);
}

void LimparTelaCompleta() {
    printf("\x1b[2J\x1b[H");
    fflush(stdout);
}

void Tempo() { /* removido */ }
void remover(int x) { (void)x; }
void randomizar() { }
void PrintarEvento(int x) { (void)x; }

void ExibirPlacar() {
    const char esq[] = "Jogador 1";
    const char dir[] = "Jogador 2";
    int l1 = (int)strlen(esq), l2 = (int)strlen(dir), pad = largura - l1 - l2;
    if (pad < 1) pad = 1;
    printf("%s%s%s", COR_AMARELO, esq, COR_RESET);
    for (int i = 0; i < pad; i++) printf(" ");
    printf("%s%s%s\n", COR_AMARELO, dir, COR_RESET);

    int scorePad = (largura - 6) / 2;
    for (int i = 0; i < scorePad; i++) printf(" ");
    printf("%s%d | %d\n\n%s", COR_AMARELO, status.player1, status.player2, COR_RESET);
}