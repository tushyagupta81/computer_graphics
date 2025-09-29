#include "apps.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

bool print_lda = true;

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
  if (print_lda) {
    printf("xinc=%f yinc=%f\n", xinc, yinc);
    printf("dx=%d dy=%d\n", dx, dy);
    printf("init.x=%f init.y=%f\n", init.x, init.y);
    printf("final.x=%f final.y=%f\n", final.x, final.y);
  }
  for (int i = 0; i <= step; i++) {
    if (print_lda) {
      printf("k = %d, x = %f, y = %f\n", i, x, y);
    }
    DrawPixel(round(x), round(y), color);
    y += yinc;
    x += xinc;
  }
  // print = false;
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

  if (print_lda) {
    printf("m=%f\n", m);
    printf("dx=%d dy=%d\n", dx, dy);
    printf("p0=%d\n", p);
    printf("init.x=%f init.y=%f\n", init.x, init.y);
    printf("final.x=%f final.y=%f\n", final.x, final.y);
  }
  int x = init.x, y = init.y;
  if (m < 1 && m > -1) {
    for (int i = 0; i <= dx; i++) {
      if (print_lda) {
        printf("k = %d, x = %d, y = %d, p = %d\n", i, x, y, p);
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
      if (print_lda) {
        printf("k = %d, x = %d, y = %d, p = %d\n", i, x, y, p);
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
  // print = false;
}

void draw(Vector2 initial_point, Vector2 final_point, Color color) {
  incDDA(initial_point, final_point, color);
  // bresenhamLDA(initial_point, final_point, color);

  DrawCircleV(final_point, 2, color);
  DrawText(TextFormat("m = %.2f", (final_point.y - initial_point.y) /
                                      (final_point.x - initial_point.x)),
           (final_point.x + initial_point.x) / 2,
           (final_point.y + initial_point.y) / 2, 16, color);
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
        .y = 180,
    };
    if (print_lda) {
      printf("=== Line 1 ===\n");
    }
    draw(initial_point, final_point, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", initial_point.x, initial_point.y),
             initial_point.x+10, initial_point.y, 16, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", final_point.x, final_point.y),
             final_point.x+10, final_point.y, 16, BLACK);

    initial_point.x = 520;
    initial_point.y = 20;
    final_point.x = 320;
    final_point.y = 180;
    if (print_lda) {
      printf("=== Line 2 ===\n");
    }
    draw(initial_point, final_point, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", initial_point.x, initial_point.y),
             initial_point.x+10, initial_point.y, 16, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", final_point.x, final_point.y),
             final_point.x+10, final_point.y, 16, BLACK);

    initial_point.x = 850;
    initial_point.y = 10;
    final_point.x = 650;
    final_point.y = 10;
    if (print_lda) {
      printf("=== Line 3 ===\n");
    }
    draw(initial_point, final_point, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", initial_point.x, initial_point.y),
             initial_point.x-20, initial_point.y+10, 16, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", final_point.x, final_point.y),
             final_point.x-20, final_point.y+10, 16, BLACK);

    initial_point.x = 900;
    initial_point.y = 10;
    final_point.x = 900;
    final_point.y = 210;
    if (print_lda) {
      printf("=== Line 4 ===\n");
    }
    draw(initial_point, final_point, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", initial_point.x, initial_point.y),
             initial_point.x+10, initial_point.y, 16, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", final_point.x, final_point.y),
             final_point.x+10, final_point.y, 16, BLACK);

    initial_point.x = 450;
    initial_point.y = 450;
    final_point.x = 250;
    final_point.y = 290;
    if (print_lda) {
      printf("=== Line 5 ===\n");
    }
    draw(initial_point, final_point, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", initial_point.x, initial_point.y),
             initial_point.x+10, initial_point.y, 16, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", final_point.x, final_point.y),
             final_point.x+10, final_point.y, 16, BLACK);

    initial_point.x = 550;
    initial_point.y = 450;
    final_point.x = 750;
    final_point.y = 290;
    if (print_lda) {
      printf("=== Line 6 ===\n");
    }
    draw(initial_point, final_point, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", initial_point.x, initial_point.y),
             initial_point.x+10, initial_point.y, 16, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", final_point.x, final_point.y),
             final_point.x+10, final_point.y, 16, BLACK);

    // DrawText("Bresenham", 20, 400, 16, BLACK);
    DrawText("DDA", 20, 400, 16, BLACK);
    print_lda = false;

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
