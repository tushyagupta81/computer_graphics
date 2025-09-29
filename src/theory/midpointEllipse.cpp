#include "apps.h"
#include "raylib.h"
#include <stdint.h>
void draw_points(int x, int y, Vector2 m) {
  DrawPixelV((Vector2){.x = x + m.x, .y = y + m.y}, WHITE);
  DrawPixelV((Vector2){.x = -x + m.x, .y = y + m.y}, WHITE);
  DrawPixelV((Vector2){.x = -x + m.x, .y = -y + m.y}, WHITE);
  DrawPixelV((Vector2){.x = x + m.x, .y = -y + m.y}, WHITE);
}

void calc_ellipse(Vector2 origin, int rx, int ry) {
  int x = 0, y = ry;
  float p1i = ry * ry - rx * rx * ry + (float)rx * rx / 4;
  int dx = 2 * ry * ry * x;
  int dy = 2 * rx * rx * y;
  while (dx < dy) {
    draw_points(x, y, origin);
    if (p1i < 0) {
      x += 1;
      dx = 2 * ry * ry * x;
      p1i = p1i + dx + ry * ry;
    } else {
      x += 1;
      y -= 1;
      dx = 2 * ry * ry * x;
      dy = 2 * rx * rx * y;
      p1i = p1i + dx - dy + ry * ry;
    }
  }
  float p2i;
  p2i = ry * ry * ((float)x + (float)1 / 2) * ((float)x + (float)1 / 2) +
        rx * rx * (y - 1) * (y - 1) - rx * rx * ry * ry;
  while (dx >= dy && y >= 0) {
    draw_points(x, y, origin);
    if (p2i > 0) {
      y -= 1;
      dy = 2 * rx * rx * y;
      p2i = p2i - dy + rx * rx;
    } else {
      x += 1;
      y -= 1;
      dy = 2 * rx * rx * y;
      dx = 2 * ry * ry * x;
      p2i = p2i + dx - dy + rx * rx;
    }
  }
}

int midpointEllipse() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "midpointEllipse");

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);
    calc_ellipse((Vector2){.x = 500, .y = 200}, 100, 50);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
