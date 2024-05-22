#ifndef SRC_TANK_BLOCK_H
#define SRC_TANK_BLOCK_H

#include <raylib.h>
#include "entity.h"
#include "textures.h"
#include <string>

// Кирпич:
// Кирпич - твёрдый блок, разрушаемый любыми пулями. Размер - 4x4, у всех других он 8x8.

// Параметр corner:
        // -----
        // |0|1|
        // |2|3|
        // -----

class Block : public Entity
{
    private:
    Texture2D graphics_ = textures::GetTexture("blocks");   
    Rectangle framerec_;
    public:
    Block()
    {
        id_ = 2;
        framerec_ = {0.0f, 0.0f, 4.0f, 4.0f};
        pos_ = {0.0f, 0.0f};
        hitbox_ = framerec_;
    }
    Block(int x, int y, uint8_t corner) : Block()
    {
        pos_.x = static_cast<float>(x);
        pos_.y = static_cast<float>(y);
        hitbox_.x = pos_.x;
        hitbox_.y = pos_.y;        
        switch (corner)
        {
            case 0:
            break;
            case 1:
            framerec_.x += 4.0f;
            break;
            case 2:
            framerec_.y += 4.0f;
            break;
            case 3:
            framerec_.y += 4.0f;
            framerec_.x += 4.0f;
            default:
            // Вообще-то, это очень плохо...
            break;
        }
    } 
    ~Block()
    {
    }
    void Update()
    {
        // idk
    }
    void Draw()
    {
        DrawTextureRec(graphics_, framerec_, pos_, WHITE);
    }
    void OnCollision(uint8_t other_id)
    {
        switch (other_id)
        {
            case 5:
            destroyable_ = true;
            break;
            default:
            break;
        }
        // Сюда реакцию на любую пулю
    }
};

// Бетон:
// Бетон - твёрдый блок. Его может разрушить только выстрел танка третьего уровня прокачки.

class Concrete : public Entity
{
    private:
    Texture2D graphics_ = textures::GetTexture("blocks");    
    Rectangle framerec_;
    public:
    Concrete()
    {
        id_ = 3;
        framerec_ = {0.0f, 16.0f, 8.0f, 8.0f};
        pos_ = {0.0f, 0.0f};
        hitbox_ = framerec_;
    }
    Concrete(int x, int y) : Concrete()
    {
        pos_.x = static_cast<float>(x);
        pos_.y = static_cast<float>(y);
        hitbox_.x = pos_.x;
        hitbox_.y = pos_.y;        
    }
    ~Concrete()
    {
        UnloadTexture(graphics_);
    } 
    void Update()
    {
        // idk
    }
    void Draw()
    {
        DrawTextureRec(graphics_, framerec_, pos_, WHITE);
    }
    void OnCollision(uint8_t other_id)
    {
        // Сюда реакцию на пулю танка третьего уровня прокачки
    }
};

// Куст:
// Куст - блок, не имеющий коллизии. В Tank 1990 его возможно разрушить выстрелом танка, прокачанного бонусом "Пистолет", но это не уничтожает патрон

class Bush : public Entity
{
    private:
    Texture2D graphics_ = textures::GetTexture("blocks");   
    Rectangle framerec_;
    public:
    Bush()
    {
        id_ = 4;
        framerec_ = {0.0f, 32.0f, 8.0f, 8.0f};
        pos_ = {0.0f, 0.0f};
        hitbox_ = framerec_;
    }
    Bush(int x, int y) : Bush()
    {
        pos_.x = static_cast<float>(x);
        pos_.y = static_cast<float>(y);
        hitbox_.x = pos_.x;
        hitbox_.y = pos_.y;        
    } 
    ~Bush()
    {
    }
    void Update()
    {
        // idk
    }
    void Draw()
    {
        DrawTextureRec(graphics_, framerec_, pos_, WHITE);
    }
    void OnCollision(uint8_t other_id)
    {
        // В оригинальной игре куст ни на что не реагировал
    }
};

class Invisible_entity : public Entity
{
    private:
    public:
    Invisible_entity()
    {
        id_ = 6;
        hitbox_ = {0.0f, 0.0f, 0.0f, 0.0f};
        //pos_.x = 0.0f;
        //pos_.y = 0.0f;
    }
    Invisible_entity(int x, int y, bool is_horizontal) : Invisible_entity()
    {
        pos_.x = static_cast<float>(x);
        pos_.y = static_cast<float>(y);

        if (is_horizontal){
            hitbox_ = {0.0f, 0.0f, 230.0f, 20.0f};
        }
        else{
            hitbox_ = {0.0f, 0.0f, 20.0f, 230.0f};
        }
        hitbox_.x = pos_.x;
        hitbox_.y = pos_.y;

    } 
    void Update()
    {
        // idk
    }
    void Draw()
    {
    }
    void OnCollision(uint8_t other_id)
    {
        
    }
};

class Eagle_base : public Entity
{
private:
    Texture2D graphics_ = textures::GetTexture("eagle");
    Rectangle framerec_;
public:
    Eagle_base()
    {
        id_ = 9;
        framerec_ = {0.0f, 0.0f, 16.0f, 16.0f};
        pos_ = {0.0f, 0.0f};
        hitbox_ = framerec_;
    }
    Eagle_base(int x, int y) : Eagle_base()
    {
        pos_.x = static_cast<float>(x);
        pos_.y = static_cast<float>(y);
        hitbox_.x = pos_.x;
        hitbox_.y = pos_.y;
    }
    ~Eagle_base()
    {
        UnloadTexture(graphics_);
    }
    void Update()
    {
        // idk
    }
    void Draw()
    {
        DrawTextureRec(graphics_, framerec_, pos_, WHITE);
    }
    void OnCollision(uint8_t other_id)
    {

        switch (other_id)
        {
            case 5:
                destroyable_ = true;
                break;
            default:
                break;
        }
    }
};



#endif // SRC_TANK_BLOCK_H