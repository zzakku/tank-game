#ifndef SRC_TANK_BLOCK_H
#define SRC_TANK_BLOCK_H

#include <raylib.h>
#include "entity.h"
#include "textures.h"
#include <string>

// Кирпич:
// Кирпич - твёрдый блок, разрушаемый любыми пулями. Одна пуля "откусывает" от кирпича 8x8 минимум один кусочек 4x4
// (Четыре прямоугольника хитбокса?)

class Block : public Entity
{
    private:
    Texture2D graphics_ = textures::GetTexture("blocks");   
    Rectangle framerec_;
    public:
    Block()
    {
        id_ = 2;
        framerec_ = {0.0f, 0.0f, 8.0f, 8.0f};
        pos_ = {0.0f, 0.0f};
        hitbox_ = framerec_;
    }
    Block(int x, int y) : Block()
    {
        pos_.x = static_cast<float>(x);
        pos_.y = static_cast<float>(y);
        hitbox_.x = pos_.x;
        hitbox_.y = pos_.y;        
    } 
    ~Block()
    {
        UnloadTexture(graphics_);
        std::cout << "Hm?" << std::endl;
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
        // В оригинальной игре куст ни на что не реагировал
    }
};

#endif // SRC_TANK_BLOCK_H