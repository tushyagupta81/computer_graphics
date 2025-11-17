#include "apps.h"
#include "raylib.h"

void liang(Vector2 p, Vector2 q, Vector2 topleft, Vector2 bottomright) {
  float dx = q.x - p.x;
  float dy = q.y - p.y;

  float p_list[4] = {-dx, dx, -dy, dy};
  float q_list[4] = {
      p.x - topleft.x,     // left
      bottomright.x - p.x, // right
      p.y - bottomright.y, // bottom
      topleft.y - p.y      // top
  };

  float t_enter = 0.0f;
  float t_exit = 1.0f;

  for (int i = 0; i < 4; i++) {
    float p_i = p_list[i];
    float q_i = q_list[i];

    if (p_i == 0) {
      if (q_i < 0)
        return; // parallel outside → reject
      continue;
    }

    float t = q_i / p_i;

    if (p_i < 0) {
      if (t > t_enter)
        t_enter = t; // entering
    } else {
      if (t < t_exit)
        t_exit = t; // leaving
    }

    if (t_enter > t_exit)
      return; // trivial reject
  }

  Vector2 c1 = {
    p.x + t_enter * dx,
    p.y + t_enter * dy,
  };
  Vector2 c2 = {
    p.x + t_exit * dx,
    p.y + t_exit * dy,
  };

  DrawCircleV(c1 , 2, BLACK);
  DrawCircleV(c2 , 2, BLACK);
}

int liang_barsky() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "liang_barsky");

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(WHITE);

    Vector2 a = {.x = 100, .y = 000};
    Vector2 b = {.x = 100, .y = 400};
    DrawLineV(a, b, BLACK);
    a.x += 300;
    b.x += 300;
    DrawLineV(a, b, BLACK);
    Vector2 c = {.x = 0, .y = 100};
    Vector2 d = {.x = 500, .y = 100};
    DrawLineV(c, d, BLACK);
    c.y += 200;
    d.y += 200;
    DrawLineV(c, d, BLACK);

    Vector2 bottomright = {.x = 400, .y = 100};
    Vector2 topleft = {.x = 100, .y = 300};
    // DrawCircleV(topleft, 2, BLACK);
    // DrawCircleV(bottomright, 2, BLACK);

    Vector2 p = {.x = 45, .y = 200};
    Vector2 q = {.x = 500, .y = 55};
    DrawLineV(p, q, BLACK);
    liang(p, q, topleft, bottomright);

    p = {.x = 75, .y = 200};
    q = {.x = 225, .y = 200};
    DrawLineV(p, q, BLACK);
    liang(p, q, topleft, bottomright);

    p = {.x = 250, .y = 50};
    q = {.x = 250, .y = 200};
    DrawLineV(p, q, BLACK);
    liang(p, q, topleft, bottomright);

    p = {.x = 50, .y = 320};
    q = {.x = 200, .y = 320};
    DrawLineV(p, q, BLACK);
    liang(p, q, topleft, bottomright);

    p = {.x = 50, .y = 275};
    q = {.x = 500, .y = 275};
    DrawLineV(p, q, BLACK);
    liang(p, q, topleft, bottomright);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
