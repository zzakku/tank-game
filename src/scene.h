#ifndef SRC_TANK_SCENE_H
#define SRC_TANK_SCENE_H

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson/raylib-tileson.h"
#include "entity.h"
#include <memory>
#include <vector>

// Уровень рисуем ровно в рамке. Shifth/v - необходимое смещение по координатам.
constexpr int shifth = 16;
constexpr int shiftv = 8;

// Материал тайла, который нужно загрузить. Nuff said. (НЕ ПОЛЬЗОВАТЬСЯ ЭТИМ ДЛЯ СОЗДАНИЯ КИРПИЧЕЙ!)

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
    std::unique_ptr<Entity> CreatePlayer();
    std::unique_ptr<Entity> CreateEnemy();
    std::unique_ptr<Entity> CreateBrickWall(int x = 0, int y = 0, uint8_t corner = 0); 
    std::unique_ptr<Entity> CreateOtherWall(TileMaterial material, int x = 0, int y = 0); // Создать блок 8x8 на позиции виртуального полотна (x,y)
    std::unique_ptr<Entity> CreateProjectile(int x = 0, int y = 0, DirectionFacing direction = up);
    std::unique_ptr<Entity> CreateInvisibleWall(int x, int y, bool is_horizontal);
    std::unique_ptr<Entity> CreateExplosion(int x, int y);
    std::unique_ptr<Entity> CreateEagle_base(int x, int y);

};

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
    std::list<std::unique_ptr<Entity>> explosions_; // Список взрывов (ну да...)
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
    void SpawnExplosion(int x = 0, int y = 0);
    void Collide(); // Проверка коллизий для всех активных сущностей
    void Remove(Entity* entity) { delete entity; } // "Вон того убей" <- НАДО ПОДПРАВИТЬ МЕТОД!!!
    void Update(); // Рассчитать состояние игрового поля
    void Draw(); // Отрисовать сущности
    void Clear(); // Выгрузить всё содержимое менеджера сущностей
    void ProcessLevel(Map& map); // Обработать переданную

    std::list<std::unique_ptr<Entity>>& getActives() {return actives_;}
};

#endif // SRC_TANK_SCENE_H