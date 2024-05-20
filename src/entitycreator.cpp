#include "scene.h"
#include "player.h"
#include "block.h"
#include "projectile.h"

std::unique_ptr<Entity> EntityCreator::CreatePlayer() { return std::make_unique<Player>(); } // new Player(); }
std::unique_ptr<Entity> EntityCreator::CreateWall(TileMaterial material, int x, int y)
    {
        switch(material)
        {
            case brick:
            return std::make_unique<Block>(x, y);
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