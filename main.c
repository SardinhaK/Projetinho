#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

int main(){
    int eixoX = 1980, eixoY=1080;
    Vector2 posicao = {1000, 50 };
    GameScreen currentScreen = LOGO;
    Rectangle boxA = { 10, GetScreenHeight()/2.0f - 50, 200, 100 };
    int boxASpeedX = 4;
    bool pause = false;             
    bool collision = false;

    InitWindow(eixoX, eixoY, "Ulala");
    SetTargetFPS(90);

    Texture fundo = LoadTexture("assets/fundo.png");
    Texture fundoI = LoadTexture("assets/images.png");
    Texture fundoF = LoadTexture("assets/final.png");
    currentScreen = TITLE;

    while (!WindowShouldClose()){
        if (IsKeyDown(KEY_RIGHT)) posicao.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) posicao.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) posicao.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) posicao.y += 2.0f;

        switch(currentScreen) // Tela de fundo
        {
            case TITLE:
            {
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                if (!pause) boxA.x += boxASpeedX;
                if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0)) boxASpeedX *= -1;
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
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
                    DrawTexture(fundoI, 10, 10, WHITE);
                    DrawText("Pau neles", 850, 20, 40, DARKGREEN);
                    DrawText("Para começar aperte o enter", 800, 220, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    DrawTexture(fundo, 10, 10, WHITE);
                    DrawCircleV(posicao, 50, MAROON);
                    //DrawRectangleRec(boxCollision, LIME);

                } break;
                case ENDING:
                {
                    DrawTexture(fundoF, 10, 10, WHITE);
                    DrawText("Morreu? NOOB!!!", 830, 20, 40, DARKBLUE);
                    DrawText("Para voltar a tela inicial aperte o enter", 790, 220, 20, DARKBLUE);

                } break;
                default: break;
            }


        ClearBackground(BLACK);
        EndDrawing();
    }



    UnloadTexture(fundo);
    UnloadTexture(fundoI);
    UnloadTexture(fundoF);
    CloseWindow();
    return 0;
}
