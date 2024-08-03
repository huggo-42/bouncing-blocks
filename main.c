#include "./raylib/raylib.h"

typedef struct {
  float x;
  float y;
} Position;

typedef struct {
  Vector2 pos;
  Vector2 velo;
  Color color;
} Bot;

int botsCount = 69;
float blockSize = 42;
int screenWidth = 800;
int screenHeight = 600;

Bot randomBot() {
  Bot bot = {
      .pos =
          {
              GetRandomValue(0, GetScreenWidth() - blockSize),
              GetRandomValue(0, GetScreenHeight() - blockSize),
          },
      .velo = {500, 500},
      .color = ColorFromHSV(360 * ((float)GetRandomValue(0, 100) / 100.0), 1, 1),
  };
  return bot;
}

int main() {
  InitWindow(screenWidth, screenHeight, "Blocks2");
  Bot bot[botsCount];
  for (int i = 0; i < botsCount; i++) {
    bot[i] = randomBot();
  }
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(0x181818AA));
    for (int i = 0; i < botsCount; i++) {
      float new_x = bot[i].pos.x + (bot[i].velo.x * GetFrameTime());
      float new_y = bot[i].pos.y + (bot[i].velo.y * GetFrameTime());
      if (new_x < 0 || new_x + blockSize > GetScreenWidth()) {
        bot[i].velo.x *= -1;
        bot[i].color =
            ColorFromHSV(360 * ((float)GetRandomValue(0, 100) / 100.0), 1, 1);
      } else {
        bot[i].pos.x = new_x;
      }
      if (new_y < 0 || new_y + blockSize > GetScreenHeight()) {
        bot[i].velo.y *= -1;
        bot[i].color =
            ColorFromHSV(360 * ((float)GetRandomValue(0, 100) / 100.0), 1, 1);
      } else {
        bot[i].pos.y = new_y;
      }
      DrawRectangle(bot[i].pos.x, bot[i].pos.y, blockSize, blockSize, bot[i].color);
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
