#include "scene.h"

Scene::Scene()
{
    walls_.insert(walls_.begin(), creator_->CreateInvisibleWall(0.0f,-3.0f,true)); //верхняя стена
    walls_.insert(walls_.begin(), creator_->CreateInvisibleWall(-4.0f,0.0f,false)); //левая стена
    walls_.insert(walls_.begin(), creator_->CreateInvisibleWall(0.0f,224.0f,true)); //нижняя стена
    walls_.insert(walls_.begin(), creator_->CreateInvisibleWall(223.0f,0.0f,false)); //правая стена

    walls_.insert(walls_.begin(), creator_->CreateEagle_base(96.0f, 208.0f));

    actives_.insert(actives_.begin(), creator_->CreatePlayer());
    (*actives_.begin())->SetScene(this);
}

Scene::~Scene()
{
/*    std::list<Entity*>::iterator iter = entitylist_.begin();

    for (iter = entitylist_.begin(); iter != entitylist_.end(); iter++)
    {
        delete *iter;
//        entitylist_.erase(iter); 
    }*/
}

void Scene::Clear()
{
    actives_.clear();
    walls_.clear();
}

void Scene::SpawnProjectile(int x, int y, DirectionFacing direction)
{
    actives_.insert(actives_.begin(), creator_->CreateProjectile(x,y,direction));

//    std::list<std::unique_ptr<Entity>>::iterator iter = actives_.begin();   

    (*actives_.begin())->SetScene(this);
}

void Scene::SpawnExplosion(int x, int y)
{
    explosions_.insert(explosions_.begin(), creator_->CreateExplosion(x,y));

    (*explosions_.begin())->SetScene(this);    
}

void Scene::Collide()
{
    for (std::list<std::unique_ptr<Entity>>::iterator iter1 = actives_.begin(); iter1 != actives_.end(); iter1++)
    {
        for (std::list<std::unique_ptr<Entity>>::iterator iter2 = walls_.begin(); iter2 != walls_.end(); iter2++)
        {
            if (CheckCollisionRecs((*iter1)->GetCollision(), (*iter2)->GetCollision()))
            {
                (*iter1)->OnCollision((*iter2)->GetID());
                (*iter2)->OnCollision((*iter1)->GetID());
            }            
        }
    }

    for (std::list<std::unique_ptr<Entity>>::iterator iter1 = actives_.begin(); iter1 != actives_.end(); iter1++)
    {
        for (std::list<std::unique_ptr<Entity>>::iterator iter2 = actives_.begin(); iter2 != actives_.end(); iter2++)
        {
            if (iter1 != iter2)
            {
                if (CheckCollisionRecs((*iter1)->GetCollision(), (*iter2)->GetCollision()))
                {
                    (*iter1)->OnCollision((*iter2)->GetID());
                    (*iter2)->OnCollision((*iter1)->GetID());
                } 
            }           
        }
    }
}

void Scene::Update()
{
    std::list<std::unique_ptr<Entity>>::iterator iter = actives_.begin();

    for (iter = actives_.begin(); iter != actives_.end(); iter++)
    {
        (*iter)->Update();
    }

    Collide(); 

    for (iter = explosions_.begin(); iter != explosions_.end(); iter++)
    {
        (*iter)->Update();
    }    

    iter = actives_.begin();

    while (iter != actives_.end()) { 
        auto next = std::next(iter); 
        if ((*iter)->CheckVitalSigns()) { 
          actives_.erase(iter); 
        } 
        iter = next; 
    } 

    iter = walls_.begin();

    while (iter != walls_.end()) { 
        auto next = std::next(iter); 
        if ((*iter)->CheckVitalSigns()) { 
          walls_.erase(iter); 
        } 
        iter = next; 
    } 

    iter = explosions_.begin();

    while (iter != explosions_.end()) { 
        auto next = std::next(iter); 
        if ((*iter)->CheckVitalSigns()) { 
          explosions_.erase(iter); 
        } 
        iter = next; 
    } 
}

void Scene::Draw()
{
    std::list<std::unique_ptr<Entity>>::iterator iter = actives_.begin();   

    iter = actives_.begin();

    for (iter = actives_.begin(); iter != actives_.end(); iter++)
    {
        (*iter)->Draw();
    }

    iter = walls_.begin();

    for (iter = walls_.begin(); iter != walls_.end(); iter++)
    {
        (*iter)->Draw();
    }

    for (iter = explosions_.begin(); iter != explosions_.end(); iter++)
    {
        (*iter)->Draw();
    }
}

void Scene::ProcessLevel(Map& map)
{
    RaylibTilesonData* data = (RaylibTilesonData*)map.data;
    if (data == NULL) {
        TraceLog(LOG_WARNING, "TILESON: Cannot draw empty map");
        return;
    }
    if (map.width != 13 || map.height != 13)
    {
        TraceLog(LOG_WARNING, "SCENE: Cannot take levels with dimensions other than 13x13!");
        return;
    }

    tson::Map* tsonMap = data->map;
    auto &layers = tsonMap->getLayers();

    for (auto &layer : layers) {
        switch (layer.getType()) {
        case tson::LayerType::TileLayer:
            ProcessTiles(layer, data);
            break;

        case tson::LayerType::ObjectGroup:
//            ProcessSpawns(layer, data);
            TraceLog(LOG_TRACE, "SCENE: Object layers not supported");
            break;

        case tson::LayerType::ImageLayer:
//            DrawImageLayer(layer, data, posX, posY, tint);
            TraceLog(LOG_TRACE, "SCENE: Image layers not supported");
            break;

        default:
            TraceLog(LOG_TRACE, "TILESON: Unsupported layer type");
            break;
    }
    }
}

