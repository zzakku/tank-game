#include <cmath> // синус же!
#include <iostream> //вывод в консоль информации для дебага

#include <raylib.h>

//TO-DO: Игрока неплохо бы вынести в отдельный класс

// Размеры экрана
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 960;

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, raylib!");
  SetTargetFPS(60);
  // Пока что игровая логика рассчитана на работу в 60 FPS.
  // Было бы круто снять потолок FPS, но мне лень ¯\_(ツ)_/¯
  char sorry[] = "Sorry nothing~";
  Texture2D player_tank = LoadTexture("res/player.png");
  std::cout << GetWorkingDirectory() << std::endl; // Чтобы проверить, с какой директорией работает программа
  int currentframe = 0;
  int frame_speed = 2;
  Rectangle frame_rec = { 0.0f, 0.0f, static_cast<float>(player_tank.width/2), static_cast<float>(player_tank.height/4)};
  SetTextureWrap(player_tank, TEXTURE_WRAP_CLAMP); // Задаёт способ отображения текстуры, часть которой вылезает за пределы картинки

  std::cout << static_cast<float>(player_tank.width/2) << static_cast<float>(player_tank.height) << std::endl;

  //Поддержка масштабирования игрового окна реализована так:
  //Сначала мы рисуем кадр в виртуальном полотне, затем масштабируем его до нужного разрешения
  //Хз, будет ли работать фуллскрин, лул
  int game_screen_width = 320;
  int game_screen_height = 240;
  RenderTexture2D virtual_canvas = LoadRenderTexture(game_screen_width, game_screen_height);
  int scale = 4; // Масштаб увеличения
  SetTextureFilter(virtual_canvas.texture, TEXTURE_FILTER_POINT); 
  //Целочисленное масштабирование (2:1, 4:1...) реализуется с помощью фильтра "ближайший сосед"
  SetWindowMinSize(320, 240); //Меньше 320x240 окно отрисовывать запрещаем

  int frames_counter = 0;
  int frames_speed = 25; // Фреймрейт анимации

  Vector2 player_pos = { static_cast<float>(game_screen_height/2), static_cast<float>(game_screen_width/2)};

  while (!WindowShouldClose()) { // Окно закрывается нажатием ESC или крестика
    // Обновить данные
    // ---------------

    Color bg = BLUE;
    if (IsKeyDown(KEY_RIGHT)) 
    {
      player_pos.x += 0.5f; // <- КОСТЫЛЬ >:(, но в целом работает

      frames_counter++;
      
      if (frames_counter >= (60/frames_speed))
      {
        frames_counter = 0;
        currentframe++;

        if (currentframe == 2) currentframe = 0;
      }
      frame_rec.x = static_cast<float>(currentframe)*static_cast<float>(player_tank.width/2);
      frame_rec.y = 1*static_cast<float>(player_tank.height/4) - 0.1f;
    }
    if (IsKeyDown(KEY_LEFT))
    {
      player_pos.x -= 0.5f;
      frames_counter++;
      
      if (frames_counter >= (60/frames_speed))
      {
        frames_counter = 0;
        currentframe++;

        if (currentframe == 2) currentframe = 0;
      }
      frame_rec.x = static_cast<float>(currentframe)*static_cast<float>(player_tank.width/2);
      frame_rec.y = 3*static_cast<float>(player_tank.height/4) - 0.1f;
    }
    if (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
    {
      player_pos.y -= 0.5f;
      frames_counter++;
      
      if (frames_counter >= (60/frames_speed))
      {
        frames_counter = 0;
        currentframe++;

        if (currentframe == 2) currentframe = 0;
      }
      frame_rec.x = static_cast<float>(currentframe)*static_cast<float>(player_tank.width/2);
      frame_rec.y = -0.1f;
    }      
    if (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
    {
      player_pos.y += 0.5f;
      frames_counter++;
      
      if (frames_counter >= (60/frames_speed))
      {
        frames_counter = 0;
        currentframe++;

        if (currentframe == 2) currentframe = 0;
      }
      frame_rec.x = static_cast<float>(currentframe)*static_cast<float>(player_tank.width/2);
      frame_rec.y = 2*static_cast<float>(player_tank.height/4) - 0.5f;
    }

    //Отрисовка виртуального полотна
    // ---------------

    BeginTextureMode(virtual_canvas);
      ClearBackground(bg);

      for (int i = 0; i < 14; i++)
      {
        Vector2 textpos;
        textpos.x = 30 + 20 * i;
        textpos.y =  30 + 2 * (sinf(textpos.x + 5 * GetTime()));
        DrawTextCodepoint(GetFontDefault(), sorry[i], textpos, 20, WHITE);
      }
      
      DrawTextureRec(player_tank, frame_rec, player_pos, WHITE);
      DrawFPS(game_screen_width - 30, game_screen_height - 30);
    EndTextureMode();

    // Отрисовать окно
    // ---------------
    BeginDrawing();
      ClearBackground(BLACK);

      DrawTexturePro(virtual_canvas.texture, (Rectangle){ 0.0f, 0.0f, (float)virtual_canvas.texture.width, (float)-virtual_canvas.texture.height },
                      (Rectangle){ (GetScreenWidth() - ((float)game_screen_width*scale))*0.5f, (GetScreenHeight() - ((float)game_screen_height*scale))*0.5f,
                      (float)game_screen_width*scale, (float)game_screen_height*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    EndDrawing();
  }

  UnloadRenderTexture(virtual_canvas);
  UnloadTexture(player_tank);

  CloseWindow();
}