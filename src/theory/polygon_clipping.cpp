#include <cstdio>
#include <raylib.h>
#include "apps.h"
#include <vector>
using namespace std;

int xmin = 200, ymin = 150, xmax = 500, ymax = 400;

struct Point {
  float x, y;
};

bool inside(Point p, int edge) {
  switch (edge) {
  case 0:
    return p.x >= xmin; // Left
  case 1:
    return p.x <= xmax; // Right
  case 2:
    return p.y >= ymin; // Bottom
  case 3:
    return p.y <= ymax; // Top
  }
  return false;
}

Point intersection(Point p1, Point p2, int edge) {
  Point i;
  float m = (p2.x - p1.x) ? (p2.y - p1.y) / (p2.x - p1.x) : 1e9;
  switch (edge) {
  case 0: // Left
    i.x = xmin;
    i.y = p1.y + (xmin - p1.x) * m;
    break;
  case 1: // Right
    i.x = xmax;
    i.y = p1.y + (xmax - p1.x) * m;
    break;
  case 2: // Bottom
    i.y = ymin;
    i.x = p1.x + (ymin - p1.y) / m;
    break;
  case 3: // Top
    i.y = ymax;
    i.x = p1.x + (ymax - p1.y) / m;
    break;
  }
  return i;
}

vector<Point> clipPolygon(vector<Point> poly, int edge) {
  vector<Point> newPoly;
  for (int i = 0; i < poly.size(); i++) {
    Point curr = poly[i];
    Point prev = poly[(i + poly.size() - 1) % poly.size()];
    bool currInside = inside(curr, edge);
    bool prevInside = inside(prev, edge);
    if (prevInside && currInside) {
      newPoly.push_back(curr);
    } else if (prevInside && !currInside) {
      newPoly.push_back(intersection(prev, curr, edge));
    } else if (!prevInside && currInside) {
      newPoly.push_back(intersection(prev, curr, edge));
      newPoly.push_back(curr);
    }
  }
  return newPoly;
}

int polygon_clipping() {
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(1280, 800, "polygon_clipping");
  vector<Point> poly = {
      {150, 200}, {300, 100}, {550, 180}, {520, 420}, {220, 450}};

  // game loop
  while (!WindowShouldClose()) {
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(WHITE);

    DrawLine(xmin, ymin, xmax, ymin, BLACK); // Bottom
    DrawLine(xmin, ymax, xmax, ymax, BLACK); // Top
    DrawLine(xmin, ymin, xmin, ymax, BLACK); // Left
    DrawLine(xmax, ymin, xmax, ymax, BLACK); // Right
                                             //
    char text[50];
    sprintf(text, "(%d, %d)", xmin, ymin);
    DrawText(text, xmin - 90, ymin + 10, 16, BLACK);
    sprintf(text, "(%d, %d)", xmax, ymin);
    DrawText(text, xmax + 10, ymin + 10, 16, BLACK);
    sprintf(text, "(%d, %d)", xmin, ymax);
    DrawText(text, xmin - 90, ymax - 20, 16, BLACK);
    sprintf(text, "(%d, %d)", xmax, ymax);
    DrawText(text, xmax + 10, ymax - 20, 16, BLACK);
    for (int i = 0; i < poly.size(); i++) {
      int next = (i + 1) % poly.size();
      DrawLine(poly[i].x, poly[i].y, poly[next].x, poly[next].y, BLACK);
      DrawCircle(poly[i].x, poly[i].y, 3, BLACK);
    }
    DrawText("RED = Original Polygon", 150, 480, 16, BLACK);
    vector<Point> clipped = poly;
    for (int edge = 0; edge < 4; edge++)
      clipped = clipPolygon(clipped, edge);

    for (int i = 0; i < clipped.size(); i++) {
      int next = (i + 1) % clipped.size();
      DrawLine(clipped[i].x, clipped[i].y, clipped[next].x, clipped[next].y,
               BLACK);
      DrawCircle(clipped[i].x, clipped[i].y, 3, BLACK);
      char lbl[40];
      sprintf(lbl, "(%d, %d)", (int)clipped[i].x, (int)clipped[i].y);
      DrawText(lbl, clipped[i].x + 10, clipped[i].y - 35, 16, BLACK);
    }
    DrawText("GREEN = Clipped Polygon", 150, 500, 16, BLACK);

    EndDrawing();
  }

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
