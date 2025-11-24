#include "apps.h"
#include "raylib.h"

static void plot_octet(Image *img, Vector2 p, Vector2 mid) {
  ImageDrawPixel(img, p.x + mid.x, p.y + mid.y, BLACK);
  ImageDrawPixel(img, -p.x + mid.x, p.y + mid.y, BLACK);
  ImageDrawPixel(img, p.x + mid.x, -p.y + mid.y, BLACK);
  ImageDrawPixel(img, -p.x + mid.x, -p.y + mid.y, BLACK);
  ImageDrawPixel(img, p.y + mid.x, p.x + mid.y, BLACK);
  ImageDrawPixel(img, -p.y + mid.x, p.x + mid.y, BLACK);
  ImageDrawPixel(img, p.y + mid.x, -p.x + mid.y, BLACK);
  ImageDrawPixel(img, -p.y + mid.x, -p.x + mid.y, BLACK);
}

static void midpoint_circle(Image *img, Vector2 center, int radius) {
  int x = 0, y = radius;
  int p = 1 - radius;
  while (x < y) {
    plot_octet(img, (Vector2){.x = (float)x, .y = (float)y}, center);
    if (p < 0) {
      p = p + 2 * x + 3;
      x += 1;
    } else {
      p = p + 2 * x - 2 * y + 5;
      x += 1;
      y -= 1;
    }
  }
}

static bool operator==(Color a, Color b) {
  return a.a == b.a && a.r == b.r && a.g == b.g && a.b == b.b;
}

static void flood_fill(Image *img, int x, int y, Color old_color,
                       Color new_color) {
  Color c = GetImageColor(*img, x, y);
  if (c == old_color) {
    ImageDrawPixel(img, x, y, new_color);
    flood_fill(img, x + 1, y, old_color, new_color);
    flood_fill(img, x, y + 1, old_color, new_color);
    flood_fill(img, x - 1, y, old_color, new_color);
    flood_fill(img, x, y - 1, old_color, new_color);
  }
}

int final() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "final");

  Image img = GenImageColor(1280, 800, WHITE);
  ImageDrawRectangleLines(&img,
                          (Rectangle){
                              .x = 200,
                              .y = 200,
                              .width = 150,
                              .height = 150,
                          },
                          1, BLACK);

  flood_fill(&img, 300, 300, WHITE, BLACK);
  Vector2 center = {
      .x = 150,
      .y = 150,
  };
  midpoint_circle(&img, center, 50);

  Texture tex = LoadTextureFromImage(img);
  UnloadImage(img);

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(WHITE);
    DrawTexture(tex, 0, 0, WHITE);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
