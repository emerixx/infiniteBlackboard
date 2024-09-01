#include <iostream>
#include <raylib.h>

const int windowWidth = 2400;
const int windowHeight = 1400;
const int textureSizeMultiplier = 2;
const Vector2 startTexturePos = {
    -windowWidth * (textureSizeMultiplier - 1) / 2.0,
    -windowHeight *(textureSizeMultiplier - 1) / 2.0};
const char *imgToLoad = "./imgs/blank.png";
const Color backgroundColor = {0, 0, 0, 255};
int radius = 1;
bool isShiftDown = false;
bool wasRMBDown = false;
Vector2 texturePos = startTexturePos;
Vector2 mousePos;
Vector2 mousePos_old;
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
      std::cout << mousePos.x << ":" << mousePos.y << "\n";
      DrawCircle(mousePos.x - texturePos.x, mousePos.y - texturePos.y, radius,
                 WHITE);
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
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      isShiftDown = true;
    } else {
      isShiftDown = false;
    }
    if (IsKeyDown(KEY_C) && isShiftDown) {
      BeginTextureMode(target);
      ClearBackground(BLACK);
      EndTextureMode();
    }
    BeginDrawing();
    ClearBackground(GRAY);

    DrawTextureRec(target.texture,
                   (Rectangle){0, 0, (float)target.texture.width,
                               (float)-target.texture.height},
                   (Vector2){texturePos.x, texturePos.y}, WHITE);

    // DrawTexture(target.texture, 0, 0, WHITE);

    EndDrawing();
    std::cout << GetFPS() << "\n";
  }
  UnloadRenderTexture(target);
  CloseWindow();
  return 0;
}
