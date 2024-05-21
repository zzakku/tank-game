#ifndef SRC_TANK_SCENE_H
#define SRC_TANK_SCENE_H

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson/raylib-tileson.h"
#include "entity.h"
//#include "player.h"
//#include "block.h"
//#include "projectile.h"
#include <memory>
#include <vector>

// Уровень рисуем ровно в рамке. Shifth/v - необходимое смещение по координатам.
constexpr int shifth = 16;
constexpr int shiftv = 8;

//std::list<std::unique_ptr<Entity>> actives_; // Список подвижных игровых сущностей (пули/танки)
//std::list<std::unique_ptr<Entity>> walls_; // Список кирпичей лул (орёл сюда же)

// Материал тайла, который нужно загрузить. Nuff said.

enum TileMaterial
{
    brick,
    concrete,
    bush
};

// Создатель - фабрика для создания игровых сущностей

class EntityCreator
{
    private:
    std::vector<Texture2D> textures_;
    public:
    EntityCreator();
    std::unique_ptr<Entity> CreatePlayer(); // new Player(); 
    std::unique_ptr<Entity> CreateWall(TileMaterial material, int x = 0, int y = 0); // Создать блок 8x8 на позиции виртуального полотна (x,y)
    std::unique_ptr<Entity> CreateProjectile(int x = 0, int y = 0, DirectionFacing direction = up);
    std::unique_ptr<Entity> CreateInvisibleWall(int x, int y, bool is_horizontal);
};

/*class EntityCreator
{
    private:
    std::vector<Texture2D> textures_;
    public:
    EntityCreator();
    std::unique_ptr<Entity> CreatePlayer() { return std::make_unique<Player>(); } // new Player(); }
    std::unique_ptr<Entity> CreateWall(TileMaterial material, int x = 0, int y = 0)
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
    std::unique_ptr<Entity> CreateProjectile(int x = 0, int y = 0, DirectionFacing direction = up)
    {
        return std::make_unique<Projectile>(x,y,direction);
    }
}; */

// Обработчик уровней используется сценой для загрузки данных из файла .tmj...
// Честно, не знаю, нужно ли вычленять эту логику из Scene

/*class LevelProcessor
{
    private:
    Map& map_;
    public:
    void ProcessTiles(tson::Layer& layer, RaylibTilesonData* data, Color tint);
    Rectangle RectangleFromTiledRectangle(tson::Rect rect) {
        Rectangle output;
        output.x = rect.x;
        output.y = rect.y;
        output.width = rect.width;
        output.height = rect.height;
        return output;
    }    
};*/

// Менеджер сущностей управляет сущностями во время *игры*, не в меню

class Scene
{
    private:
    std::list<std::unique_ptr<Entity>> actives_; // Список подвижных игровых сущностей (пули/танки)
    std::list<std::unique_ptr<Entity>> walls_; // Список кирпичей лул (орёл сюда же)
    // Возможно, полезно завезти список активных пуль, у них чуть иная логика коллизий с кирпичами (надо отслеживать точку попадания)
    // Ещё надо захардкодить координаты трёх точек спавна врагов и точку спавна игрока
    EntityCreator* creator_;
    void ProcessTiles(tson::Layer& layer, RaylibTilesonData* data);
//    void ProcessSpawns(tson::Layer &layer, RaylibTilesonData* data); Я хотел сделать возможной конфигурацию точек спавна и положения орла из карты, но да ладно
    //std::list<Particle> <Debris?> - для частиц
    public:
    Scene();
    ~Scene();
    void SpawnProjectile(int x = 0, int y = 0, DirectionFacing direction = up);
    void Collide(); // Проверка коллизий для всех активных сущностей
    void Remove(Entity* entity) { delete entity; } // "Вон того убей" <- НАДО ПОДПРАВИТЬ МЕТОД!!!
    void Update(); // Рассчитать состояние игрового поля
    void Draw(); // Отрисовать сущности
    void Clear(); // Выгрузить всё содержимое менеджера сущностей
    void ProcessLevel(Map& map); // Обработать переданную
};

#endif // SRC_TANK_SCENE_H