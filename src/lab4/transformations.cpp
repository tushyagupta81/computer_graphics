#include "apps.h"
#include "raylib.h"
#include <cmath>
#include <vector>
using namespace std;

#define pi 3.14

vector<vector<float>> mul(vector<vector<float>> a, vector<vector<float>> b) {
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

vector<vector<float>> translate(float sx, float sy) {
  vector<vector<float>> mat = {{1, 0, 0}, {0, 1, 0}, {sx, sy, 1}};
  return mat;
}

vector<vector<float>> reflect(string wrt) {
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

vector<vector<float>> shear(float sx, float sy) {
  vector<vector<float>> mat = {{1, sy, 0}, {sx, 1, 0}, {0, 0, 1}};
  return mat;
}

vector<vector<float>> scale(float sx, float sy) {
  vector<vector<float>> mat = {{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}};
  return mat;
}

vector<vector<float>> rotatation(int angle) {
  float c = cos(angle * pi / 180);
  float s = sin(angle * pi / 180);
  vector<vector<float>> mat = {{c, s, 0}, {-s, c, 0}, {0, 0, 1}};
  return mat;
}

void drawRect(vector<vector<float>> &points, vector<float> p, vector<float> q) {
  for (float i = p[0]; i <= q[0]; i++) {
    points.push_back({i, p[1], 1});
    points.push_back({i, q[1], 1});
  }
  for (float i = p[1]; i <= q[1]; i++) {
    points.push_back({p[0], i, 1});
    points.push_back({q[0], i, 1});
  }
}

void drawPoints(vector<vector<float>> points) {
  for (auto p : points) {
    DrawPixel(p[0], p[1], WHITE);
  }
}

int transformations() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "transformations");

  vector<vector<float>> points;
  vector<float> start = {40, 40, 1};
  vector<float> end = {200, 160, 1};
  drawRect(points, start, end);

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    DrawText("Regular", 95, 25, 12, WHITE);
    drawPoints(points);
    DrawText("Shear-X", 295, 25, 12, WHITE);
    drawPoints(
      mul(
        points,
        mul(
          mul(
            translate(-((float)start[0]+end[0])/2, -((float)start[1]+end[1])/2),
            mul(
              shear(0.4, 0),
              translate(((float)start[0]+end[0])/2, ((float)start[1]+end[1])/2)
            )
          ),
          translate(200, 0)
        )
      )
    );
    DrawText("Shear-Y", 560, 25, 12, WHITE);
    drawPoints(
      mul(
        points,
        mul(
          mul(
            translate(-((float)start[0]+end[0])/2, -((float)start[1]+end[1])/2),
            mul(
              shear(0, 0.4),
              translate(((float)start[0]+end[0])/2, ((float)start[1]+end[1])/2)
            )
          ),
          translate(450, 0)
        )
      )
    );
    DrawText("Rotation", 120, 250, 12, WHITE);
    drawPoints(
      mul(
        points,
        mul(
          mul(
            translate(-((float)start[0]+end[0])/2, -((float)start[1]+end[1])/2),
            mul(
              rotatation(30),
              translate(((float)start[0]+end[0])/2, ((float)start[1]+end[1])/2)
            )
          ),
          translate(0, 250)
        )
      )
    );
    DrawText("Scaling", 745, 300, 12, WHITE);
    drawPoints(
      mul(
        points,
        mul(
          mul(
            translate(-((float)start[0]+end[0])/2, -((float)start[1]+end[1])/2),
            mul(
              scale(0.5, 0.5),
              translate(((float)start[0]+end[0])/2, ((float)start[1]+end[1])/2)
            )
          ),
          translate(650, 250)
        )
      )
    );
    DrawText("Reflect along X", 75, 525, 12, WHITE);
    drawPoints(
      mul(
        points,
        mul(
          translate(0, -700),
          reflect("x")
        )
      )
    );
    drawPoints(
      mul(
        points,
          translate(450, 250)
      )
    );
    DrawText("Reflect along X=Y", 500, 450, 16, WHITE);
    DrawLine(300, 300, 600, 600, WHITE);
    drawPoints(
      mul(
        points,
        mul(
          translate(450, 250),
          reflect("x=y")
        )
      )
    );

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
