#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"
#include "player.h"

//       mingw32-make PLATFORM=PLATFORM_DESKTOP

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING, CONTROLS } GameScreen;




int main(){
    // Carregamento das variaveis
    int eixoX = 900, eixoY=600;
    int frameAtual = 0;
    int totalFrame = 7;
    int direcao = 0;
    int pulo = 0;
    int start=1; 
    bool pause = 0;
    float telaPassando = 0.0f;
    float parteFrente = 0.0f;
    float parteMeio = 0.0f;
    float parteMeio2 = 0.0f;
    float parteFundo = 0.0f;
    float time = 0.0f;
    GameScreen currentScreen = LOGO;
    Vector2 posCivil[3];
    //tiro disparo[30];
    jogador player;
    char msg1[20] = {"Start [Enter]"};
    char msg2[20] = {"Comandos [M]"};
    char msg3[20] = {"Fechar [Esc]"};
    char msg4[25] = {"Retornar [M]"};

  

 /* //Botao n funfa
    int botaoAcao=0;
    int botao = 0;
    Texture botaoI1 = LoadTexture("assets/normal.png");
    Texture botaoI2 = LoadTexture("assets/hover.png");
    Texture botaoI3 = LoadTexture("assets/pressed.png");
    Vector2 posMouse = { 0.0f, 0.0f };

    Rectangle mouseA = {0.0f, 0.0f, 20.0f, 20.0f};
    Rectangle btnBounds = { 300.0f, 200.0f , 270.0f, 100.0f };
    Rectangle sourceRec = { 0.0f, 0.0f, 270.0f, 100.0f};   */



    //Abrir a tela
    InitWindow(eixoX, eixoY, "Ulala");
    SetTargetFPS(60);
    InitAudioDevice();

    //Carregamento das texturas
    //Texture fundo = LoadTexture("assets/copa.png");

    //Frente
    Texture plano1 = LoadTexture("assets/telaInicial/inicio1plano.png");
    Texture plano2 = LoadTexture("assets/telaInicial/inicio2plano.png");
    Texture plano3 = LoadTexture("assets/telaInicial/houses2.png");
    Texture plano4 = LoadTexture("assets/telaInicial/inicio4plano.png");

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
                parteFrente -= 1.2f;
                parteMeio -= 0.7f;
                parteMeio2 -= 0.3f;
                parteFundo -= 0.1f;

                if (parteFrente <= -plano1.width*2) parteFrente = 0;
                if (parteMeio <= -plano2.width*2) parteMeio = 0;
                if (parteMeio2 <= -plano3.width*2) parteMeio2 = 0;
                if (parteFundo <= -plano4.width*2) parteFundo = 0;

                /* posMouse.x = GetMouseX(); // Mouse n funfa
                posMouse.y = GetMouseY();
                mouseA = (Rectangle) {(float)posMouse.x, (float)posMouse.x, 15, 15};
                botaoAcao = 0;
                botao = 0;

                if (CheckCollisionRecs(mouseA, btnBounds))
                {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) botao = 2;
                    else botao = 1;

                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) botaoAcao = 1;
                else botao = 0;
                } 
                if (botaoAcao){
                    currentScreen = GAMEPLAY;
                } */
                

                // Condição de ir a proxima tela
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = GAMEPLAY;
                }
                if (IsKeyPressed(KEY_M)){
                    currentScreen = CONTROLS;
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
                    
                    //telaPassando = 0.0f;
                    direcao = 0;
                    pulo = 0;
                    posCivil[0].x = 1100;
                    posCivil[0].y = 420;
                    posCivil[1].x = 1200;
                    posCivil[1].y = 410;
                    posCivil[2].x = 1000;
                    posCivil[2].y = 430;

                    pause = 0;
                    start = 0;
                }

                if (IsKeyPressed(KEY_P)) pause = !pause;

                if(!pause){
                    if(posCivil[1].x > -250){
                        posCivil[0].x -= 4.0f;
                        posCivil[1].x -= 4.0f;
                        posCivil[2].x -= 4.0f;
                    }

                    movPlayer(&direcao, &totalFrame, &player, &pulo);
                    if(direcao == 6){
                        //atirando(player, &disparo);
                    }
                }else{
                    if (IsKeyPressed(KEY_M)){
                    currentScreen = TITLE;
                }
                }


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
            case CONTROLS:
            {
                if (IsKeyPressed(KEY_M)){
                    currentScreen = TITLE;
                }
            }break;
            default: 
            break;
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen) // Tela de fundo
            {
                case TITLE:
                {  
                    DrawTextureEx(plano4, (Vector2){ parteFundo, 0 }, 0.0f, 2.0f, WHITE);
                    DrawTextureEx(plano4, (Vector2){ plano4.width*2 + parteFundo, 0 }, 0.0f, 2.0f, WHITE);

                    DrawTextureEx(plano3, (Vector2){ parteMeio2, 0 }, 0.0f, 2.0f, WHITE);
                    DrawTextureEx(plano3, (Vector2){ plano3.width*2 + parteMeio2, 0 }, 0.0f, 2.0f, WHITE);

                    DrawTextureEx(plano2, (Vector2){ parteMeio, 0 }, 0.0f, 2.0f, WHITE);
                    DrawTextureEx(plano2, (Vector2){ plano2.width*2 + parteMeio, 0 }, 0.0f, 2.0f, WHITE);

                    DrawTextureEx(plano1, (Vector2){ parteFrente, 0 }, 0.0f, 2.0f, WHITE);
                    DrawTextureEx(plano1, (Vector2){ plano4.width*2 + parteFrente, 0 }, 0.0f, 2.0f, WHITE);

                    DrawRectangle(605, 500, 230, 70, BLACK);
                    DrawRectangle(605, 300, 230, 70, BLACK);
                    DrawRectangle(605, 400, 230, 70, BLACK);
                    DrawText(msg1, 620, 320, 30, RED);
                    DrawText(msg2, 620, 420, 30, RED);
                    DrawText(msg3, 620, 520, 30, RED);


                   /*  if(botao == 0){ //      Mouse n funfa
                        DrawTextureEx(botaoI1, (Vector2){ 0, 0 }, 0.0f, 0.0f, WHITE);
                    }else if( botao == 1){
                        DrawTextureRec(botaoI2, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE);
                    }else if(botao == 2){
                        DrawTextureRec(botaoI3, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE);
                    } 
 */
                } break;
                case GAMEPLAY:
                {
                    if(!pause){
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
                    }else{
                        DrawText("Pause", 50, 20, 60, DARKGREEN);
                        DrawText("Retornar ao Menu [M]", 550, 520, 30, RED);
                    }
                   
                } break;
                case ENDING:
                {
                    DrawTexture(fundoF, 125, 0, WHITE);
                    DrawText("Morreu? NOOB!!!", 250, 20, 40, DARKBLUE);
                    DrawText("Para voltar a tela inicial aperte o enter", 250, 50, 20, DARKBLUE);

                } break;
                case CONTROLS:
                {
                    DrawTextureEx(plano4, (Vector2){ parteFundo, 0 }, 0.0f, 2.0f, WHITE);
                    DrawTextureEx(plano4, (Vector2){ plano4.width*2 + parteFundo, 0 }, 0.0f, 2.0f, WHITE);

                    DrawTextureEx(plano3, (Vector2){ parteMeio2, 0 }, 0.0f, 2.0f, WHITE);
                    DrawTextureEx(plano3, (Vector2){ plano3.width*2 + parteMeio2, 0 }, 0.0f, 2.0f, WHITE);

                    DrawTextureEx(plano2, (Vector2){ parteMeio, 0 }, 0.0f, 2.0f, WHITE);
                    DrawTextureEx(plano2, (Vector2){ plano2.width*2 + parteMeio, 0 }, 0.0f, 2.0f, WHITE);

                    DrawTextureEx(plano1, (Vector2){ parteFrente, 0 }, 0.0f, 2.0f, WHITE);
                    DrawTextureEx(plano1, (Vector2){ plano4.width*2 + parteFrente, 0 }, 0.0f, 2.0f, WHITE);

                    DrawRectangle(605, 500, 230, 70, BLACK);
                    DrawText(msg4, 620, 520, 30, RED);
                    DrawText("Controles:", 20, 20, 50, WHITE);
                    DrawText("W,A,S,D ou as setas do teclado", 20, 75, 25, RED);
                    DrawText(" para andar", 410, 75, 25, BLACK);
                    DrawText("ESPAÇO", 20, 105, 25, RED);
                    DrawText(" para atirar", 120, 105, 25, BLACK);


                } break;

                default: break;
            }

        ClearBackground(BLACK);
        EndDrawing();
    }

/* 
    UnloadTexture(botaoI1); // Mouse n funfa
    UnloadTexture(botaoI2);
    UnloadTexture(botaoI3);   */
    UnloadTexture(plano4);
    UnloadTexture(plano3);
    UnloadTexture(plano2);
    UnloadTexture(plano1);
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