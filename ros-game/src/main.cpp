#include <raylib.h>

int main() {
    InitWindow(800, 600, "Realm Of Spells. The Online Duelling Card Game. by @TKGS");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Yooo what a gameplay", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}