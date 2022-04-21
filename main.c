#include <raylib.h>
#include <stdio.h>
#include <math.h>
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
// dsakldjasldjasd


float d2(Vector2 a, Vector2 b) {
    return ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(0, 0, "raylib [core] example - mouse input");
    if (!IsWindowFullscreen()) ToggleFullscreen();

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    const float W2 = screenWidth / 2.0f;
    const float H2 = screenHeight / 2.0f;

    Texture ff_img = LoadTexture("assets/ff.png");
    Texture chico_img = LoadTexture("assets/chico1.png");

    Sound song = LoadSound("assets/yes-baby.wav");
    InitAudioDevice();
    SetMasterVolume(0.2f);
    int playing = 0;


    printf("%f, %f\n", W2, H2);

    Vector2 player = {.x = 10.0f, .y = 10.0f};
    const float pspeed = 250.0f;
    Camera2D camera = {.offset = {screenWidth / 2.0f, screenHeight / 2.0f},
                       .target = {0},
                       .rotation = 0,
                       .zoom = 1};

    SetTargetFPS(60);

    double time = GetTime();

    char buf[500] = {0};
    float dprev = 0.0f;

    while (!WindowShouldClose() && !IsKeyPressed(KEY_CAPS_LOCK)) {
        double delta = GetTime() - time;
        time = GetTime();

        if (IsKeyDown(KEY_W)) {
            player.y -= pspeed * delta;
        }

        if (IsKeyDown(KEY_S)) {
            player.y += pspeed * delta;
        }

        if (IsKeyDown(KEY_D)) {
            player.x += pspeed * delta;
        }

        if (IsKeyDown(KEY_A)) {
            player.x -= pspeed * delta;
        }

        float camd =
            d2(camera.target, (Vector2){.x = player.x, .y = player.y}) / 100.0f;
        float dDelta = abs(camd - dprev);

        float err = camd + (dDelta * 10.0f);

        if (err > 80.0f) {
            camera.target.x += ((player.x) - camera.target.x) * 0.005;
            camera.target.y += ((player.y) - camera.target.y) * 0.005;
        }

        dprev = camd;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        sprintf(buf, "%02.02f, cam: (%02.02f, %02.0f2), p (%02.02f, %02.02f)",
                err, camera.target.x, camera.target.y, player.x, player.y);
        if(playing) DrawText("Yes baby", 10, 50, 15, RED);
        DrawText(buf, 10, 10, 20, DARKGRAY);

        BeginMode2D(camera);


        DrawCircle(0, 0, 10, BLUE);
        DrawRectangle(player.x, player.y, 40, 40, RED);

        DrawText(
            "Este círculo azul é o centro do mundo.\nUse WASD para se "
            "movimentar...",
            10, 10, 20, DARKGRAY);

        DrawText("Este mundo é a sua tela, o código é a sua tinta.", 700, 10,
                 20, DARKGRAY);


        DrawTexture(ff_img, 1400, 100, WHITE);
        DrawText("Você pode usar imagens.", 1400, 10,
                 20, DARKGRAY);


        int par = ((int)GetTime())%2;
        DrawTextureRec(chico_img, (Rectangle) {256 * par, 0, 256, 256 }, (Vector2){2100, 100}, WHITE);
        DrawText("Animações???", 2100, 10,
                 20, DARKGRAY);

        if(!playing && player.x > 1800) {
            PlaySound(song);
            playing = 1;
        }
        DrawText("Música?", 2700, 10,
                 20, DARKGRAY);


        DrawText("Projeto de IP OwO", 3200, 10,
                 40, BLACK);

        DrawText("Estamos ansiosos para ver\no que vocês vão criar.", 3200, 70,
                 30, BLUE);


        EndMode2D();
        EndDrawing();
    }

    UnloadTexture(chico_img);
    UnloadTexture(ff_img);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
