#include "raylib.h"
#include "apps.h"

int bar_graph() {
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

    DrawLine(50, 400, 50, 150, WHITE);
    DrawLine(50, 400, 300, 400, WHITE);
    DrawRectangle(100, 325, 50, 75, WHITE);
    DrawText("(75, 1)", 100, 310, 12, WHITE);
    DrawText("y = 1", 110, 400, 12, WHITE);
    DrawRectangle(150, 300, 50, 100, GREEN);
    DrawText("(100, 2)", 150, 285, 12, WHITE);
    DrawText("y = 2", 160, 400, 12, WHITE);
    DrawRectangle(200, 275, 50, 125, BLUE);
    DrawText("(125, 3)", 200, 260, 12, WHITE);
    DrawText("y = 3", 210, 400, 12, WHITE);
    DrawText("This is a bar chart", 75, 420, 20, WHITE);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
