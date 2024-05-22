#ifndef SRC_TANK_GAME_H
#define SRC_TANK_GAME_H

#include <raylib.h>

#include "scene.h"
#include "textures.h"
#include "font.h"

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
private:
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
    private:
    uint16_t lifetime_ = 100;
    bool can_proceed_ = false;
    Texture2D logo_ = LoadTexture("res/logo.png");
    Rectangle framerec_ = { 0.0f, 0.0f, static_cast<float>(logo_.width), static_cast<float>(logo_.height)};
    Color alpha_ = WHITE;
public:

    void Update() override
    {
        SetTextureFilter(logo_, TEXTURE_FILTER_BILINEAR);
        lifetime_--;
        if (lifetime_ <= 25)
        {
            alpha_ = ColorAlpha(alpha_, (static_cast<float>(lifetime_)/25.0f));
            if (lifetime_ == 0)
            {
                can_proceed_ = true;
            }
        }
    }

    void Draw() override
    {
        DrawTextureEx(logo_, {0.0f, 0.0f}, 0.0f, 0.25f, alpha_);
//    DrawTextureRec(logo_, framerec_, {0.0f, 0.0f}, alpha_); 
    }   
    bool CanProceed() { return can_proceed_; }
    void ResetLifetime() { lifetime_ = 100; }
};

class Game : public ScreenState
{
    private:
    std::unique_ptr<Scene> currentscene_;
//    Scene* currentscene_;
    uint8_t lives_ = 5;
    uint8_t enemies_remaining_;
    bool is_over_ = false;
    bool paused_ = false;
    public:
    Game()
    {
        sounds::InitSounds();
        Map map = LoadTiled("res/levels/stage1.tmj");
        currentscene_ = std::make_unique<Scene>();
        currentscene_->ProcessLevel(map);
        sounds::StartBGM("electrophilia");
    }
    void RespawnEnemy();
    void RespawnPlayer();
    void EndGame();
    void Update() override
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            paused_ = !paused_;
        }

        if (!paused_)
        {
            currentscene_->Update();
            sounds::UpdateBGM("electrophilia");
        }
    }
    void Draw() override
    {
        DrawTexture(textures::GetTexture("border"), 0, shiftv, WHITE);
        currentscene_->Draw();
        if (paused_)
        {
            DrawTextEx(fonts::GetFont("gametext"), "PAUSED", {101.0f, 113.0f}, 8, 0, RED);
        }
    }
};

class TitleScreen : public ScreenState
{
    private:
    bool can_proceed_;
    char titletext[256] = ".######...####...##..##..##..##.\n...##....##..##..###.##..##.##..\n...##....######..##.###..####...\n...##....##..##..##..##..##.##..\n...##....##..##..##..##..##..##.\n................................";
    //    char titletext[75] = " #### #### #  # # #\n  #  #  # ## # ##\n #  #### # ## ##\n#  #  # #  # #  #";
    public:
    void Update() override
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            can_proceed_ = true;
        }
    }

    void Draw() override
    {
        DrawTextEx(fonts::GetFont("gametext"), titletext, {0.0f, 10.0f}, 8, 0, WHITE);        
        DrawTextEx(fonts::GetFont("gametext"), "PUSH ENTER", {80.0f, 112.0f}, 8, 0, WHITE);
        DrawTextEx(fonts::GetFont("gametext"), "(c) KUZKULCHIK 2024", {88.0f, 210.0f}, 8, 0, WHITE);
    }   
    bool CanProceed()
    {
        return can_proceed_;
    }
};

/*class ScreenState
{
    public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

class Game : public ScreenState
{
    private:
    Scene* currentscene_;
    uint8_t lives_;
    uin8t_t enemies_remaining_;
    bool is_over_;
    public:
    void RespawnEnemy();
    void RespawnPlayer();
    void EndGame();
    void 
};*/

#endif // SRC_TANK_GAME_H