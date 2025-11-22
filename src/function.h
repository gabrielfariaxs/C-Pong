#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

extern int bolaPosX;
extern int bolaPosY;
extern int direcaoX;
extern int direcaoY;
extern int raqueteEsquerda;
extern int raqueteDireita;
extern int marcador;

#define altura 20
#define largura 50

#define COR_MAGENTA "\x1b[35m"
#define COR_RESET   "\x1b[0m"
#define COR_CIANO   "\x1b[36m"
#define COR_AMARELO "\x1b[33m"

// Struct de pontuação (mantido o nome conforme o código reescrito)
typedef struct pontuacao {
    int player1;
    int player2;
    struct pontuacao *next;
} pontuacao;

// Funções com nomes atualizados
void MostraJogo();
void GravarPonto(int j1, int j2);
void LimparPlacar();
void SalvarEmArquivo();
void MostrarArquivo();
void MoverBola();
void LimparTela();
void LimparTelaCompleta();
void Tempo();
void remover(int x);
void randomizar();
void PrintarEvento(int x);
void ExibirPlacar();

#endif
