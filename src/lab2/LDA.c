#include "apps.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

bool print = true;

void incDDA(Vector2 init, Vector2 final, Color color) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  float m = (float)dy / dx;
  float b = (float)init.y - m * init.x;

  float x = init.x, y = init.y;
  float step, xinc, yinc;
  step = fmax(abs(dy), abs(dx));
  xinc = dx / step;
  yinc = dy / step;
  if (print) {
    printf("xinc=%f yinc=%f\n", xinc, yinc);
    printf("dx=%d dy=%d\n", dx, dy);
    printf("init.x=%f init.y=%f\n", init.x, init.y);
    printf("final.x=%f final.y=%f\n", final.x, final.y);
  }
  for (int i = 0; i <= step; i++) {
    if (print) {
      printf("x = %f, y = %f\n", x, y);
    }
    DrawPixel(round(x), round(y), color);
    y += yinc;
    x += xinc;
  }
  print = false;
}

void bresenhamLDA(Vector2 init, Vector2 final, Color color) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  int sx = dx < 0 ? -1 : 1;
  int sy = dy < 0 ? -1 : 1;
  float m = (float)dy / dx;
  dx = abs(dx);
  dy = abs(dy);
  int p;
  if (dx >= dy) {
    p = 2 * dy - dx;
  } else {
    p = 2 * dx - dy;
  }

  if (print) {
    printf("m=%f\n", m);
    printf("dx=%d dy=%d\n", dx, dy);
    printf("init.x=%f init.y=%f\n", init.x, init.y);
    printf("final.x=%f final.y=%f\n", final.x, final.y);
  }
  int x = init.x, y = init.y;
  if (m < 1 && m > -1) {
    for (int i = 0; i <= dx; i++) {
      if (print) {
        printf("x = %d, y = %d\n", x, y);
      }
      DrawPixel(x, y, color);
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
    for (int i = 0; i <= dy; i++) {
      if (print) {
        printf("x = %d, y = %d\n", x, y);
      }
      DrawPixel(x, y, color);
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
  print = false;
}

void draw(Vector2 initial_point, Vector2 final_point, Color color) {
  // incDDA(initial_point, final_point, color);
  bresenhamLDA(initial_point, final_point, color);

  DrawCircleV(final_point, 2, color);
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
    ClearBackground(WHITE);

    Vector2 initial_point = {
        .x = 20,
        .y = 20,
    };
    Vector2 final_point = {
        .x = 220,
        .y = 220,
    };
    draw(initial_point, final_point, BLACK);

    initial_point.x = 220;
    initial_point.y = 20;
    final_point.x = 20;
    final_point.y = 220;
    draw(initial_point, final_point, RED);

    initial_point.x = 500;
    initial_point.y = 10;
    final_point.x = 300;
    final_point.y = 10;
    draw(initial_point, final_point, BLUE);

    initial_point.x = 500;
    initial_point.y = 10;
    final_point.x = 500;
    final_point.y = 210;
    draw(initial_point, final_point, BLUE);

    initial_point.x = 450;
    initial_point.y = 450;
    final_point.x = 250;
    final_point.y = 250;
    draw(initial_point, final_point, BLACK);

    initial_point.x = 450;
    initial_point.y = 250;
    final_point.x = 250;
    final_point.y = 450;
    draw(initial_point, final_point, RED);

    // DrawText("Bresenham", 20, 400, 16, BLACK);
    DrawText("DDA", 20, 400, 16, BLACK);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
