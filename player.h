#include "raylib.h"

typedef struct{
    Vector2 posicao;
    Rectangle colisao;
} jogador;

void movPlayer (int *direcao, int *totalFrame, jogador *player, int *pulo);

void carregaPlayer();