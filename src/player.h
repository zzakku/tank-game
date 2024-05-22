#ifndef TANK_SRC_PLAYER_H_
#define TANK_SRC_PLAYER_H_

#include <raylib.h>
#include "entity.h"
#include <stdint.h>
#include "textures.h"
#include "sound.h"


// TO-DO: Класс "игрок", реализовать (потенциально) поддержку двух игроков и "автопилота" в демо-режиме

class Player: public Entity
{
    private:
    uint8_t hp_; // Сколько попаданий пуль танк выдержит
    uint8_t grade_; // Уровень прокачки танка (нужно допилить павер-апы...)
    Rectangle framerec_; // Прямоугольник, в который мы помещаем текущий кадр анимации
    Texture2D graphics_ = textures::GetTexture("player"); // Текстура, откуда мы берём кадры анимации игрока
    int currentframe_; // Текущий кадр анимации
    int framespeed_; // Скорость анимации (FPS)
    int framecounter_; // Счётчик, отслеживающий удерживание ввода игроком (чтобы "двигать" анимацию)
    DirectionFacing direction_; // Куда смотрит дуло танка?
    float movespeed_; // Скорость передвижения танка
    public:
    Player();
    ~Player();
    void Update();
    void Draw();
    void OnCollision(uint8_t other_id);
    void Upgrade(); // Здесь будет подбор бонуса "звезда"
};



// пока возможно временно - пуля имеет ID 5

//Player::Player()
//{
//    id_ = 1;
//    hp_ = 1;
//    grade_ = 1;
//    graphics_ = LoadTexture("res/player.png");
//    SetTextureWrap(graphics_, TEXTURE_WRAP_CLAMP); // Задаёт способ отображения текстуры, часть которой вылезает за пределы картинки
//    framerec_ = { 0.0f, 0.0f, static_cast<float>(graphics_.width/2), static_cast<float>(graphics_.height/4)};
//    currentframe_ = 0;
//    framespeed_ = 25;
//    framecounter_ = 0;
//    pos_ = { 0.0f, 0.0f};
//    hitbox_ = {0.0f, 0.0f, 15.0f, 15.0f};
//    direction_ = up;
//    movespeed_ = 0.5f;
//}


// Мне лень создавать хедеры-заглушки для пуль и врагов, но вот моя идея пока что:
// Враг один, отличается лишь внешним видом, скоростью и количеством ХП
// Пули можно помечать как "свои/чужие", но если игрок будет один, то можно и не помечать
// Надо придумать способ ограничить максимальное кол-во пуль на экране для каждого танка (1 на первом уровне/2 далее)
// Ещё у пуль особое взаимодействие ИМЕННО с кирпичами: кирпичам надо отслеживать, в какую четверть их квадрата коллизий прилетела пуля
// Также есть эффекты спавна и взрывы, посмотрите, как они ведут себя в оригинальной игре
// Ещё игроку надо прописать эффект бонуса "неуязвимость"

class Enemy: public Entity
{
private:
    uint8_t hp_; // Сколько попаданий пуль танк выдержит
    uint8_t grade_; // Уровень прокачки танка
    Rectangle framerec_; // Прямоугольник, в который мы помещаем текущий кадр анимации
    Texture2D graphics_ = textures::GetTexture("enemy"); // Текстура, откуда мы берём кадры анимации
    int currentframe_; // Текущий кадр анимации
    int framespeed_; // Скорость анимации (FPS)
    int framecounter_; // Счётчик кадров для анимации
    DirectionFacing direction_; // Куда смотрит дуло танка?
    float movespeed_; // Скорость передвижения танка
public:
    Enemy();
    ~Enemy();
    void Update();
    void Draw();
    void OnCollision(uint8_t other_id);
};

#endif // TANK_SRC_PLAYER_H_