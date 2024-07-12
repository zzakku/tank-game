#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "block.h"
#include "projectile.h"
#include "explosion.h"

std::unique_ptr<Entity> EntityCreator::CreatePlayer() { return std::make_unique<Player>(); } // new Player(); }

std::unique_ptr<Entity> EntityCreator::CreateEnemy() { return std::make_unique<Enemy>(); }

std::unique_ptr<Entity> EntityCreator::CreateBrickWall(int x, int y, uint8_t corner)
    {
        return std::make_unique<Block>(x, y, corner);
    }
std::unique_ptr<Entity> EntityCreator::CreateOtherWall(TileMaterial material, int x, int y)
    {
        switch(material)
        {
            case brick:
//            for (int i = 0; i < 4; i++)
//            {
//            return std::make_unique<Block>(x, y,i);                
//            }
//            return std::make_unique<Block>(x, y);
            return nullptr;
            break;
            case concrete:
            return std::make_unique<Concrete>(x, y);
            break;
            case bush:
            return std::make_unique<Bush>(x, y);
            break;
            default:
            return nullptr;
        }
    } // Создать блок 8x8 на позиции виртуального полотна (x,y)
std::unique_ptr<Entity> EntityCreator::CreateProjectile(int x, int y, DirectionFacing direction)
    {
        return std::make_unique<Projectile>(x,y,direction);
    }

std::unique_ptr<Entity> EntityCreator::CreateInvisibleWall(int x, int y, bool is_horizontal){
    return std::make_unique<Invisible_entity>(x,y,is_horizontal);
}

std::unique_ptr<Entity> EntityCreator::CreateExplosion(int x, int y)
{
    return std::make_unique<Explosion>(x,y);    
}

std::unique_ptr<Entity> EntityCreator::CreateEagle_base(int x, int y)
{
    return std::make_unique<Eagle_base>(x,y);
}