#include "raylib.h"
#include "apps.h"

int concentric_circles() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "Hello Raylib");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);


    DrawCircle(400, 400, 200, GREEN);
    DrawCircle(400, 400, 150, BLUE);
    DrawCircle(400, 400, 100, RED);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
