#ifndef SRC_TANK_EXPLOSION_H
#define SRC_TANK_EXPLOSION_H

#include <raylib.h>
#include "entity.h"
#include "textures.h"
#include <string>
#include <stdint.h>

class Explosion : public Entity
{
    private:
    Texture2D graphics_;
    Rectangle framerec_;
    int framespeed_ = 10;
    int framecounter_ = 0;
    int lifetime_ = 600;
    int currentframe_ = 0;
    public:
    Explosion()
    {
        id_ = 7;
        graphics_ = textures::GetTexture("explosion");
        framerec_ = {0.0f, 0.0f, static_cast<float>(graphics_.width/4), static_cast<float>(graphics_.height)};
    }
    Explosion(int x, int y) : Explosion()
    {
        pos_.x = static_cast<float>(x);
        pos_.y = static_cast<float>(y);
    }
    void Update()
    {
      framecounter_++;
      
      if (framecounter_ >= (60/framespeed_))
      {
        framecounter_ = 0;
        currentframe_++;

        if (currentframe_ == 4) destroyable_ = true;
      }
      framerec_.x = static_cast<float>(currentframe_)*static_cast<float>(graphics_.width/4);
    }
    void Draw()
    {
        DrawTextureRec(graphics_, framerec_, pos_, WHITE);
    }
    void OnCollision(uint8_t other_id)
    {
        
    }
};

#endif // SRC_TANK_EXPLOSION_H