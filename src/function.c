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

int bolaX = 5;
int bolaY = 5;
int velocidadeX = 1;
int velocidadeY = 1;
int barraEsquerda = 10;
int barraDireita = 10;
int pass = 0;
struct pontuacao player;
struct pontuacao *head = NULL;

void Tela() {
  LimparTela();
  PrintSd();
  for (int i = 0; i < altura; i++) {
      for (int j = 0; j < largura; j++) {
          if (j == 0 || j == largura - 1) {
              printf("%s█%s", COR_MAGENTA, COR_RESET);
          } else if ((i == 0 || i == altura - 1) && (j > 0 && j < largura - 1)) {
              printf("%s█%s", COR_MAGENTA, COR_RESET);
          } else if (j == 2 && (i >= barraEsquerda - 2 && i <= barraEsquerda + 2)) {
              printf("█");
          } else if (j == largura - 3 && (i >= barraDireita - 2 && i <= barraDireita + 2)) {
              printf("█");
          } else if (i == (int)bolaY && j == (int)bolaX) {
              printf("%s●%s", COR_CIANO, COR_RESET);
          } else if (j == largura / 2) {
              printf("|");
          } else {
              printf(" ");
          }
      }
      printf("\n");
  }
  /* diminuir o tempo de espera entre frames para respostas mais rápidas */
  usleep(40000); /* ~40ms */
}

void AdicionarPonto(int p1, int p2) {
  pontuacao *novo = (pontuacao *)malloc(sizeof(pontuacao));
  if (novo == NULL) {
    return;
  }

  novo->player1 = p1;
  novo->player2 = p2;
  novo->next = head;
  head = novo;
}

void LiberarPonto() {
  pontuacao *atual = head;
  pontuacao *prox;

  while (atual != NULL) {
    prox = atual->next;
    free(atual);
    atual = prox;
  }

  head = NULL;
}

void EscreverArquivo() {
  FILE *fptr = fopen("pontos.txt", "a");
  if (fptr == NULL) {
    exit(1);
  }

  fprintf(fptr, "Player 1: %d | Player 2: %d\n", head->player1, head->player2);
  fclose(fptr);
}

void PrintArquivo() {
  FILE *fptr = fopen("pontos.txt", "r");
  if (fptr == NULL) {
    exit(1);
  }

  char linha[100];
  while (fgets(linha, sizeof(linha), fptr) != NULL) {
    printf("%s", linha);
  }

  fclose(fptr);
}

void AtualizarBola() {
  bolaX += velocidadeX;
  bolaY += velocidadeY;

  /* bounce top/bottom */
  if (bolaY <= 0) {
    bolaY = 0;
    velocidadeY = -velocidadeY;
  } else if (bolaY >= altura - 1) {
    bolaY = altura - 1;
    velocidadeY = -velocidadeY;
  }

  /* paddle collisions: check when ball reaches or passes the paddle column
     and the Y is inside the paddle range. Reposiciona a bola fora da
     barra para evitar que ela atravesse quando a velocidade for > 1. */
  if (velocidadeX < 0 && bolaX <= 2) {
    if (bolaY >= barraEsquerda - 2 && bolaY <= barraEsquerda + 2) {
      bolaX = 3; /* coloca 1 posição à direita da barra */
      velocidadeX = -velocidadeX;
    }
  }

  if (velocidadeX > 0 && bolaX >= largura - 3) {
    if (bolaY >= barraDireita - 2 && bolaY <= barraDireita + 2) {
      bolaX = largura - 4; /* coloca 1 posição à esquerda da barra */
      velocidadeX = -velocidadeX;
    }
  }

  /* scoring: mantém comportamento anterior quando bola sai totalmente pela borda */
  if (bolaX <= 0) {
    player.player2 += 1;
    velocidadeX = -velocidadeX;
    /* verificar condição de vitória */
    if (player.player2 >= 15) {
      LimparTelaCompleta();
      printf("\n\n\t\tJogador 2 venceu! %d x %d\n", player.player1, player.player2);
      AdicionarPonto(player.player1, player.player2);
      EscreverArquivo();
      LiberarPonto();
      keyboardDestroy();
      exit(0);
    }
  }

  if (bolaX >= largura - 1) {
    player.player1 += 1;
    velocidadeX = -velocidadeX;
    /* verificar condição de vitória */
    if (player.player1 >= 15) {
      LimparTelaCompleta();
      printf("\n\n\t\tJogador 1 venceu! %d x %d\n", player.player1, player.player2);
      AdicionarPonto(player.player1, player.player2);
      EscreverArquivo();
      LiberarPonto();
      keyboardDestroy();
      exit(0);
    }
  }
}

void LimparTela() {
  /* Não limpar toda a tela: apenas reposiciona o cursor no início.
     Isso reduz o "piscamento" da borda ao redesenhar o frame.
  */
  printf("\x1b[H");
  fflush(stdout);
}

/* Limpa completamente a tela (usa em menus/ajuda/historico) */
void LimparTelaCompleta() {
  printf("\x1b[2J\x1b[H");
  fflush(stdout);
}

void Tempo() {
  /* cronômetro removido */
}

/* eventos removidos */
void remover(int x) { (void)x; }

void randomizar() { /* eventos desativados */ }

void PrintarEvento(int x) { (void)x; }

void PrintSd(){
  /* Exibe os rótulos dos jogadores acima do campo, fora da borda magenta */
  const char leftLabel[] = "Player 1 (Esq)";
  const char rightLabel[] = "Player 2 (Dir)";
  int leftLen = (int)strlen(leftLabel);
  int rightLen = (int)strlen(rightLabel);
  int pad = largura - leftLen - rightLen;
  if (pad < 1) pad = 1;

  printf("%s%s%s", COR_AMARELO, leftLabel, COR_RESET);
  for (int i = 0; i < pad; i++) printf(" ");
  printf("%s%s%s\n", COR_AMARELO, rightLabel, COR_RESET);

  /* segunda linha: placar centralizado abaixo dos rótulos */
  int scorePad = (largura - 6) / 2; /* espaço antes do "X | Y" aproximado */
  for (int i = 0; i < scorePad; i++) printf(" ");
  printf("%s%d | %d\n\n%s", COR_AMARELO, player.player1, player.player2, COR_RESET);
}