void Scene::ProcessTiles(tson::Layer& layer, RaylibTilesonData* data)
{
    for (auto& [pos, tileObject] : layer.getTileObjects()) {
        const tson::Tileset *tileset = tileObject.getTile()->getTileset();
//        std::string image = tileset->getImage().string(); // Находит путь к файлу с тайлсетом
//        if (data->textures.count(image) == 0) {
//            continue;
//            TraceLog(LOG_TRACE, "Now where is my pipe? GARFIEEELD!!!");
//        }

        tson::Vector2f position = tileObject.getPosition();
        position.x += shifth;
        position.y += shiftv;
        uint32_t tileid = tileObject.getTile()->getId();

        TileMaterial tilematerial;

        if (tileid >= 1 && tileid <= 5)
        {
            tilematerial = brick;
        }
        else if (tileid >= 6 && tileid <= 10)
        {
            tilematerial = concrete;
        }
        else if (tileid >= 11 && tileid <= 15)
        {
            tilematerial = bush;
        }
        else
        {
            TraceLog(LOG_TRACE, "Unknown kind of tile in passed tilemap");
            return;
        }

        // Массив corners говорит о том, какие углы у блока есть
        // -----
        // |0|1|
        // |2|3|
        // -----

        bool corners[4] = {false, false, false, false};

        switch (tileid)
        {
            case 1: case 6: case 11:
            corners[0] = true;
            corners[1] = true;
            corners[2] = true;
            corners[3] = true;
            break;
            case 2: case 7: case 12:
            corners[1] = true;
            corners[3] = true;
            break;
            case 3: case 8: case 13:
            corners[2] = true;
            corners[3] = true;
            break;
            case 4: case 9: case 14:
            corners[0] = true;
            corners[2] = true;
            break;
            case 5: case 10: case 15:
            corners[0] = true;
            corners[1] = true;
            break;
            default:
            break;
        }

        if (corners[0])
        {
            if (tilematerial == brick)
            {
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x, position.y + 8, 0));
                (*walls_.begin())->SetScene(this);      
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 4, position.y + 8, 1));
                (*walls_.begin())->SetScene(this); 
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x, position.y + 8 + 4, 2));
                (*walls_.begin())->SetScene(this); 
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 4, position.y + 8 + 4, 3));
                (*walls_.begin())->SetScene(this);           
            }
            else
            {
                walls_.insert(walls_.begin(), creator_->CreateOtherWall(tilematerial, position.x, position.y + 8));
                (*walls_.begin())->SetScene(this);
            }
        }
        if (corners[1])
        {
            if (tilematerial == brick)
            {
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 8, position.y + 8, 0));
                (*walls_.begin())->SetScene(this);      
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 8 + 4, position.y + 8, 1));
                (*walls_.begin())->SetScene(this); 
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 8, position.y + 8 + 4, 2));
                (*walls_.begin())->SetScene(this); 
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 8 + 4, position.y + 8 + 4, 3));
                (*walls_.begin())->SetScene(this);           
            }
            else
            {
                walls_.insert(walls_.begin(), creator_->CreateOtherWall(tilematerial, position.x + 8, position.y + 8));
                (*walls_.begin())->SetScene(this);
            }
//            walls_.insert(walls_.begin(), creator_->CreateWall(tilematerial, position.x + 8, position.y + 8));
//            (*walls_.begin())->SetScene(this);
        }
        if (corners[2])
        {
            if (tilematerial == brick)
            {
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x, position.y + 8 + 8, 0));
                (*walls_.begin())->SetScene(this);      
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 4, position.y + 8 + 8, 1));
                (*walls_.begin())->SetScene(this); 
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x, position.y + 8 + 8 + 4, 2));
                (*walls_.begin())->SetScene(this); 
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 4, position.y + 8 + 8 + 4, 3));
                (*walls_.begin())->SetScene(this);           
            }
            else
            {
                walls_.insert(walls_.begin(), creator_->CreateOtherWall(tilematerial, position.x, position.y + 8 + 8));
                (*walls_.begin())->SetScene(this);
            }
//            walls_.insert(walls_.begin(), creator_->CreateWall(tilematerial, position.x, position.y + 8 + 8));
//            (*walls_.begin())->SetScene(this);
        }
        if (corners[3])
        {
            if (tilematerial == brick)
            {
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 8, position.y + 8 + 8, 0));
                (*walls_.begin())->SetScene(this);      
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 8 + 4, position.y + 8 + 8, 1));
                (*walls_.begin())->SetScene(this); 
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 8, position.y + 8 + 8 + 4, 2));
                (*walls_.begin())->SetScene(this); 
                walls_.insert(walls_.begin(), creator_->CreateBrickWall(position.x + 8 + 4, position.y + 8 + 8 + 4, 3));
                (*walls_.begin())->SetScene(this);           
            }
            else
            {
                walls_.insert(walls_.begin(), creator_->CreateOtherWall(tilematerial, position.x + 8, position.y + 8 + 8));
                (*walls_.begin())->SetScene(this);
            }
//            walls_.insert(walls_.begin(), creator_->CreateWall(tilematerial, position.x + 8, position.y + 8 + 8));
//            (*walls_.begin())->SetScene(this);
        }
    }   
}