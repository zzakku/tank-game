#ifndef TANK_SRC_OBJECT_H_
#define TANK_SRC_OBJECT_H_

#include <raylib.h>
#include <list>
#include <stdint.h>

// От Entity наследуются все объекты, существующие во время игрового процесса

// Перечень ID: 1 - игрок, 2 - кирпич, 3 - бетон, 4 - куст, 5 - пуля, 6 - невидимая стена, 7 - пуля

// Это если какой-то сущности потребуется иметь данные о том, куда что-либо смотрит

enum DirectionFacing
{
    up,
    down,
    left,
    right
};

class Scene; // См. "Scene.h"
 
class Entity
{
    protected:
    Scene* scene_ = nullptr; // Каждая сущность знает сцену, из которой она происходит
    Rectangle hitbox_; // Надо определиться, совпадает ли хитбокс с прямоугольником отрисовки
    Vector2 pos_;
    bool fliph_; // Флаг "объект отражён по горизонтали"
    bool flipv_; // Флаг "объект отражён по вертикали"
    uint8_t id_; // ID объекта
    // Подтип?
    bool destroyable_ = false; // Флаг "данную сущность можно уничтожить"
    public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    uint8_t GetID() { return id_; }
    Rectangle GetCollision() { return hitbox_; }
    bool CheckVitalSigns() { return destroyable_; } // Проверить, жива ли сущность 
    virtual void OnCollision(uint8_t other_id) = 0; // В эту функцию менеджер объектов передаёт объект, коллизию с которым необходимо обработать
    void SetScene(Scene* scene) { scene_ = scene; };
//    uint8_t RequestSpawn(uint8_t id, int x, int y, DirectionFacing direction) {return }
};

#endif // TANK_SRC_OBJECT_H_