#include <cmath> // синус же!
#include <iostream> //вывод в консоль информации для дебага

#define RAYLIB_TILESON_IMPLEMENTATION
#include "src/raylib-tileson/raylib-tileson.h"

#include <raylib.h>
#include "src/player.h"
#include "src/scene.h"
#include "src/game.h"
// Размеры экрана
constexpr int SCREEN_WIDTH = 256 * 4;
constexpr int SCREEN_HEIGHT = 224 * 4;

enum screenstate
{
  teamlogo,
  titlescreen,
  options,
  game
}; 

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, raylib!");
  InitAudioDevice();      // Initialize audio device
  SetTargetFPS(60);
  SplashScreen s1;
//  s1.Draw();
  textures::InitTextures();
  fonts::InitFonts();
  SetTargetFPS(60);
  // Пока что игровая логика рассчитана на работу в 60 FPS.
  // Было бы круто снять потолок FPS, но мне лень ¯\_(ツ)_/¯
  std::cout << GetWorkingDirectory() << std::endl; // Чтобы проверить, с какой директорией работает программа

  Map map = LoadTiled("res/levels/stage1.tmj");
  screenstate currentstate = teamlogo;

  //Поддержка масштабирования игрового окна реализована так:
  //Сначала мы рисуем кадр в виртуальном полотне, затем масштабируем его до нужного разрешения
  //Хз, будет ли работать фуллскрин, лул
  int game_screen_width = 256;
  int game_screen_height = 240;
  Color bg = MAROON;
  RenderTexture2D virtual_canvas = LoadRenderTexture(game_screen_width, game_screen_height);
  int scale = 4; // Масштаб увеличения
  SetTextureFilter(virtual_canvas.texture, TEXTURE_FILTER_POINT);
  //Целочисленное масштабирование (2:1, 4:1...) реализуется с помощью фильтра "ближайший сосед"
  SetWindowMinSize(320, 240); //Меньше 320x240 окно отрисовывать запрещаем


  Scene mngtest;

  Game gm;
//  mngtest.ProcessLevel(map);

  while (!WindowShouldClose()) { // Окно закрывается нажатием ESC или крестика
    // Обновить данные
    // ---------------

    switch (currentstate)
    {
      case teamlogo:
      if (!s1.CanProceed())
      {
        s1.Update();
      }
      else
      {
        currentstate = game;
      }
      break;
      case game:
      gm.Update();
//      mngtest.Update();
      break;
      default:
      break;
    }

    //Отрисовка виртуального полотна
    // ---------------

    BeginTextureMode(virtual_canvas);

      switch (currentstate)
      {
        case teamlogo:
        s1.Draw();
        break;
        case game:
        ClearBackground(bg);
        gm.Draw();
        break;
        default:

        break;
      }

//      mngtest.Draw();
      DrawFPS(game_screen_width - 30, game_screen_height - 30);
    EndTextureMode();

    // Отрисовать окно
    // ---------------
    BeginDrawing();
      ClearBackground(BLACK);

    switch (currentstate)
    {
      case teamlogo:
      case game:
      DrawTexturePro(virtual_canvas.texture, Rectangle{ 0.0f, 0.0f, (float)virtual_canvas.texture.width, (float)-virtual_canvas.texture.height },
                      Rectangle{ (GetScreenWidth() - ((float)game_screen_width*scale))*0.5f, (GetScreenHeight() - ((float)game_screen_height*scale))*0.5f,
                      (float)game_screen_width*scale, (float)game_screen_height*scale }, Vector2{ 0, 0 }, 0.0f, WHITE);      
      break;
      default:
      break;
    }

//      DrawTexturePro(virtual_canvas.texture, Rectangle{ 0.0f, 0.0f, (float)virtual_canvas.texture.width, (float)-virtual_canvas.texture.height },
//                      Rectangle{ (GetScreenWidth() - ((float)game_screen_width*scale))*0.5f, (GetScreenHeight() - ((float)game_screen_height*scale))*0.5f,
//                      (float)game_screen_width*scale, (float)game_screen_height*scale }, Vector2{ 0, 0 }, 0.0f, WHITE);
    EndDrawing();
  }

  mngtest.Clear();
  textures::UnloadTextures();
  UnloadRenderTexture(virtual_canvas);
  UnloadMap(map);

  CloseWindow();
}