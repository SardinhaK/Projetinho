#include "raylib.h"

typedef struct{
    Vector2 posicao;
    Rectangle colisao;
} jogador;

typedef struct{
    Rectangle colisao;
    Vector2 posicao;
} tiro;

void atirando (jogador player, tiro *disparo);

void movPlayer (int *direcao, int *totalFrame, jogador *player, int *pulo);

void carregaPlayer();