#ifndef SRC_TANK_GAME_H
#define SRC_TANK_GAME_H

#include <raylib.h>

#include "scene.h"

// Здесь будет класс "Игра". Он управляет сценами, то бишь, основным геймплеем
// Поля: количество жизней игрока, текущий уровень, "игра стоит на паузе", указатель на сцену, количество оставшихся врагов (20 в начале раунда)
// Игра запрашивает у сцены респавн врагов и игроков, в сцене надо предусмотреть методы, которые спавнят игроков и врагов с соответствующим визуальным эффектом
// Ещё игра следит за жизнями игрока и в случае чего говорит, что произошёл гейм овер (можно вынести как булевое значение в поля класса)
// По идее, Игра наследуется от ScreenState
// ScreenState - полностью абстрактный класс с методами Update() и Draw()
// Из main переключение можно осуществлять путём получения указателя на текущее состояние экрана из какого-нибудь контейнера
// Кстати, предлагаю такие состояния:
// Splash Screen (лого команды), TitleScreen (опция "начать игру", ВОЗМОЖНО "настройки"), Game, Options

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