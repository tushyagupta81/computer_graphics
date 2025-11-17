#include "apps.h"
#include "raylib.h"
#include <cstdio>
#include <stdio.h>
#include <utility>

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

int get_encoding(Vector2 p, Vector2 topleft, Vector2 bottomright) {
  int encoding = 0;

  if (p.x < topleft.x) {
    encoding |= LEFT;
  }
  if (p.x > bottomright.x) {
    encoding |= RIGHT;
  }
  if (p.y < bottomright.y) {
    encoding |= BOTTOM;
  }
  if (p.y > topleft.y) {
    encoding |= TOP;
  }

  return encoding;
}

void cohen(Vector2 p, Vector2 q, Vector2 topleft, Vector2 bottomright) {
  int encp = get_encoding(p, topleft, bottomright);
  int encq = get_encoding(q, topleft, bottomright);
  // DrawLineV(p, q, BLACK);

  if (encp & encq) {
    return;
  }
  if (encq == 0 && encp == 0) {
    DrawCircleV(p, 2, BLACK);
    DrawCircleV(q, 2, BLACK);
    return;
  }

  if (p.x > q.x || encp == 0) {
    Vector2 temp = p;
    p = q;
    q = temp;
    std::swap(encq, encp);
  }

  float m = (q.y - p.y) / (q.x - p.x);
  if (encp & LEFT) {
    p.y += (topleft.x - p.x) * m;
    p.x = topleft.x;
  }
  if (encp & RIGHT) {
    p.y += (bottomright.x - p.x) * m;
    p.x = bottomright.x;
  }
  if (encp & BOTTOM) {
    p.x += (bottomright.y - p.y) / m;
    p.y = bottomright.y;
  }
  if (encp & TOP) {
    p.x += (topleft.y - p.y) / m;
    p.y = topleft.y;
  }

  cohen(p, q, topleft, bottomright);
}

int cohen_sutherland() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "cohen_sutherland");

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(WHITE);

    Vector2 a = {.x = 100, .y = 000};
    Vector2 b = {.x = 100, .y = 400};
    DrawLineV(a, b, BLACK);
    a.x += 300;
    b.x += 300;
    DrawLineV(a, b, BLACK);
    Vector2 c = {.x = 0, .y = 100};
    Vector2 d = {.x = 500, .y = 100};
    DrawLineV(c, d, BLACK);
    c.y += 200;
    d.y += 200;
    DrawLineV(c, d, BLACK);

    Vector2 bottomright = {.x = 400, .y = 100};
    Vector2 topleft = {.x = 100, .y = 300};
    // DrawCircleV(topleft, 2, BLACK);
    // DrawCircleV(bottomright, 2, BLACK);

    Vector2 p = {.x = 45, .y = 200};
    Vector2 q = {.x = 200, .y = 55};
    DrawLineV(p, q, BLACK);
    cohen(p, q, topleft, bottomright);

    p = {.x = 75, .y = 200};
    q = {.x = 225, .y = 200};
    DrawLineV(p, q, BLACK);
    cohen(p, q, topleft, bottomright);

    p = {.x = 250, .y = 50};
    q = {.x = 250, .y = 200};
    DrawLineV(p, q, BLACK);
    cohen(p, q, topleft, bottomright);

    p = {.x = 50, .y = 320};
    q = {.x = 200, .y = 320};
    DrawLineV(p, q, BLACK);
    cohen(p, q, topleft, bottomright);

    p = {.x = 50, .y = 275};
    q = {.x = 200, .y = 275};
    DrawLineV(p, q, BLACK);
    cohen(p, q, topleft, bottomright);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
