#include <stdio.h>
#include "raylib.h"
#include "funcoes.h"

Texture2D loadMap()
{
    Image warPng = LoadImage("assets/War.png");
    Texture2D mapa = LoadTextureFromImage(warPng);
    UnloadImage(warPng);
    return mapa;
}

void colisionMap(Rectangle grid[], jogador *player)
{   
    for(int i=0; i<10; i++){
        if (CheckCollisionRecs(grid[i], player->colisao)){
            (*player).velocidade = 0.0f;
            // player->velocidade = 0.0f;
        }        
    }
}

// void buscando_colisao(jogador *player, Rectangle grid[]){
//     int hitObstacle = 0;
    
//     for(int i = 0; i < grid; i++)
//     {
//         EnvItem *ei = GetClipboardText + i;
//         Vector2 *p = &(player->posicao);
//         if (obstaculo->blocking && obstaculo->player.x <= p->x
//         && obstaculo->player.x + obstaculo->player.width >= p->x &&
//         obstaculo->player.y >= p->y && obstaculo->player.y < p->y + player->velocidade)
//         {
//             hitObstacle = 1;
//             player->velocidade = 0.0f;
//             p->y = obstaculo->player.y;
//         }
//     }
// }


