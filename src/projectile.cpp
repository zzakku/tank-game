#include "projectile.h"
#include "scene.h"

void Projectile::Update()
{
    switch(direction_)
    {
        case right:
        pos_.x += movespeed_;
        framerec_.x = static_cast<float>((graphics_.width/4)*1);
        break;
        case left:
        pos_.x -= movespeed_;
        framerec_.x = static_cast<float>((graphics_.width/4)*3); 
        break;
        case up:
        pos_.y -= movespeed_;
        framerec_.x = static_cast<float>((graphics_.width/4)*4);
        break;  
        case down:
        pos_.y += movespeed_;
        framerec_.x = static_cast<float>((graphics_.width/4)*2);
        break;            
    }

    hitbox_.x = pos_.x;
    hitbox_.y = pos_.y;
}

void Projectile::Draw()
{
    DrawTextureRec(graphics_, framerec_, pos_, WHITE);
//    DrawRectangle(hitbox_.x, hitbox_.y, hitbox_.width, hitbox_.height, WHITE); <- если захочется отладить хитбокс
}

void Projectile::OnCollision(uint8_t other_id)
{
  Sound sound_expload = LoadSound("..\\res\\soundtracks\\Explosion.wav");
  switch (other_id)
  {
    case 1: case 2: case 3: case 5: case 6:
    destroyable_ = true;
    //Sound sound_expload = LoadSound("..\\res\\soundtracks\\Explosion.wav");
    PlaySound(sound_expload);
    scene_->SpawnExplosion(pos_.x - hitbox_.width, pos_.y - hitbox_.height);
    break;
    default:
    break;
  }
}