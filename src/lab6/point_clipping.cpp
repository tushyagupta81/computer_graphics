#include "apps.h"
#include "raylib.h"

void draw_point(Vector2 p, int wxman, int wxmin, int wymax, int wymin) {
  if (p.y > wymax || p.y < wymin || p.x > wxman || p.x < wxmin) {
    DrawCircleV(p, 2, RED);
    DrawText("Rejected", p.x+5, p.y-20, 16, BLACK);
    return;
  }
  DrawCircleV(p, 2, BLACK);
}

int point_clipping() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "point_clipping");

  Vector2 point1 = {.x = 105, .y = 105};
  Vector2 point2 = {.x = 50, .y = 50};
  int wxmax = 200, wxmin = 100, wymax = 200, wymin = 100;

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(WHITE);

    DrawLine(wxmin, 50, wxmin, 250, BLACK);
    DrawLine(wxmax, 50, wxmax, 250, BLACK);
    DrawLine(50, wymin, 250, wymin, BLACK);
    DrawLine(50, wymax, 250, wymax, BLACK);
    draw_point(point1, wxmax, wxmin, wymax, wymin);
    draw_point(point2, wxmax, wxmin, wymax, wymin);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
