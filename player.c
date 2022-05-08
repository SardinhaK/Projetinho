#include <stdio.h>
#include "raylib.h"
#include "player.h"




void movPlayer (int *direcao, int *totalFrame, jogador *player, int *pulo){
    //Controles do personagem
    *direcao = 0;
    *totalFrame = 6;
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        *direcao = 4;
        *totalFrame = 7;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        (*player).posicao.x += 4.0f;
        (*player).colisao.x += 4.0f;
        *direcao = 1;
        *totalFrame = 11;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        (*player).posicao.x -= 4.0f;
        (*player).colisao.x -= 4.0f;
        *direcao = 2;
        *totalFrame = 11;
    }
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && *pulo == 0  ){
        *pulo = 1;
    }
    if (IsKeyDown(KEY_J)){
        *direcao = 5;
        *totalFrame = 7;
    }if(IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_T)){
        *direcao = 6;
        *totalFrame = 4;
    }

    //Pulo
    if((*pulo == 1) && (*player).posicao.y !=325){
        (*player).posicao.y -= 5;
        (*player).colisao.y -= 5;
        *direcao = 3;
        *totalFrame =13;
    } 
    if((*player).posicao.y == 325) *pulo = 2;
    if((*pulo == 2) && ((*player).posicao.y != 425)){
        (*player).posicao.y += 5;
        (*player).colisao.y += 5;
        *direcao = 3;
        *totalFrame = 13;
    } 
    if((*player).posicao.y == 425) *pulo = 0;

}


void carregaPlayer();