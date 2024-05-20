#ifndef SRC_TANK_GAME_H
#define SRC_TANK_GAME_H

#include <raylib.h>

// Здесь будет класс "Игра". Он управляет сценами, то бишь, основным геймплеем
// Поля: количество жизней игрока, текущий уровень, "игра стоит на паузе", указатель на сцену, количество оставшихся врагов (20 в начале раунда)
// Игра запрашивает у сцены респавн врагов и игроков, в сцене надо предусмотреть методы, которые спавнят игроков и врагов с соответствующим визуальным эффектом
// Ещё игра следит за жизнями игрока и в случае чего говорит, что произошёл гейм овер (можно вынести как булевое значение в поля класса)
// По идее, Игра наследуется от ScreenState
// ScreenState - полностью абстрактный класс с методами Update() и Draw()
// Из main переключение можно осуществлять путём получения указателя на текущее состояние экрана из какого-нибудь контейнера
// Кстати, предлагаю такие состояния:
// Splash Screen (лого команды), TitleScreen (опция "начать игру", ВОЗМОЖНО "настройки"), Game, Options

class ScreenState
{
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;

};

//class Game: public ScreenState
//{
//private:
//    bool pause_;
//
//};

class SplashScreen : public ScreenState
{
public:

    void Update() override
    {
        //тут пусто
    }

void Draw() override {
        int framesCounter = 0;
    BeginDrawing();

    ClearBackground(RAYWHITE);
    Texture2D logo = LoadTexture("res/logo.png");

    SetTextureWrap(logo, TEXTURE_WRAP_CLAMP); // Задаёт способ отображения текстуры
    Rectangle framerec_ = { 0.0f, 0.0f, static_cast<float>(logo.width), static_cast<float>(logo.height)};

    Vector2 pos_ = { 0.0f, 0.0f};
    DrawTextureRec(logo, framerec_, pos_, WHITE);

    EndDrawing();
    while (1)
    {
        framesCounter++;
        if (framesCounter > 600) // ! счетчик не привязан к кадрам
        {
            break;
        }

    }
    ClearBackground(BLACK);
}
};

#endif // SRC_TANK_GAME_H