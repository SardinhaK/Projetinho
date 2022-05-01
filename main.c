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

    //Abrir a tela
    InitWindow(eixoX, eixoY, "Ulala");
    SetTargetFPS(60);

    //Carregamento das texturas
    Texture fundo = LoadTexture("assets/Mission 1.png");
    Texture fundoI = LoadTexture("assets/images.png");
    Texture fundoF = LoadTexture("assets/final.png");
    Texture personagemJoinha = LoadTexture("assets/MarcoJoinha.png");
    Texture personagemDireita = LoadTexture("assets/MarcoD.png");
    Texture personagemEsquerda = LoadTexture("assets/MarcoE.png");
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
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
                    posPlayer.x += 4.0f;
                    direcao = 1;
                    totalFrame = 11;
                }else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
                    posPlayer.x -= 4.0f;
                    direcao = 2;
                    totalFrame = 11;
                }else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)){ // Pulo nao implementado
                    //posPlayer.y -= 4.0f;
                    //direcao = 3;
                }else if (IsKeyDown(KEY_J)){
                    direcao = 5;
                }else{
                    direcao = 0;
                    totalFrame = 7;
                }

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
                    DrawText("Pau neles", 50, 20, 40, DARKGREEN);
                    DrawText("Para começar aperte o enter", 50, 50, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    if(direcao == 0){       //Caso ele fique parado
                        DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureRec(personagemJoinha,(Rectangle) {(personagemJoinha.width /totalFrame)*frameAtual, 0, personagemJoinha.width/totalFrame, personagemJoinha.height}, posPlayer, WHITE);

                    }else if(direcao ==1) {     // Caso ande para direita
                        DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureRec(personagemDireita,(Rectangle) {(personagemDireita.width /totalFrame)*frameAtual, 0, personagemDireita.width/totalFrame, personagemDireita.height}, posPlayer, WHITE);

                    }else if(direcao == 2){     //Caso ande a esquerda
                        DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                        DrawTextureRec(personagemEsquerda,(Rectangle) {(personagemEsquerda.width /totalFrame)*frameAtual, 0, personagemEsquerda.width/totalFrame, personagemEsquerda.height}, posPlayer, WHITE);
                    }
                   
                } break;
                case ENDING:
                {
                    DrawTexture(fundoF, 0, 0, WHITE);
                    DrawText("Morreu? NOOB!!!", 50, 20, 40, DARKBLUE);
                    DrawText("Para voltar a tela inicial aperte o enter", 50, 50, 20, DARKBLUE);

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
    CloseWindow();
    return 0;
}
