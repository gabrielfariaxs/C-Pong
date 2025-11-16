#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>

extern int bolaX;
extern int velocidadeX;
extern int barraEsquerda;
extern int barraDireita;
#define altura 20
#define largura 50
#define COR_MAGENTA "\x1b[35m"
#define COR_RESET   "\x1b[0m"
#define COR_CIANO   "\x1b[36m"
#define COR_AMARELO "\x1b[33m"
typedef struct pontuacao{
    int player1;
    int player2;
    struct pontuacao *next;
}pontuacao;

void Tela();
void EscreverArquivo();
void PrintArquivo();
void AdicionarPonto(int p1, int p2);
void LiberarPonto();
void AtualizarBola();
void LimparTela();
void LimparTelaCompleta();
void Tempo();
void PrintSd();
#endif