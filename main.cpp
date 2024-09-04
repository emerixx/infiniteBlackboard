#include <cmath>
#include <raylib.h>
#include <rlgl.h>

const int windowWidth = 2000;
const int windowHeight = 1125;
const int textureSizeMultiplier = 3;

// i derived it somehow, i dont remember
const Vector2 startTexturePos = {
    -windowWidth * (textureSizeMultiplier - 1) / 2.0,
    -windowHeight *(textureSizeMultiplier - 1) / 2.0};

const Color backgroundColor = {0, 0, 0, 255};

Color availableDrawColors[] = {
    {255, 255, 255, 255}, {255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}};
int drawColorIndex = 0;
Color drawColor = availableDrawColors[drawColorIndex];
int radius = 1;
bool moveMode = false;
bool eraserMode = false;
bool shiftMode = false;
bool ctrlMode = false;
bool debugMode = false;
bool changeColorMode = false;
Vector2 texturePos = startTexturePos;
Vector2 mousePos;
Vector2 mousePos_old;

void betweenFrameDraw(Vector2 mp_old, Vector2 mp);

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
    // MODES - START
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      shiftMode = true;
    } else {
      shiftMode = false;
    }
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
      ctrlMode = true;
    } else {
      ctrlMode = false;
    }
    if (IsKeyDown(KEY_E)) {
      eraserMode = true;
    } else {
      eraserMode = false;
    }
    if (IsKeyDown(KEY_C)) {
      changeColorMode = true;
    } else {
      changeColorMode = false;
    }
    // MODES - END
    if (radius < 1) {
      radius = 1;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      if (moveMode && !changeColorMode) {
        texturePos.x += mousePos.x - mousePos_old.x;
        texturePos.y += mousePos.y - mousePos_old.y;
      }

      moveMode = true;
    } else {
      moveMode = false;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      if (changeColorMode) {
        drawColorIndex += 1;
        if (drawColorIndex ==
            sizeof(availableDrawColors) / sizeof(availableDrawColors[0])) {
          drawColorIndex = 0;
        }
      }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

      BeginTextureMode(target);
      if (eraserMode) {
        drawColor = backgroundColor;
      } else {
        drawColor = availableDrawColors[drawColorIndex];
      }
      betweenFrameDraw(mousePos_old, mousePos);
      DrawCircle(mousePos.x - texturePos.x, mousePos.y - texturePos.y, radius,
                 drawColor);
      EndTextureMode();
    }
    if (IsKeyPressed(KEY_UP)) {
      if (changeColorMode) {
        drawColorIndex += 1;
        if (drawColorIndex ==
            sizeof(availableDrawColors) / sizeof(availableDrawColors[0])) {
          drawColorIndex = 0;
        }
      } else {
        texturePos.y += windowHeight / 2.0;
      }
    }
    if (IsKeyPressed(KEY_DOWN)) {
      if (changeColorMode) {
        drawColorIndex -= 1;
        if (drawColorIndex == -1) {
          drawColorIndex =
              sizeof(availableDrawColors) / sizeof(availableDrawColors[0]) - 1;
        }
      } else {
        texturePos.y -= windowHeight / 2.0;
      }
    }
    if (IsKeyPressed(KEY_LEFT)) {
      texturePos.x += windowWidth / 2.0;
    }
    if (IsKeyPressed(KEY_RIGHT)) {
      texturePos.x -= windowWidth / 2.0;
    }

    if (IsKeyPressed(KEY_D)) {
      if (shiftMode) {
        BeginTextureMode(target);
        ClearBackground(BLACK);
        EndTextureMode();
      } else if (ctrlMode) {
        debugMode = !debugMode;
      }
    }
    BeginDrawing();
    ClearBackground(GRAY);

    DrawTextureRec(target.texture,
                   (Rectangle){0, 0, (float)target.texture.width,
                               (float)-target.texture.height},
                   (Vector2){texturePos.x, texturePos.y}, RAYWHITE);
    if (debugMode) {
      DrawFPS(0, 0);
    }
    EndDrawing();
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
