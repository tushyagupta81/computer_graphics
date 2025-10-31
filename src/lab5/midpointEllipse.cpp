#include "apps.h"
#include "raylib.h"
#include <cstdio>
void draw_points(int x, int y, Vector2 m) {
  DrawPixelV((Vector2){.x = x + m.x, .y = y + m.y}, BLACK);
  DrawPixelV((Vector2){.x = -x + m.x, .y = y + m.y}, BLACK);
  DrawPixelV((Vector2){.x = -x + m.x, .y = -y + m.y}, BLACK);
  DrawPixelV((Vector2){.x = x + m.x, .y = -y + m.y}, BLACK);
}

bool print = true;

void calc_ellipse(Vector2 origin, int rx, int ry) {
  int x = 0, y = ry;
  float p1i = ry * ry - rx * rx * ry + (float)rx * rx / 4;
  int dx = 2 * ry * ry * x;
  int dy = 2 * rx * rx * y;
  while (dx < dy) {
    if (print) {
      printf("x = %d, y = %d\n", x, y);
    }
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
    if (print) {
      printf("x = %d, y = %d\n", x, y);
    }
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
  print = false;
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
    ClearBackground(WHITE);
    calc_ellipse((Vector2){.x = 500, .y = 200}, 200, 120);
    DrawLine(500, 200, 300, 200, BLACK);
    DrawLine(500, 200, 500, 80, BLACK);
    DrawText("(500, 200)", 480, 210, 12, BLACK);
    DrawText("ry=120", 505, 150, 12, BLACK);
    DrawText("rx=200", 380, 205, 12, BLACK);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
