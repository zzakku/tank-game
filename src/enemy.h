#ifndef TANK_SRC_ENEMY_H_
#define TANK_SRC_ENEMY_H_

#include <raylib.h>
#include "entity.h"
#include <stdint.h>
#include "textures.h"
#include "sound.h"

class Enemy: public Entity
{
private:
    uint8_t hp_;
    uint8_t grade_; // Уровень прокачки танка
    Rectangle framerec_;
    Texture2D graphics_ = textures::GetTexture("enemy");
    int currentframe_;
    int framespeed_;
    int framecounter_;
    DirectionFacing direction_;
    float movespeed_;
    float currentspeed_;
public:
    Enemy();
    ~Enemy();
    void Update();
    void Draw();
    void OnCollision(uint8_t other_id);
};

#endif // TANK_SRC_ENEMY_H_