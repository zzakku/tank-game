#ifndef SRC_TANK_PROJECTILE_H
#define SRC_TANK_PROJECTILE_H

#include <raylib.h>
#include "entity.h"
#include <stdint.h>
#include "textures.h"

class Projectile : public Entity
{
    private:
    uint8_t movespeed_;
    Texture2D graphics_ = textures::GetTexture("projectile");
    DirectionFacing direction_;
    Rectangle framerec_;
    public:
    Projectile()
    {
        id_ = 5;
        movespeed_ = 1.0f;
        hitbox_ = {0.0f, 0.0f, 8.0f, 8.0f};
        framerec_ = { 0.0f, 0.0f, static_cast<float>(graphics_.width/4), static_cast<float>(graphics_.height)};
        pos_ = {0.0f, 0.0f};
    }
    Projectile(int x, int y, DirectionFacing direction) : Projectile()
    {
        pos_.x = static_cast<float>(x);
        pos_.y = static_cast<float>(y);
        direction_ = direction;
    }
    void Update();
    void Draw();
    void OnCollision(uint8_t other_id);
};

#endif // SRC_TANK_PROJECTILE_H