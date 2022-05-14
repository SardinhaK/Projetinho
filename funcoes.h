#include "raylib.h"


typedef struct{
    Vector2 posicao;
    Rectangle colisao;
    Vector2 velocidade;
} jogador;


typedef struct {
    Rectangle projet;
    Vector2 vel;
    bool active;
    Color color;
} shoot;

typedef struct {
    Rectangle projet;
    Vector2 vel;
    bool active;
    Color color;
} shootInimigo;

void movPlayer (int *direcao, int *totalFrame, jogador *player, int *pulo, Rectangle *grid);

void atirar(int *shootRate, shoot **disparo, jogador *player);
