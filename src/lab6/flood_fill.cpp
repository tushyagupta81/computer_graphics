#include "apps.h"
#include "raylib.h"

static bool operator==(Color a, Color b) {
  return (a.a == b.a && a.b == b.b && a.r == b.r && a.g == b.g);
}
static bool operator!=(Color a, Color b) {
  return !(a.a == b.a && a.b == b.b && a.r == b.r && a.g == b.g);
}

static void fill_4(Image *img, Vector2 seed, Color fill_color, Color old_color) {
  Color c = GetImageColor(*img, seed.x, seed.y);
  if (c == old_color) {
    ImageDrawPixel(img, seed.x, seed.y, fill_color);
    fill_4(img, (Vector2){.x = seed.x + 1, .y = seed.y}, fill_color, old_color);
    fill_4(img, (Vector2){.x = seed.x, .y = seed.y + 1}, fill_color, old_color);
    fill_4(img, (Vector2){.x = seed.x - 1, .y = seed.y}, fill_color, old_color);
    fill_4(img, (Vector2){.x = seed.x, .y = seed.y - 1}, fill_color, old_color);
  }
}

static void fill_8(Image *img, Vector2 seed, Color fill_color, Color old_color) {
  // printf("%d %d %d\n", color.r, color.g, color.b);
  Color c = GetImageColor(*img, seed.x, seed.y);
  if (c == old_color) {
    ImageDrawPixel(img, seed.x, seed.y, fill_color);
    fill_8(img, (Vector2){.x = seed.x + 1, .y = seed.y}, fill_color, old_color);
    fill_8(img, (Vector2){.x = seed.x, .y = seed.y + 1}, fill_color, old_color);
    fill_8(img, (Vector2){.x = seed.x - 1, .y = seed.y}, fill_color, old_color);
    fill_8(img, (Vector2){.x = seed.x, .y = seed.y - 1}, fill_color, old_color);
    fill_8(img, (Vector2){.x = seed.x + 1, .y = seed.y + 1}, fill_color,
           old_color);
    fill_8(img, (Vector2){.x = seed.x - 1, .y = seed.y + 1}, fill_color,
           old_color);
    fill_8(img, (Vector2){.x = seed.x - 1, .y = seed.y - 1}, fill_color,
           old_color);
    fill_8(img, (Vector2){.x = seed.x + 1, .y = seed.y - 1}, fill_color,
           old_color);
  }
}

int flood_fill() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "flood_fill");

  Color FILL_COLOR = BLACK, OLD_COLOR = WHITE;

  Image img = GenImageColor(1280, 800, WHITE);
  ImageDrawRectangleLines(
      &img, Rectangle{.x = 20, .y = 170, .width = 100, .height = 100}, 2, BLACK);
  ImageDrawCircleLines(&img, 70, 70, 50, BLACK);

  fill_4(&img, Vector2{.x = 50, .y = 50}, FILL_COLOR, OLD_COLOR);
  fill_4(&img, Vector2{.x = 50, .y = 250}, FILL_COLOR, OLD_COLOR);
  ImageDrawText(&img, "4 Fill", 50, 125, 16, BLACK);

  ImageDrawRectangleLines(
      &img, Rectangle{.x = 200, .y = 20, .width = 100, .height = 100}, 2,
      BLACK);
  ImageDrawText(&img, "8 Fill", 225, 125, 16, BLACK);

  fill_8(&img, Vector2{.x = 250, .y = 50}, FILL_COLOR, OLD_COLOR);

  Texture2D tex = LoadTextureFromImage(img);
  UnloadImage(img);

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    DrawTexture(tex, 0, 0, WHITE);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
