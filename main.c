#include <raylib.h>
#include <stdlib.h>
#define FPS 60
#define COUNT 6

typedef struct {
    int x, y;
} pos;

void init() {
    InitWindow(800, 450, "game of life");
    SetTargetFPS(FPS);
}

void renderBird(pos pos) { DrawCircle(pos.x, pos.y, 20, GREEN); }
void renderPipe(pos pos) {
    DrawRectangle(pos.x, pos.y, 40, 800 - pos.y, GRAY);
    DrawRectangle(pos.x, 0, 40, pos.y - 60, LIGHTGRAY);
}

int main(void) {
    pos bird = {.x = 400, .y = 225};
    pos column[COUNT];
    for (int i = 0; i < COUNT; ++i)
        column[i] = (pos){.y = rand() % 450, .x = i * 200};
    int jump_countdown = 0;

    init();
    while (!WindowShouldClose()) {
        if (jump_countdown > 0) {
            bird.y = bird.y - 7;
            jump_countdown = jump_countdown - 1;
        }
        if (IsKeyPressed(KEY_SPACE))
            jump_countdown = FPS;
        bird.y = bird.y + 5;

        for (int i = 0; i < COUNT; ++i)
            column[i].x -= 1;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        renderBird(bird);
        for (int i = 0; i < COUNT; ++i)
            renderPipe(column[i]);
        EndDrawing();
    }
}
