#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"
#include "funcoes.h"

//       mingw32-make PLATFORM=PLATFORM_DESKTOP

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING, CONTROLS, WIN } GameScreen;




int main(){
    // Carregamento das variaveis
    int eixoX = 900, eixoY=600;
    int frameAtual = 0;
    int totalFrame = 7;
    int direcao = 0;
    int pulo = 0;
    bool pause = 0;
    float parteFrente = 0.0f;
    float parteMeio = 0.0f;
    float parteMeio2 = 0.0f;
    float parteFundo = 0.0f;
    float time = 0.0f;
    GameScreen currentScreen = LOGO;
    Vector2 posCivil[3];
    jogador player;
    shoot disparo[50]; //https://www.raylib.com/examples.html
    int shootRate = 0;
    Rectangle inimigo = {890.0f, 0.0f, 30.0f, 150.0f};
    int vidaIni;
    int movIni;
    int nivel = 0;
    shootInimigo disparoInimigo[50];
    int qtdBalaInimigo = 1;
    int flagMenu=1;
    int start=1; 
    int flagMorreu=0;
    int flagVenceu=0;

    /* Rectangle grid[10];
    grid[0].width = 100;
    grid[0].height = 30;
    grid[0].x = 200;
    grid[0].y = 450; */
   
  


    //Abrir a tela
    InitWindow(eixoX, eixoY, "Ulala");
    SetTargetFPS(60);
    InitAudioDevice();


    //Frente
    Texture plano1 = LoadTexture("assets/telaInicial/inicio1plano.png");
    Texture plano2 = LoadTexture("assets/telaInicial/inicio2plano.png");
    Texture plano3 = LoadTexture("assets/telaInicial/houses2.png");
    Texture plano4 = LoadTexture("assets/telaInicial/inicio4plano.png");
    Texture fialho = LoadTexture("assets/unknown.png");

    Texture fundoF = LoadTexture("assets/gameover.png");
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
    Texture fase1 = LoadTexture("assets/War.png");
    Texture fase2 = LoadTexture("assets/War2.png");
    Texture fase3 = LoadTexture("assets/War4.png");
    Texture inimigoIm = LoadTexture("assets/bills.png");
    Texture imBala = LoadTexture("assets/tiro.png");

    Sound pulou = LoadSound("assets/pulo.mp3");   
    Sound joia = LoadSound("assets/joinha.mp3");
    Sound musMenu = LoadSound("assets/menu_theme.mp3");
    Sound musGame = LoadSound("assets/gameplay_theme.mp3");
    Sound musDerrota = LoadSound("assets/gameover_theme.mp3");

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
                if(flagMenu ==1){
                    PlaySound(musMenu);
                    flagMenu =0;
                }
                start = 1;
                nivel=1;
                parteFrente -= 1.2f;
                parteMeio -= 0.7f;
                parteMeio2 -= 0.3f;
                parteFundo -= 0.1f;

                if (parteFrente <= -plano1.width*2) parteFrente = 0;
                if (parteMeio <= -plano2.width*2) parteMeio = 0;
                if (parteMeio2 <= -plano3.width*2) parteMeio2 = 0;
                if (parteFundo <= -plano4.width*2) parteFundo = 0;


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
                    StopSound(musMenu);
                    PlaySound(musGame);
                    if(nivel ==1){
                        vidaIni = 15;
                        movIni = 5; 
                        player.velocidade = 7.0f;
                        qtdBalaInimigo = 6;
                    }
                    if(nivel == 2){
                        vidaIni = 45;
                        movIni = 8; 
                        player.velocidade = 10.0f;
                        qtdBalaInimigo = 10;
                    }
                    if(nivel ==3){
                        vidaIni = 95;
                        movIni = 10; 
                        player.velocidade = 13.0f;
                        qtdBalaInimigo = 15;
                    }
                    player.posicao.x = 50;
                    player.posicao.y = 425;
                    player.colisao.x = 75;
                    player.colisao.y = 425;
                    player.colisao.height = 140;
                    player.colisao.width = 50;
                    
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
                    for (int i = 0; i < 50; i++)
                    {
                        disparo[i].projet.x = player.posicao.x;
                        disparo[i].projet.y = player.posicao.y;
                        disparo[i].projet.width = 15;
                        disparo[i].projet.height = 3;
                        disparo[i].vel.x = 15;
                        disparo[i].vel.y = 0;
                        disparo[i].active = false;
                        disparo[i].color = YELLOW;
                    }
                    for (int i = 0; i < qtdBalaInimigo; i++)
                    {
                        disparoInimigo[i].projet.width = 20;
                        disparoInimigo[i].projet.height = 20;
                        disparoInimigo[i].projet.x = GetRandomValue(eixoX, eixoX + 1000);
                        disparoInimigo[i].projet.y = GetRandomValue(0, eixoY - disparoInimigo[i].projet.height);
                        disparoInimigo[i].vel.x = 5;
                        disparoInimigo[i].vel.y = 5;
                        disparoInimigo[i].active = true;
                        disparoInimigo[i].color = GRAY;
                    }
                }

                if (IsKeyPressed(KEY_P)) pause = !pause;

                if(!pause){
                    if(posCivil[1].x > -250){
                        posCivil[0].x -= 4.0f;
                        posCivil[1].x -= 4.0f;
                        posCivil[2].x -= 4.0f;
                    }
 
                    movPlayer(&direcao, &totalFrame, &player, &pulo);
                    if(direcao == 6 ){
                        shootRate += 5;

                        for (int i = 0; i < 50; i++){
                            if (! disparo[i].active && shootRate%20 == 0){
                                disparo[i].projet.x = player.posicao.x+140;
                                disparo[i].projet.y = player.posicao.y+48;
                                disparo[i].active = true;
                                break;
                            }
                        }
                    }

                    for (int i = 0; i < 50; i++){
                        if (disparo[i].active){
                            // Movement
                            disparo[i].projet.x += disparo[i].vel.x;
                            if (disparo[i].projet.x + disparo[i].projet.width >= 910){
                                    disparo[i].active = false;
                                    shootRate = 0;
                            }
                            if(CheckCollisionRecs(disparo[i].projet, inimigo)){
                                vidaIni --;
                            }
                        }
                    }
                    inimigo.y += movIni;
                    if(inimigo.y >= 450 || inimigo.y <= 0) movIni *= -1;

                    for (int i = 0; i < qtdBalaInimigo; i++)
                    {
                        if (disparoInimigo[i].active)
                        {
                            disparoInimigo[i].projet.x -= disparoInimigo[i].vel.x;

                            if (disparoInimigo[i].projet.x < 0)
                            {
                                disparoInimigo[i].projet.x = GetRandomValue(eixoX, eixoX + 1000);
                                disparoInimigo[i].projet.y = GetRandomValue(0, eixoY - disparoInimigo[i].projet.height);
                            }
                        }
                    }
                    for (int i = 0; i < qtdBalaInimigo; i++)
                    {
                        if (CheckCollisionRecs(player.colisao, disparoInimigo[i].projet)){
                            currentScreen = ENDING;
                            flagMorreu =1;
                        } 
                    }

                    
                }else{
                    if (IsKeyPressed(KEY_M)){
                        currentScreen = TITLE;
                        flagMenu =1;
                    }
                }


                //Condição para passar a proxima tela
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = ENDING;
                    flagMorreu =1;
                }

                if(vidaIni == 0){
                    start = 1;
                    //currentScreen = WIN;
                }                
                if(vidaIni == 0) nivel++;
                if(nivel == 4)currentScreen = WIN;
            } break;
            
            case ENDING:
            {   
                if(flagMorreu ==1){
                    StopSound(musGame);
                    PlaySound(musDerrota);
                    flagMorreu =0;
                }
                //Condição para passar a proxima tela
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = TITLE;
                    flagMenu=1;
                }
            } break;
            case CONTROLS:
            {
                if (IsKeyPressed(KEY_M)){
                    currentScreen = TITLE;
                }
            }break;
            case WIN:
            {
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = TITLE;
                    flagMenu =1;
                }
            }
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
                    DrawText("Start [Enter]", 620, 320, 30, RED);
                    DrawText("Comandos [M]", 620, 420, 30, RED);
                    DrawText("Fechar [Esc]", 620, 520, 30, RED);
                    DrawText("NOME DO JOGO!", 20, 20, 70, WHITE);
                    DrawText("Mate o maximo de inimigos que puder", 20, 100, 30, BLACK);
                    DrawText("A sua pontuação depende disso!", 20, 140, 30, RED);

                  
                } break;
                case GAMEPLAY:
                {
                    if(!pause){
                        DrawTexture(fase1, 0, 0, WHITE);
                        if(nivel ==2)DrawTexture(fase2, 0, 0, WHITE);
                        if(nivel ==3)DrawTexture(fase3, 0, 0, WHITE);
                        DrawTextureRec(inimigoIm,(Rectangle) {(inimigoIm.width /4)*frameAtual, 0, inimigoIm.width/4, personagemEsquerda.height}, (Vector2){(inimigo.x-30), inimigo.y}, WHITE);
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
                        for (int i = 0; i < 50; i++){
                            if (disparo[i].active) DrawRectangleRec(disparo[i].projet, disparo[i].color);
                        }
                        for (int i = 0; i < qtdBalaInimigo; i++)
                        {
                            if (disparoInimigo[i].active) {
                                DrawTexture(imBala, disparoInimigo[i].projet.x-5, disparoInimigo[i].projet.y-5, WHITE);
                                //DrawRectangleRec(disparoInimigo[i].projet, disparoInimigo[i].color); //Hitbox tiro inimigo
                            }
                        }
                        //DrawRectangleRec(player.colisao, BLACK); //Hitbox player
                    }else{
                        DrawText("Pause", 50, 20, 60, DARKGREEN);
                        DrawText("Retornar ao Menu [M]", 550, 520, 30, RED);
                    }
                   
                } break;
                case ENDING:
                {
                    DrawTexture(fundoF, 44, 0, WHITE);
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
                    DrawText("Retornar [M]", 620, 520, 30, RED);
                    DrawText("Controles:", 20, 20, 50, WHITE);
                    DrawText("W,A,S,D ou as setas do teclado", 20, 75, 25, RED);
                    DrawText(" para andar", 410, 75, 25, BLACK);
                    DrawText("ESPAÇO", 20, 105, 25, RED);
                    DrawText(" para atirar", 120, 105, 25, BLACK);


                } break;
                case WIN:
                {
                    DrawTexture(fialho, 125, 0, WHITE);
                }

                default: break;
            }

            ClearBackground(BLACK);
            EndDrawing();
        
    }

   
    UnloadTexture(plano4);
    UnloadTexture(plano3);
    UnloadTexture(plano2);
    UnloadTexture(plano1);
    UnloadTexture(fialho);
    UnloadTexture(inimigoIm);
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
    UnloadSound(musMenu);
    UnloadSound(musGame);
    UnloadSound(musDerrota);

    
    
    CloseWindow();
    CloseAudioDevice();
    
    return 0;

}