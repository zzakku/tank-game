#include <algorithm> // for std::clamp
#include <cmath> // for std::hypot

#include <raylib.h>

// Размеры экрана
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

// Фоновые цвета для интерполяции
constexpr Color COLOR_BG_A = { 30, 10, 10, 255 }; // темно-красный
constexpr Color COLOR_BG_B = { 10, 10, 30, 255 }; // темно-синий

// Функция линейной интерполяции
constexpr double lerp(double a, double b, double t)
{
  return a + t * (b - a);
}

// Функция линейной интерполяции цветов
Color InterpolateColor(Color a, Color b, double t)
{
  double ar = (double)a.r / 255.0;
  double ag = (double)a.g / 255.0;
  double ab = (double)a.b / 255.0;
  double br = (double)b.r / 255.0;
  double bg = (double)b.g / 255.0;
  double bb = (double)b.b / 255.0;

  t = std::clamp(t, 0.0, 1.0);
  double cr = lerp(ar, br, t);
  double cg = lerp(ag, bg, t);
  double cb = lerp(ab, bb, t);

  return Color { 
    (unsigned char)(cr * 255.0),
    (unsigned char)(cg * 255.0),
    (unsigned char)(cb * 255.0),
    255
  };
}

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, raylib!");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Обновить данные
    // ---------------
    Vector2 mouse = GetMousePosition();
    double mouse_percentage = 
      std::hypot((double)mouse.x, (double)mouse.y) /
      std::hypot((double)SCREEN_WIDTH, (double)SCREEN_HEIGHT);

    // меняем цвет фона в зависимости от того, как далеко расположен курсор от левого верхнего края экрана
    Color bg = InterpolateColor(COLOR_BG_A, COLOR_BG_B, mouse_percentage);

    // Отрисовать окно
    // ---------------
    BeginDrawing();
      ClearBackground(bg);
      DrawText("Hello, world!", 30, 30, 20, WHITE);
      DrawFPS(SCREEN_WIDTH - 30, SCREEN_HEIGHT - 30);
    EndDrawing();
  }

  CloseWindow();
}