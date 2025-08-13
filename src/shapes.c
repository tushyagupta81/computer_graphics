#include "raylib.h"
#include "apps.h"

int shapes() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "Hello world");

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    DrawLine(10, 10, 200, 200, WHITE);
    DrawCircle(400, 400, 50, WHITE);
    DrawCircleLines(600, 600, 50, WHITE);
    Vector2 center = {
        .x = 400,
        .y = 200,
    };
    DrawCircleSector(center, 50, 45, 315, 0, WHITE);
    DrawEllipse(600, 200, 20, 30, GREEN);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
