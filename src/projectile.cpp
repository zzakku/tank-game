#include "projectile.h"

void Projectile::Update()
{
    switch(direction_)
    {
        case right:
        pos_.x += movespeed_;
        framerec_.x = static_cast<float>((graphics_.width/4)*2);
        break;
        case left:
        pos_.x -= movespeed_;
        framerec_.x = static_cast<float>((graphics_.width/4)*4); 
        break;
        case up:
        pos_.y -= movespeed_;
        framerec_.x = static_cast<float>((graphics_.width/4)*1);
        break;  
        case down:
        pos_.y += movespeed_;
        framerec_.x = static_cast<float>((graphics_.width/4)*3);
        break;            
    }

    hitbox_.x = pos_.x;
    hitbox_.y = pos_.y;
}

void Projectile::Draw()
{
    DrawTextureRec(graphics_, framerec_, pos_, WHITE);
}

void Projectile::OnCollision(uint8_t other_id)
{
  switch (other_id)
  {
    case 1: case 2: case 3: case 5:
    destroyable_ = true;
    break;
    default:
    break;
  }
}