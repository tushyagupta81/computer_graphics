#include "apps.h"
#include "raylib.h"
#include <stdint.h>

void draw_all_sides(int x, int y, Vector2 m) {
  DrawPixelV((Vector2){.x = x + m.x, .y = y + m.y}, WHITE);
  DrawPixelV((Vector2){.x = y + m.x, .y = x + m.y}, WHITE);
  DrawPixelV((Vector2){.x = -x + m.x, .y = y + m.y}, WHITE);
  DrawPixelV((Vector2){.x = -y + m.x, .y = x + m.y}, WHITE);
  DrawPixelV((Vector2){.x = -x + m.x, .y = -y + m.y}, WHITE);
  DrawPixelV((Vector2){.x = -y + m.x, .y = -x + m.y}, WHITE);
  DrawPixelV((Vector2){.x = x + m.x, .y = -y + m.y}, WHITE);
  DrawPixelV((Vector2){.x = y + m.x, .y = -x + m.y}, WHITE);
}

void calc_circle(Vector2 midpoint, uint32_t r) {
  int x = 0, y = r;
  int di = 1 - r, di_1;
  draw_all_sides(x, y, midpoint);
  while (x < y) {
    if (di < 0) {
      di_1 = di + 2 * x + 3;
      x += 1;
    } else {
      di_1 = di + 2 * x - 2 * y + 5;
      x += 1;
      y -= 1;
    }
    di = di_1;
    draw_all_sides(x, y, midpoint);
  }
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
    ClearBackground(BLACK);

    calc_circle((Vector2){.x = 500, .y = 500}, 200);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
