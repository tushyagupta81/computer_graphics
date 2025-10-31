#include "apps.h"
#include "raylib.h"
#include <cmath>
#include <vector>
using namespace std;

#define pi 3.14

static vector<vector<float>> mul(vector<vector<float>> a, vector<vector<float>> b) {
  vector<vector<float>> points(a.size(), vector<float>(3, 0));
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b[0].size(); j++) {
      points[i][j] = 0;
      for (int k = 0; k < b.size(); k++) {
        points[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return points;
}

static vector<vector<float>> translate(float sx, float sy) {
  vector<vector<float>> mat = {{1, 0, 0}, {0, 1, 0}, {sx, sy, 1}};
  return mat;
}

static vector<vector<float>> reflect(string wrt) {
  vector<vector<float>> mat = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  if (wrt == "x") {
    mat = {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
  } else if (wrt == "y") {
    mat = {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  } else if (wrt == "xy") {
    mat = {{-1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
  } else if (wrt == "x=y") {
    mat = {{0, 1, 0}, {1, 0, 0}, {0, 0, 1}};
  }
  return mat;
}

static vector<vector<float>> shear(float sx, float sy) {
  vector<vector<float>> mat = {{1, sy, 0}, {sx, 1, 0}, {0, 0, 1}};
  return mat;
}

static vector<vector<float>> scale(float sx, float sy) {
  vector<vector<float>> mat = {{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}};
  return mat;
}

static vector<vector<float>> rotatation(int angle) {
  float c = cos(angle * pi / 180);
  float s = sin(angle * pi / 180);
  vector<vector<float>> mat = {{c, s, 0}, {-s, c, 0}, {0, 0, 1}};
  return mat;
}

static void bresenhamLDA(vector<vector<float>> &points, Vector2 init, Vector2 final) {
  int dy = final.y - init.y;
  int dx = final.x - init.x;
  int sx = dx < 0 ? -1 : 1;
  int sy = dy < 0 ? -1 : 1;
  float m = (float)dy / dx;
  dx = abs(dx);
  dy = abs(dy);
  int p;
  if (dx >= dy) {
    p = 2 * dy - dx;
  } else {
    p = 2 * dx - dy;
  }

  float x = init.x, y = init.y;
  if (m < 1 && m > -1) {
    for (int i = 0; i <= dx; i++) {
      points.push_back({x, y, 1});
      if (p < 0) {
        x += sx;
        p += 2 * dy;
      } else {
        x += sx;
        y += sy;
        p += 2 * dy - 2 * dx;
      }
    }
  } else {
    for (int i = 0; i <= dy; i++) {
      points.push_back({x, y, 1});
      if (p < 0) {
        y += sy;
        p += 2 * dx;
      } else {
        x += sx;
        y += sy;
        p += 2 * dx - 2 * dy;
      }
    }
  }
}

static void drawTri(vector<vector<float>> &points) {
  bresenhamLDA(points, (Vector2){.x = 20, .y = 200},
               (Vector2){.x = 120, .y = 200});
  bresenhamLDA(points, (Vector2){.x = 120, .y = 200},
               (Vector2){.x = 70, .y = 50});
  bresenhamLDA(points, (Vector2){.x = 70, .y = 50},
               (Vector2){.x = 20, .y = 200});
}

static void drawPoints(vector<vector<float>> points) {
  for (auto p : points) {
    DrawPixel(p[0], p[1], BLACK);
  }
}

int compo_transformations() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "transformations");

  vector<vector<float>> points;
  drawTri(points);

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(WHITE);

    DrawText("Regular", 50, 40, 12, BLACK);
    drawPoints(points);
    DrawText("Rotation", 180, 50, 12, BLACK);
    drawPoints(
      mul(
        points,
        mul(
          translate(-70, -50),
          mul(
            rotatation(45),
            translate(270, 50)
          )
        )
      )
    );
    DrawText("Shearing", 300, 40, 12, BLACK);
    drawPoints(
      mul(
        points,
        mul(
          translate(-70, -50),
          mul(
            shear(0.3, 0),
            translate(300, 50)
          )
        )
      )
    );
    DrawText("Reflection", 40, 205, 12, BLACK);
    drawPoints(
      mul(
        points,
        mul(
          translate(0, -300),
          mul(
            reflect("x"),
            translate(0, 120)
          )
        )
      )
    );
    DrawText("Scaling", 180, 210, 12, BLACK);
    drawPoints(
      mul(
        points,
        mul(
          translate(-70, -50),
          mul(
            scale(0.5, 0.5),
            translate(200, 230)
          )
        )
      )
    );

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
