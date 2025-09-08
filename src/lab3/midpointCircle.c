#include "apps.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void draw_all_sides(int x, int y, Vector2 m) {
  DrawPixelV((Vector2){.x = x + m.x, .y = y + m.y}, BLACK);
  DrawPixelV((Vector2){.x = y + m.x, .y = x + m.y}, BLACK);
  DrawPixelV((Vector2){.x = -x + m.x, .y = y + m.y}, BLACK);
  DrawPixelV((Vector2){.x = -y + m.x, .y = x + m.y}, BLACK);
  DrawPixelV((Vector2){.x = -x + m.x, .y = -y + m.y}, BLACK);
  DrawPixelV((Vector2){.x = -y + m.x, .y = -x + m.y}, BLACK);
  DrawPixelV((Vector2){.x = x + m.x, .y = -y + m.y}, BLACK);
  DrawPixelV((Vector2){.x = y + m.x, .y = -x + m.y}, BLACK);
}

bool print_midpoint_circle = true;

void calc_circle(Vector2 midpoint, uint32_t r) {
  int x = 0, y = r;
  int d = 1 - r;
  draw_all_sides(x, y, midpoint);
  if (print_midpoint_circle) {
    printf("radius = %d\n", r);
    printf("center = (%.0f, %.0f)\n", midpoint.x, midpoint.y);
    printf("d = %d\n", d);
  }
  while (x < y) {
    if (print_midpoint_circle) {
      printf("x = %d, y = %d, d = %d\n", x, y, d);
    }
    if (d < 0) {
      d = d + 2 * x + 3;
      x += 1;
    } else {
      d = d + 2 * x - 2 * y + 5;
      x += 1;
      y -= 1;
    }
    draw_all_sides(x, y, midpoint);
  }
  print_midpoint_circle = false;
}

int midpointCircle() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "midpointCircle");

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(WHITE);

    Vector2 center = {.x = 250, .y = 250};
    int radius = 20;
    calc_circle(center, radius);
    DrawLineV(center, (Vector2){.x = center.x, .y = center.y + radius}, BLACK);
    DrawCircleV(center, 2, BLACK);
    DrawText(TextFormat("radius = %i", radius), center.x + 5,
             center.y + ((float)radius / 2), 16, BLACK);
    DrawText(TextFormat("(%.0f, %.0f)", center.x, center.y), center.x + 10,
             center.y, 16, BLACK);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
