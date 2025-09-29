#include "apps.h"
#include "raylib.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>

void drawLine(Vector2 init, Vector2 final) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  float m = (float)dy / dx;
  float b = (float)init.y - m * init.x;

  float x = init.x, y = init.y;
  float step, xinc, yinc;
  step = fmax(abs(dy), abs(dx));
  xinc = dx / step;
  yinc = dy / step;
  while (x <= final.x && y <= final.y) {
    DrawPixel(round(x), round(y), WHITE);
    y = (y + yinc);
    x = (x + xinc);
  }
  DrawPixelV(init, YELLOW);
  DrawPixelV(final, YELLOW);
}

void drawRect(Vector2 start, Vector2 end) {
  drawLine(start, (Vector2){end.x, start.y});
  drawLine(start, (Vector2){start.x, end.y});
  drawLine((Vector2){end.x, start.y}, end);
  drawLine((Vector2){start.x, end.y}, end);
}

int rect() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "rect");

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    drawRect((Vector2){10, 10}, (Vector2){200, 200});

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
