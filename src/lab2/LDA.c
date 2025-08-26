#include "apps.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void incDDA(Vector2 init, Vector2 final) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  float m = (float)dy / dx;
  float b = (float)init.y - m * init.x;

  float x = init.x, y = init.y;
  float step, xinc, yinc;
  step = fmax(abs(dy), abs(dx));
  xinc = dx / step;
  yinc = dy / step;
  for (int i = 0; i <= step; i++) {
    DrawPixel(round(x), round(y), WHITE);
    y = (y + yinc);
    x = (x + xinc);
  }
}

void bresenhamLDA(Vector2 init, Vector2 final) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  int sx = dx <= 0 ? -1 : 1;
  int sy = dy <= 0 ? -1 : 1;
  int p = 2 * dy - dx;
  float m = (float)dy / dx;

  int x = init.x, y = init.y;
  if (m < 1 && m > -1) {
    for (int i = 0; i < abs(dx); i++) {
      DrawPixel(x, y, WHITE);
      if (p < 0) {
        x += sx;
        p += 2 * dy;
      } else {
        x += sx;
        y += sy;
        p += 2 * dy - 2 * dx;
      }
    }
  } else {
    for (int i = 0; i < abs(dy); i++) {
      DrawPixel(x, y, WHITE);
      if (p < 0) {
        y += sy;
        p += 2 * dx;
      } else {
        x += sx;
        y += sy;
        p += 2 * dx - 2 * dy;
      }
    }
  }
}

void draw(Vector2 initial_point, Vector2 final_point) {
  incDDA(initial_point, final_point);

  // bresenhamLDA(initial_point, final_point);
}

int LDA() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "LDA");

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    Vector2 initial_point = {
        .x = 10,
        .y = 300,
    };
    Vector2 final_point = {
        .x = 100,
        .y = 200,
    };
    draw(initial_point, final_point);

    initial_point.x = 200;
    initial_point.y = 10;
    final_point.x = 300;
    initial_point.y = 200;
    draw(initial_point, final_point);

    initial_point.x = 300;
    initial_point.y = 150;
    final_point.x = 200;
    initial_point.y = 100;
    draw(initial_point, final_point);

    initial_point.x = 200;
    initial_point.y = 100;
    final_point.x = 100;
    initial_point.y = 100;
    draw(initial_point, final_point);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
