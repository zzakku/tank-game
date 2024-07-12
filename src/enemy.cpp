#include "enemy.h"
#include "scene.h"

Enemy::Enemy()
{
    id_ = 8;
    hp_ = 1;
    grade_ = 1;
    SetTextureWrap(graphics_, TEXTURE_WRAP_CLAMP); // Задаёт способ отображения текстуры, часть которой вылезает за пределы картинки
    framerec_ = { 0.0f, 0.0f, static_cast<float>(graphics_.width/2), static_cast<float>(graphics_.height/4)};
    currentframe_ = 0;
    framespeed_ = 25;
    framecounter_ = 0;
    pos_ = { 32.0f, 32.0f};
    hitbox_ = {0.0f, 0.0f, 16.0f, 16.0f};
    direction_ = down;
    movespeed_ = 0.5f;
}

Enemy::~Enemy()
{
    //UnloadTexture(graphics_);
}

void Enemy::Draw()
{
    DrawTextureRec(graphics_, framerec_, pos_, WHITE);
}

void Enemy::OnCollision(uint8_t other_id)
{
    switch (other_id)
    {
        //case 1:
        //    break;
        case 1: case 2: case 3: case 6: case 9:
            switch (direction_)
            {
                case up:
                    pos_.y += movespeed_;
                    hitbox_.y = pos_.y;
                    direction_ = right;
                    break;
                case down:
                    pos_.y -= movespeed_;
                    hitbox_.y = pos_.y;
                    direction_ = left;
                    break;
                case left:
                    pos_.x += movespeed_;
                    hitbox_.x = pos_.x;
                    direction_ = up;
                    break;
                case right:
                    pos_.x -= movespeed_;
                    hitbox_.x = pos_.x;
                    direction_ = down;
                    break;
            }
        case 5:
            destroyable_ = true;
            sounds::PlaySFX("explosion");
            for (int i = 0; i < 3; i++)
            {
                scene_->SpawnExplosion(pos_.x + GetRandomValue(-5,5), pos_.y + GetRandomValue(-5,5));
            }


        default:
            break;
    }
}

void Enemy::Update()
{

    if (direction_ == right)
    {
        pos_.x += movespeed_;

        framecounter_++;

        if (framecounter_ >= (60/framespeed_))
        {
            framecounter_ = 0;
            currentframe_++;

            if (currentframe_ == 2) currentframe_ = 0;
        }
        framerec_.x = static_cast<float>(currentframe_)*static_cast<float>(graphics_.width/2);
        framerec_.y = 1*static_cast<float>(graphics_.height/4) - 0.1f; // <- КОСТЫЛЬ >:(, но в целом работает
    }
    if (direction_ == left)
    {
        pos_.x -= movespeed_;
        framecounter_++;

        if (framecounter_ >= (60/framespeed_))
        {
            framecounter_ = 0;
            currentframe_++;

            if (currentframe_ == 2) currentframe_ = 0;
        }
        framerec_.x = static_cast<float>(currentframe_)*static_cast<float>(graphics_.width/2);
        framerec_.y = 3*static_cast<float>(graphics_.height/4) - 0.1f;
    }
    if (direction_ == up)
    {
        pos_.y -= movespeed_;
        framecounter_++;

        if (framecounter_ >= (60/framespeed_))
        {
            framecounter_ = 0;
            currentframe_++;

            if (currentframe_ == 2) currentframe_ = 0;
        }
        framerec_.x = static_cast<float>(currentframe_)*static_cast<float>(graphics_.width/2);
        framerec_.y = -0.1f;
    }
    if (direction_ == down)
    {
        pos_.y += movespeed_;
        framecounter_++;

        if (framecounter_ >= (60/framespeed_))
        {
            framecounter_ = 0;
            currentframe_++;

            if (currentframe_ == 2) currentframe_ = 0;
        }
        framerec_.x = static_cast<float>(currentframe_)*static_cast<float>(graphics_.width/2);
        framerec_.y = 2*static_cast<float>(graphics_.height/4) - 0.5f;
    }

    hitbox_.x = pos_.x;
    hitbox_.y = pos_.y;

}