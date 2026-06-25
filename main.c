#define CUTE_C2_IMPLEMENTATION
#include "cute_c2.h"
#include <raylib.h>
#include <stdlib.h>
#define FPS 60
#define COUNT 6
#define RADIUS 20
#define SIZE 40
#define GAP 120

typedef struct {
    int x, y;
} pos;

void init() {
    InitWindow(800, 450, "game of life");
    SetTargetFPS(FPS);
}

void renderBird(pos pos) { DrawCircle(pos.x, pos.y, RADIUS, GREEN); }
void renderPipe(pos pos) {
    DrawRectangle(pos.x, pos.y, SIZE, 800 - pos.y, GRAY);
    DrawRectangle(pos.x, 0, SIZE, pos.y - GAP, LIGHTGRAY);
}

int main(void) {
    pos bird = {.x = 300, .y = 225};
    pos column[COUNT];
    for (int i = 0; i < COUNT; ++i)
        column[i] = (pos){.y = rand() % 350, .x = i * 200};
    int jump_countdown = 0;
    c2Circle circle;
    c2AABB box1;
    c2AABB box2;
    int hit1;
    int hit2;
    int acc = 8;
    init();
    while (!WindowShouldClose()) {
        circle = (c2Circle){.p = {bird.x, bird.y}, .r = RADIUS};

        for (int i = 0; i < COUNT; ++i) {
            if (column[i].x < 0)
                column[i].x = column[COUNT - 1].x + 200;
        }
        for (int i = 0; i < COUNT; ++i) {
            c2AABB bottom = {.min = {column[i].x, column[i].y},
                             .max = {column[i].x + SIZE, 800}};
            c2AABB top = {.min = {column[i].x, 0},
                          .max = {column[i].x + SIZE, column[i].y - GAP}};
            if (c2CircletoAABB(circle, bottom) || c2CircletoAABB(circle, top))
                return 0;
        }
        if (jump_countdown > 0 && jump_countdown < 4) {
            acc -= 1;
        }
        if (jump_countdown == 0)
            acc = 8;
        if (jump_countdown > 0) {
            bird.y = bird.y - acc;
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
