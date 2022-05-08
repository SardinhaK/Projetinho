#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"
#include "player.h"

//       mingw32-make PLATFORM=PLATFORM_DESKTOP

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;




int main(){
    // Carregamento das variaveis
    int eixoX = 900, eixoY=600;
    jogador player;
    GameScreen currentScreen = LOGO;
    float telaPassando = 0.0f;
    int frameAtual = 0;
    int totalFrame = 7;
    float time = 0.0f;
    int direcao = 0;
    int pulo = 0;
    int start; 
    Vector2 posCivil[3];


    //Abrir a tela
    InitWindow(eixoX, eixoY, "Ulala");
    SetTargetFPS(60);
    InitAudioDevice();

    //Carregamento das texturas
    //Texture fundo = LoadTexture("assets/copa.png");
    Texture fundo = LoadTexture("assets/Mission 1.png");
    Texture fundoI = LoadTexture("assets/images.png");
    Texture fundoF = LoadTexture("assets/final.png");
    Texture personagemJoinha = LoadTexture("assets/MarcoJoinha.png");
    Texture personagemDireita = LoadTexture("assets/MarcoD.png");
    Texture personagemEsquerda = LoadTexture("assets/MarcoE.png");
    Texture personagemParado = LoadTexture("assets/MarcoParado.png");
    Texture personagemSentado = LoadTexture("assets/MarcoSentado.png"); 
    Texture personagemPulo = LoadTexture("assets/MarcoPulo.png");
    Texture personagemTiro = LoadTexture("assets/MarcoAtirando.png");
    Texture civil1 = LoadTexture("assets/civil1.png");
    Texture civil2 = LoadTexture("assets/civil2.png");
    Texture civil3 = LoadTexture("assets/civil3.png");
    
    Sound pulou = LoadSound("assets/pulo.mp3");
    Sound joia = LoadSound("assets/joinha.mp3");

    currentScreen = TITLE;

    while (!WindowShouldClose()){

        time += GetFrameTime();
        if(time >= 0.1f){
            time = 0.0f;
            frameAtual += 1;
        }
        frameAtual = frameAtual % totalFrame;

        switch(currentScreen) // Tela de fundo
        {
            case TITLE:
            {
                start = 1;
                // Condição de ir a proxima tela
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                if(start == 1){
                    player.posicao.x = 50;
                    player.posicao.y = 425;
                    player.colisao.x = 50;
                    player.colisao.y = 425;
                    player.colisao.height = 140;
                    player.colisao.width = 50;
                    
                    telaPassando = 0.0f;
                    direcao = 0;
                    pulo = 0;
                    posCivil[0].x = 1100;
                    posCivil[0].y = 420;
                    posCivil[1].x = 1200;
                    posCivil[1].y = 410;
                    posCivil[2].x = 1000;
                    posCivil[2].y = 430;

                    start = 0;
                }
                if(posCivil[1].x > -250){
                    posCivil[0].x -= 4.0f;
                    posCivil[1].x -= 4.0f;
                    posCivil[2].x -= 4.0f;
                }

                movPlayer(&direcao, &totalFrame, &player, &pulo);
                //Posição do player se limitando a meia tela e sem voltar cena
                if(player.posicao.x >= 450){
                telaPassando -= 4.0f;
                player.posicao.x -= 4.0f;
                }else if(player.posicao.x <= 0){
                player.posicao.x += 4.0f;
                }
                if (telaPassando <= -fundo.width) telaPassando = 0; 

               
                //Condição para passar a proxima tela
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:

            {   
                //Condição para passar a proxima tela
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = TITLE;
                }
            } break;
            default: 
            break;
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen) // Tela de fundo
            {
                case TITLE:
                {
                    DrawTexture(fundoI, 0, 0, WHITE);
                    DrawText("Pau neles", 150, 20, 40, DARKGREEN);
                    DrawText("Para começar aperte o enter", 350, 50, 20, DARKGREEN);
                } break;
                case GAMEPLAY:
                {
                    DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                    DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                    DrawTextureRec(civil1,(Rectangle) {(civil1.width /10)*frameAtual, 0, civil1.width/10, civil1.height}, posCivil[0], WHITE);
                    DrawTextureRec(civil2,(Rectangle) {(civil2.width /12)*frameAtual, 0, civil2.width/12, civil2.height}, posCivil[1], WHITE);
                    DrawTextureRec(civil3,(Rectangle) {(civil3.width /12)*frameAtual, 0, civil3.width/12, civil3.height}, posCivil[2], WHITE);

                    if(direcao == 0){       //Caso ele fique parado
                        DrawTextureRec(personagemParado,(Rectangle) {(personagemParado.width /totalFrame)*frameAtual, 0, personagemParado.width/totalFrame, personagemParado.height}, player.posicao, WHITE);

                    }else if(direcao == 1) {     // Caso ande para direita
                        DrawTextureRec(personagemDireita,(Rectangle) {(personagemDireita.width /totalFrame)*frameAtual, 0, personagemDireita.width/totalFrame, personagemDireita.height}, player.posicao, WHITE);

                    }else if(direcao == 2){     //Caso ande a esquerda
                        DrawTextureRec(personagemEsquerda,(Rectangle) {(personagemEsquerda.width /totalFrame)*frameAtual, 0, personagemEsquerda.width/totalFrame, personagemEsquerda.height}, player.posicao, WHITE);
                    }else if(direcao == 3){     //Caso de um Pulo
                        DrawTextureRec(personagemPulo,(Rectangle) {(personagemPulo.width /totalFrame)*frameAtual, 0, personagemPulo.width/totalFrame, personagemPulo.height}, player.posicao, WHITE);
                    }else if(direcao == 4){     //Caso ele sente
                        player.posicao.y +=40;
                        DrawTextureRec(personagemSentado,(Rectangle) {(personagemSentado.width /totalFrame)*frameAtual, 0, personagemSentado.width/totalFrame, personagemSentado.height}, player.posicao, WHITE);
                        player.posicao.y -=40;
                    }else if(direcao == 5){     //Caso dele dando um joinha
                        DrawTextureRec(personagemJoinha,(Rectangle) {(personagemJoinha.width /totalFrame)*frameAtual, 0, personagemJoinha.width/totalFrame, personagemJoinha.height}, player.posicao, WHITE);
                    }else if(direcao == 6){
                        DrawTextureRec(personagemTiro,(Rectangle) {(personagemTiro.width /totalFrame)*frameAtual, 0, personagemTiro.width/totalFrame, personagemTiro.height}, player.posicao, WHITE);
                    }
                    
                   
                } break;
                case ENDING:
                {
                    DrawTexture(fundoF, 125, 0, WHITE);
                    DrawText("Morreu? NOOB!!!", 250, 20, 40, DARKBLUE);
                    DrawText("Para voltar a tela inicial aperte o enter", 250, 50, 20, DARKBLUE);

                } break;
                default: break;
            }

        ClearBackground(BLACK);
        EndDrawing();
    }



    UnloadTexture(fundo);
    UnloadTexture(fundoI);
    UnloadTexture(fundoF);
    UnloadTexture(personagemJoinha);
    UnloadTexture(personagemDireita);
    UnloadTexture(personagemEsquerda);
    UnloadTexture(personagemSentado);
    UnloadTexture(personagemParado);
    UnloadTexture(personagemPulo);
    UnloadTexture(personagemTiro);
    UnloadTexture(civil1);
    UnloadTexture(civil2);
    UnloadTexture(civil3);

    UnloadSound(pulou);
    UnloadSound(joia);

    
    
    CloseWindow();

    CloseAudioDevice();
    return 0;
}