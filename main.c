#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

int main(){
    // Carregamento das variaveis
    int eixoX = 900, eixoY=600;
    Vector2 posPlayer = {50, 425};
    GameScreen currentScreen = LOGO;
    float telaPassando = 0.0f;
    int frameAtual = 0;
    int totalFrame = 7;
    float time = 0.0f;
    int direcao = 0;
    int pulo = 0;

    //Abrir a tela
    InitWindow(eixoX, eixoY, "Ulala");
    SetTargetFPS(60);
    InitAudioDevice();

    //Carregamento das texturas
    Texture fundo = LoadTexture("assets/Mission 1.png");
    Texture fundoI = LoadTexture("assets/images.png");
    Texture fundoF = LoadTexture("assets/final.png");
    Texture personagemJoinha = LoadTexture("assets/MarcoJoinha.png");
    Texture personagemDireita = LoadTexture("assets/MarcoD.png");
    Texture personagemEsquerda = LoadTexture("assets/MarcoE.png");
    Texture personagemParado = LoadTexture("assets/MarcoParado.png");
    Texture personagemSentado = LoadTexture("assets/MarcoSentado.png");
    Texture personagemPulo = LoadTexture("assets/MarcoPulo.png");
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
                // Condição de ir a proxima tela
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                //Controles do personagem
                direcao = 0;
                totalFrame = 6;
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
                    posPlayer.x += 4.0f;
                    direcao = 1;
                    totalFrame = 11;
                }
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
                    posPlayer.x -= 4.0f;
                    direcao = 2;
                    totalFrame = 11;
                }
                if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && pulo == 0  ){
                    PlaySound(pulou);
                    pulo = 1;
                }
                if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
                    direcao = 4;
                    totalFrame = 7;
                }
                if (IsKeyDown(KEY_J)){
                    PlaySound(joia);
                    direcao = 5;
                    totalFrame = 7;
                }
                

                //Pulo
                if((pulo == 1) && (posPlayer.y != 325)){
                    posPlayer.y -= 5;
                    direcao = 3;
                    totalFrame =13;
                } 
                if(posPlayer.y == 325) pulo = 2;
                if((pulo == 2) && (posPlayer.y != 425)){
                    posPlayer.y += 5;
                    direcao = 3;
                    totalFrame = 13;
                } 
                if(posPlayer.y == 425) pulo = 0;

                //Posição do player se limitando a meia tela e sem voltar cena
                if(posPlayer.x >= 450){
                telaPassando -= 4.0f;
                posPlayer.x -= 4.0f;
                }else if(posPlayer.x <= 0){
                posPlayer.x += 4.0f;
                }

                
                //Tela infinita para frente -->
                if (telaPassando <= -fundo.width) telaPassando = 0; 
               
                //Condição para passar a proxima tela
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {   
                //restart de fase, função mais p frente.
                posPlayer.x = 50;
                posPlayer.y = 425;
                telaPassando = 0.0f;
                direcao = 0;
                pulo = 0;
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
                    if(direcao == 0){       //Caso ele fique parado
                        DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureRec(personagemParado,(Rectangle) {(personagemParado.width /totalFrame)*frameAtual, 0, personagemParado.width/totalFrame, personagemParado.height}, posPlayer, WHITE);

                    }else if(direcao ==1) {     // Caso ande para direita
                        DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureRec(personagemDireita,(Rectangle) {(personagemDireita.width /totalFrame)*frameAtual, 0, personagemDireita.width/totalFrame, personagemDireita.height}, posPlayer, WHITE);

                    }else if(direcao == 2){     //Caso ande a esquerda
                        DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureRec(personagemEsquerda,(Rectangle) {(personagemEsquerda.width /totalFrame)*frameAtual, 0, personagemEsquerda.width/totalFrame, personagemEsquerda.height}, posPlayer, WHITE);
                    }else if(direcao == 3){     //Caso de um Pulo
                        DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureRec(personagemPulo,(Rectangle) {(personagemPulo.width /totalFrame)*frameAtual, 0, personagemPulo.width/totalFrame, personagemPulo.height}, posPlayer, WHITE);
                    }else if(direcao == 4){     //Caso ele sente
                        DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        posPlayer.y +=40;
                        DrawTextureRec(personagemSentado,(Rectangle) {(personagemSentado.width /totalFrame)*frameAtual, 0, personagemSentado.width/totalFrame, personagemSentado.height}, posPlayer, WHITE);
                        posPlayer.y -=40;
                    }else if(direcao == 5){     //Caso dele dando um joinha
                        DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureRec(personagemJoinha,(Rectangle) {(personagemJoinha.width /totalFrame)*frameAtual, 0, personagemJoinha.width/totalFrame, personagemJoinha.height}, posPlayer, WHITE);
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
    UnloadTexture(civil1);
    UnloadTexture(civil2);
    UnloadTexture(civil3);

    UnloadSound(pulou);
    UnloadSound(joia);

    
    
    CloseWindow();

    CloseAudioDevice();
    return 0;
}
