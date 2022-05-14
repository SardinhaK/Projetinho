#include <stdio.h>
#include "raylib.h"
#include "funcoes.h"



void movPlayer (int *direcao, int *totalFrame, jogador *player, int *pulo){
    float velPulo= 7.0f;
    //Controles do personagem
    *direcao = 0;
    *totalFrame = 6;
    
    if(IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_T)){
        *direcao = 6;
        *totalFrame = 4;
    }
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        *direcao = 4;
        *totalFrame = 7;
        (*player).colisao.height = 90.0f;
        (*player).colisao.y = (*player).posicao.y + 50.0f;
    }else{
        (*player).colisao.height = 140.0f;
        (*player).colisao.y = (*player).posicao.y;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        (*player).posicao.x += (*player).velocidade;
        (*player).colisao.x += (*player).velocidade;
        *direcao = 1;
        *totalFrame = 11;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        (*player).posicao.x -= (*player).velocidade;
        (*player).colisao.x -= (*player).velocidade;
        *direcao = 2;
        *totalFrame = 11;
    }
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && *pulo == 0  ){
        *pulo = 1;
    }
    if (IsKeyDown(KEY_J)){
        *direcao = 5;
        *totalFrame = 7;
    }



    




    //Pulo
    if((*pulo == 1) && (*player).posicao.y >= 225){
        (*player).posicao.y -= velPulo;
        (*player).colisao.y -= velPulo;
        *direcao = 3;
        *totalFrame =13;
    } 
    if((*player).posicao.y <= 225) *pulo = 2;
    if((*pulo == 2) && ((*player).posicao.y != 425)){
        (*player).posicao.y += velPulo;
        (*player).colisao.y += velPulo;
        *direcao = 3;
        *totalFrame = 13;
    } 
    if((*player).posicao.y == 425) *pulo = 0;

}

/* void atirando (jogador player, tiro *disparo){
    
} */

void carregaPlayer();




void atirar(int *shootRate, shoot **disparo, jogador *player){
    *shootRate += 5;

    for (int i = 0; i < 50; i++){
        if (! (*disparo)[i].active && *shootRate%20 == 0)
        {
            (*disparo)[i].projet.x = (*player).posicao.x+140;
            (*disparo)[i].projet.y = (*player).posicao.y+48;
            (*disparo)[i].active = true;
            break;
        }
    }


    for (int i = 0; i < 50; i++){
        if ((*disparo)[i].active){
            // Movement
            (*disparo)[i].projet.x += (*disparo)[i].vel.x;
            if ((*disparo)[i].projet.x + (*disparo)[i].projet.width >= 910){
                    (*disparo)[i].active = false;
                    *shootRate = 0;
            }
        }
    }
}
