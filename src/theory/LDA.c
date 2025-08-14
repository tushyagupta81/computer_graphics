#include "apps.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void simpleLDA(Vector2 init, Vector2 final) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  float m = (float)dy / dx;
  float b = (float)init.y - m * init.x;

  float x = init.x, y = init.y;
  if (m < 1 && m > -1) {
    while (x < final.x) {
      DrawPixel(round(x), round(y), WHITE);
      x += 1;
      y = (m * x + b);
    }
  } else {
    while (y < final.y) {
      DrawPixel(round(x), round(y), WHITE);
      y += 1;
      x = ((y - b) / m);
    }
  }
}

void simpleDDA(Vector2 init, Vector2 final) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  float m = (float)dy / dx;
  float b = (float)init.y - m * init.x;

  float x = init.x, y = init.y;
  if (m < 1 && m > -1) {
    while (x < final.x) {
      DrawPixel(round(x), round(y), WHITE);
      x += 1;
      y = (y + m);
    }
  } else {
    while (y < final.y) {
      DrawPixel(round(x), round(y), WHITE);
      y += 1;
      x = (x + 1 / m);
    }
  }
}

float max(float a, float b) {
  if (a > b) {
    return a;
  }
  return b;
}

void incDDA(Vector2 init, Vector2 final) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  float m = (float)dy / dx;
  float b = (float)init.y - m * init.x;

  float x = init.x, y = init.y;
  float step, xinc, yinc;
  step = max(dy, dx);
  xinc = dx / step;
  yinc = dy / step;
  while (x < final.x && y < final.y) {
    DrawPixel(round(x), round(y), WHITE);
    y = (y + yinc);
    x = (x + xinc);
  }
}

void bresenhamLDA(Vector2 init, Vector2 final) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  int p = 2 * dy - dx;
  float m = (float)dy / dx;

  int x = init.x, y = init.y;
  if (m < 1 && m > -1) {
    while (x < final.x) {
      DrawPixel(x, y, WHITE);
      if (p < 0) {
        x += 1;
        p += 2 * dy;
      } else {
        x += 1;
        y += 1;
        p += 2 * dy - 2 * dx;
      }
    }
  } else {
    while (y < final.y) {
      DrawPixel(x, y, WHITE);
      if (p < 0) {
        y += 1;
        p += 2 * dx;
      } else {
        x += 1;
        y += 1;
        p += 2 * dx - 2 * dy;
      }
    }
  }
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
        .x = 1,
        .y = 1,
    };
    Vector2 final_point = {
        .x = 50,
        .y = 300,
    };
    simpleLDA(initial_point, final_point);
    DrawPixelV(initial_point, YELLOW);
    DrawPixelV(final_point, YELLOW);
    DrawText("simpleLDA", (final_point.x - 75), final_point.y, 12, WHITE);

    initial_point.x += 100;
    final_point.x += 100;
    simpleDDA(initial_point, final_point);
    DrawPixelV(initial_point, YELLOW);
    DrawPixelV(final_point, YELLOW);
    DrawText("simpleDDA", (final_point.x - 75), final_point.y, 12, WHITE);

    initial_point.x += 100;
    final_point.x += 100;
    incDDA(initial_point, final_point);
    DrawPixelV(initial_point, YELLOW);
    DrawPixelV(final_point, YELLOW);
    DrawText("incDDA", (final_point.x - 75), final_point.y, 12, WHITE);

    initial_point.x += 100;
    final_point.x += 100;
    bresenhamLDA(initial_point, final_point);
    DrawPixelV(initial_point, YELLOW);
    DrawPixelV(final_point, YELLOW);
    DrawText("bresenhamLDA", (final_point.x - 75), final_point.y, 12, WHITE);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
