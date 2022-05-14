#include <stdio.h>
#include "raylib.h"
#include "funcoes.h"



void movPlayer (int *direcao, int *totalFrame, jogador *player, int *pulo, Rectangle *grid){
    //Controles do personagem
    *direcao = 0;
    *totalFrame = 6;
    if((*player).colisao.y >= 650){
        (*player).colisao.y= -100;
        (*player).posicao.y= -100;
    }
    
    if(IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_T)){
        *direcao = 6;
        *totalFrame = 4;
    }
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        *direcao = 4;
        *totalFrame = 7;
        (*player).colisao.height = 70.0f;
        (*player).colisao.y = (*player).posicao.y;
    }else{
        (*player).colisao.height = 140.0f;
    }

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        (*player).posicao.x += (*player).velocidade.x;
        (*player).colisao.x += (*player).velocidade.x;
        *direcao = 1;
        *totalFrame = 11;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        (*player).posicao.x -= (*player).velocidade.x;
        (*player).colisao.x -= (*player).velocidade.x;
        *direcao = 2;
        *totalFrame = 11;
        if((*player).posicao.x <= -40){
            (*player).posicao.x += (*player).velocidade.x;
            (*player).colisao.x += (*player).velocidade.x;
        }
    }
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && *pulo == 0  ){
        *pulo = 1;
        (*player).posicao.y -= 230;
        (*player).colisao.y -= 230;
    }
    if (IsKeyDown(KEY_J)){
        *direcao = 5;
        *totalFrame = 7;
    }

    //Colisão
    int platColisao = 0;
    for(int i = 0; i<3; i++){
        Rectangle plataform = grid[i];
        Vector2 *r = &((*player).posicao);
        if(plataform.x <= r->x && plataform.x + plataform.width >= r->x &&
        plataform.y == r->y + (*player).colisao.height){
            platColisao = 1;
        }
        DrawRectangle(plataform.x, plataform.y, plataform.width, plataform.height, RED);
    }
    
    if(!platColisao){
        (*player).posicao.y += (*player).velocidade.y;
        (*player).colisao.y += (*player).velocidade.y;
        (*player).velocidade.y = 10.0;
        *direcao = 3;
        *totalFrame = 13;
    }else{
        *pulo = 0;
        (*player).velocidade.y = 0;
    } 

}

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
