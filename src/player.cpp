#include "player.h"
#include "scene.h"
#include <iostream>
#include "scene.h"

Player::Player()
{
    id_ = 1;
    hp_ = 1;
    grade_ = 1;
    SetTextureWrap(graphics_, TEXTURE_WRAP_CLAMP); // Задаёт способ отображения текстуры, часть которой вылезает за пределы картинки
    framerec_ = { 0.0f, 0.0f, static_cast<float>(graphics_.width/2), static_cast<float>(graphics_.height/4)};
    currentframe_ = 0;
    framespeed_ = 25;
    framecounter_ = 0;
    pos_ = { 104.0f, 180.0f};
    hitbox_ = {0.0f, 0.0f, 15.0f, 15.0f};
    direction_ = up;
    movespeed_ = 0.5f;
    reloaded_bullet_ = true;
    cooldawn_ = 60;
}

Player::~Player()
{
    std::cout << "Player destructor called" << std::endl;
    UnloadTexture(graphics_);
}

void Player::Draw()
{
    DrawTextureRec(graphics_, framerec_, pos_, WHITE);
}

void Player::Update()
{

    if (IsKeyDown(KEY_SPACE))
    {
        //actives_.push_back(creator_->CreateBullet());
    }

    if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) 
    {
      pos_.x += movespeed_;
      direction_ = right;

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
    if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
    {
      pos_.x -= movespeed_;
      framecounter_++;
      direction_ = left;
      
      if (framecounter_ >= (60/framespeed_))
      {
        framecounter_ = 0;
        currentframe_++;

        if (currentframe_ == 2) currentframe_ = 0;
      }
      framerec_.x = static_cast<float>(currentframe_)*static_cast<float>(graphics_.width/2);
      framerec_.y = 3*static_cast<float>(graphics_.height/4) - 0.1f;
    }
    if (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN))
    {
      pos_.y -= movespeed_;
      framecounter_++;
      direction_ = up;
      
      if (framecounter_ >= (60/framespeed_))
      {
        framecounter_ = 0;
        currentframe_++;

        if (currentframe_ == 2) currentframe_ = 0;
      }
      framerec_.x = static_cast<float>(currentframe_)*static_cast<float>(graphics_.width/2);
      framerec_.y = -0.1f;
    }      
    if (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_UP))
    {
      pos_.y += movespeed_;
      framecounter_++;
      direction_ = down;
      
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

    if (cooldawn_ < 60){
      cooldawn_+=1;
    }
    else{
      reloaded_bullet_ = true;
    }

    if (IsKeyPressed(KEY_Z))
    {
      if (reloaded_bullet_ == true){
      reloaded_bullet_ = false;
      cooldawn_ = 0;


      Sound sound_append_bullet = LoadSound("res/soundtracks/Gun.wav");
      PlaySound(sound_append_bullet);
      //std::cout<<"lol";
      switch (direction_){
        case up:
        scene_->SpawnProjectile(pos_.x + 6.0f, pos_.y - 5.0f, direction_);
        break;
        case right:
        scene_->SpawnProjectile(pos_.x + 16.0f, pos_.y + 7.0f, direction_);
        break;
        case down:
        scene_->SpawnProjectile(pos_.x + 6.0f, pos_.y + 16.0f, direction_);
        break;
        case left:
        scene_->SpawnProjectile(pos_.x - 5.0f, pos_.y + 7.0f, direction_);
        break;

      }

      }
    }
}

void Player::OnCollision(uint8_t other_id)
{
  switch (other_id)
  {
    case 1:
    break;
    case 2: case 3: case 6: case 9: case 8:
    switch (direction_)
    {
      case up:
      pos_.y += movespeed_;
      hitbox_.y = pos_.y;
      break;
      case down:
      pos_.y -= movespeed_;
      hitbox_.y = pos_.y;
      break;
      case left:
      pos_.x += movespeed_;
      hitbox_.x = pos_.x;
      break;
      case right:
      pos_.x -= movespeed_;
      hitbox_.x = pos_.x;
      break;
    }
    default:
    break;
  }
}


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
    hitbox_ = {0.0f, 0.0f, 15.0f, 15.0f};
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