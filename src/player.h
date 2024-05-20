#ifndef TANK_SRC_PLAYER_H_
#define TANK_SRC_PLAYER_H_

#include <raylib.h>
#include "entity.h"
#include <stdint.h>
#include "textures.h"


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

class Bullet: public Entity
{
    Rectangle framerec_;
    Texture2D graphics_;
    DirectionFacing direction_;
    float movespeed;
public:
    Bullet()
    {
        id_ = 5;
        graphics_ = LoadTexture("res/bullet.png");
        SetTextureWrap(graphics_, TEXTURE_WRAP_CLAMP);
        framerec_ = { 0.0f, 0.0f, static_cast<float>(graphics_.width/4), static_cast<float>(graphics_.height)};
        direction_ = up;
        movespeed = 1.0f;
        hitbox_ = {40.0f, 40.0f, 40.0f, 40.0f};
        pos_ = {40.0f, 40.0f};
    }
    Bullet(float x_pos, float y_pos, DirectionFacing dir)
    {
        id_ = 5;
        graphics_ = LoadTexture("res/bullet.png");
        SetTextureWrap(graphics_, TEXTURE_WRAP_CLAMP);
        framerec_ = { 0.0f, 0.0f, static_cast<float>(graphics_.width/4), static_cast<float>(graphics_.height)};
        direction_ = up;
        movespeed = 1.0f;
        hitbox_ = {x_pos, y_pos, x_pos+4, y_pos+4};
        pos_ = {x_pos, y_pos};
    }
    ~Bullet(){}
    void Update()
    {
        switch (direction_) {
            case up:
            {
                pos_.y-=movespeed;
                break;
            }
            case down:
            {
                pos_.y+=movespeed;
                break;
            }
            case right:
            {
                pos_.x+=movespeed;
                break;
            }
            case left:
            {
                pos_.x-=movespeed;
                break;
            }

        }
    }
    void OnCollision(uint8_t other_id)
    {
        int a  = 0;
    }
    void Draw()
    {
        DrawTextureRec(graphics_, framerec_, pos_, WHITE);
    }
};
//class Entity
//{
//protected:
//    Scene* scene_ = nullptr; // Каждая сущность знает сцену, из которой она происходит
//    Rectangle hitbox_; // Надо определиться, совпадает ли хитбокс с прямоугольником отрисовки
//    Vector2 pos_;
//    bool fliph_; // Флаг "объект отражён по горизонтали"
//    bool flipv_; // Флаг "объект отражён по вертикали"
//    uint8_t id_; // ID объекта
//    // Подтип?
//    bool destroyable_; // Флаг "данную сущность можно уничтожить"
//public:
//    virtual void Update() = 0;
//    virtual void Draw() = 0;
//    uint8_t GetID() { return id_; }
//    Rectangle GetCollision() { return hitbox_; }
//    virtual void OnCollision(uint8_t other_id) = 0; // В эту функцию менеджер объектов передаёт объект, коллизию с которым необходимо обработать
//};


// Мне лень создавать хедеры-заглушки для пуль и врагов, но вот моя идея пока что:
// Враг один, отличается лишь внешним видом, скоростью и количеством ХП
// Пули можно помечать как "свои/чужие", но если игрок будет один, то можно и не помечать
// Надо придумать способ ограничить максимальное кол-во пуль на экране для каждого танка (1 на первом уровне/2 далее)
// Ещё у пуль особое взаимодействие ИМЕННО с кирпичами: кирпичам надо отслеживать, в какую четверть их квадрата коллизий прилетела пуля
// Также есть эффекты спавна и взрывы, посмотрите, как они ведут себя в оригинальной игре
// Ещё игроку надо прописать эффект бонуса "неуязвимость"

#endif // TANK_SRC_PLAYER_H_