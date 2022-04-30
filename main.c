#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

int main(){
    int eixoX = 900, eixoY=600;
    Vector2 posPlayer = {50, 50};
    GameScreen currentScreen = LOGO;
    int boxASpeedX = 4;
    bool pause = false;             
    bool collision = false;
    float telaPassando = 0.0f;

    InitWindow(eixoX, eixoY, "Ulala");
    SetTargetFPS(60);

    Texture fundo = LoadTexture("assets/Mission 1.png");
    Texture fundoI = LoadTexture("assets/images.png");
    Texture fundoF = LoadTexture("assets/final.png");
    currentScreen = TITLE;

    while (!WindowShouldClose()){
        if (IsKeyDown(KEY_RIGHT)) posPlayer.x += 4.0f;
        if (IsKeyDown(KEY_LEFT)) posPlayer.x -= 4.0f;
        if (IsKeyDown(KEY_UP)) posPlayer.y -= 4.0f;
        if (IsKeyDown(KEY_DOWN)) posPlayer.y += 4.0f;
        if (telaPassando <= -fundo.width) telaPassando = 0; 
       


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
                telaPassando -= 3.0f;

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
                    DrawText("Pau neles", 50, 20, 40, DARKGREEN);
                    DrawText("Para começar aperte o enter", 50, 20, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    DrawTextureEx(fundo, (Vector2){ telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                    DrawTextureEx(fundo, (Vector2){ fundo.width + telaPassando, 0 }, 0.0f, 1.0f, WHITE);
                    DrawCircleV(posPlayer, 10, BLACK);

                } break;
                case ENDING:
                {
                    DrawTexture(fundoF, 10, 10, WHITE);
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
    CloseWindow();
    return 0;
}
