#include <cmath>
#include <iostream>
#include <raylib.h>
#include <rlgl.h>

const int windowWidth = 2000;
const int windowHeight = 1125;
const int textureSizeMultiplier = 3;

const double pi = 3.1415926535897932384626433832795028841971693993751;
const Vector2 startTexturePos = {
    -windowWidth * (textureSizeMultiplier - 1) / 2.0,
    -windowHeight *(textureSizeMultiplier - 1) / 2.0};
const char *imgToLoad = "./imgs/blank.png";
const Color backgroundColor = {0, 0, 0, 255};
int circleSegments = 10;
Color drawColor = {255, 255, 255, 255};
int radius = 1;
bool wasRMBDown = false;
bool eraserMode = false;
bool shiftMode = false;
Vector2 texturePos = startTexturePos;
Vector2 mousePos;
Vector2 mousePos_old;
void betweenFrameDraw(Vector2 mp_old, Vector2 mp);
void drawCircleOptimised(Vector2 center, float radius, Color color,
                         RenderTexture2D target);

int main(void) {

  InitWindow(windowWidth, windowHeight, "infinite blackboard");
  RenderTexture2D target =
      LoadRenderTexture(windowWidth * textureSizeMultiplier,
                        windowHeight * textureSizeMultiplier);
  BeginTextureMode(target);
  ClearBackground(BLACK);
  EndTextureMode();
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    mousePos_old = mousePos;
    mousePos = GetMousePosition();
    radius += GetMouseWheelMove();
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      shiftMode = true;
    } else {
      shiftMode = false;
    }
    if (IsKeyDown(KEY_E)) {
      eraserMode = true;
    } else {
      eraserMode = false;
    }
    if (radius < 1)
      radius = 1;
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {

      if (wasRMBDown) {
        texturePos.x += mousePos.x - mousePos_old.x;
        texturePos.y += mousePos.y - mousePos_old.y;
      }

      wasRMBDown = true;
    } else {
      wasRMBDown = false;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

      BeginTextureMode(target);
      if (eraserMode) {
        drawColor = backgroundColor;
      } else {
        drawColor = {255, 255, 255, 255};
      }
      betweenFrameDraw(mousePos_old, mousePos);
      DrawCircle(mousePos.x - texturePos.x, mousePos.y - texturePos.y, radius,
                 drawColor);
      EndTextureMode();
    }
    if (IsKeyDown(KEY_UP)) {
      texturePos.y++;
    }
    if (IsKeyDown(KEY_DOWN)) {
      texturePos.y--;
    }
    if (IsKeyDown(KEY_LEFT)) {
      texturePos.x++;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      texturePos.x--;
    }

    if (IsKeyDown(KEY_C) && shiftMode) {
      BeginTextureMode(target);
      ClearBackground(BLACK);
      EndTextureMode();
    }
    BeginDrawing();
    ClearBackground(GRAY);

    DrawTextureRec(target.texture,
                   (Rectangle){0, 0, (float)target.texture.width,
                               (float)-target.texture.height},
                   (Vector2){texturePos.x, texturePos.y}, RAYWHITE);

    // DrawTexture(target.texture, 0, 0, WHITE);

    EndDrawing();
    // std::cout << GetFPS() << "\n";
  }
  UnloadRenderTexture(target);
  CloseWindow();
  return 0;
}

void betweenFrameDraw(Vector2 mp_old, Vector2 mp) {
  Vector2 mp_delta = {mp.x - mp_old.x, mp.y - mp_old.y};
  float mp_delta_mag = sqrt(pow(mp_delta.x, 2) + pow(mp_delta.y, 2));
  // draw line between those 2 points
  int line_length_in_circles = ceil(mp_delta_mag / radius);
  Vector2 step = {mp_delta.x / line_length_in_circles,
                  mp_delta.y / line_length_in_circles};
  for (int i = 0; i < line_length_in_circles; i++) {
    DrawCircle(mp_old.x + i * step.x - texturePos.x,
               mp_old.y + i * step.y - texturePos.y, radius, drawColor);
  }
};

void drawCircleOptimised(Vector2 center, float radius, Color color,
                         RenderTexture2D target) {
  int segments = circleSegments;
  double step = 2 * pi / segments; // step in rads
  double angle = 0;                // rads

  Vector2 vertex2 = {0, 0};
  Vector2 vertex2old = {0, 0};

  vertex2 = {cosf(angle + step) * (float)radius,
             sinf(angle + step) * (float)radius};
  vertex2old = {0, (float)radius};
  rlBegin(RL_TRIANGLES);
  rlSetTexture(target.texture.id);
  for (int i = 0; i < segments; i++) {
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlVertex2f(center.x, center.y);
    rlVertex2f(vertex2.x + center.x, vertex2.y + center.y);
    rlVertex2f(vertex2old.x + center.x, vertex2old.y + center.y);
    angle += step;
    vertex2old = vertex2;
    vertex2 = {cosf(angle + step) * (float)radius,
               sinf(angle + step) * (float)radius};
  }
  rlEnd();
}
