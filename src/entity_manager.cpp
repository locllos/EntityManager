#include "hdr/entity_manager.h"

Entity** reallocBalls(Entity** entities, size_t old_capacity, size_t new_capacity)
{
    Entity** realloc_entities = new Entity*[new_capacity];

    for (size_t i = 0; i < old_capacity; ++i)
    {
        realloc_entities[i] = entities[i];
    }
    delete[] entities;

    return realloc_entities;
}

EntityManager::EntityManager(size_t capacity)
{
    capacity_ = capacity;
    size_ = 0;
    entities_ = new Entity*[capacity];
}

void EntityManager::addEntity(Entity* Entity)
{
    if (size_ + 1 < capacity_)
    {
        entities_ = reallocBalls(entities_, capacity_, capacity_ * 2);
        capacity_ *= 2;
    }
    entities_[size_++] = Entity;
}

//TODO: переписать на двумерную таблицу виртуальных функций
void EntityManager::processEntities(Display& display, Field& field, float tick)
{
    printf("===============\n");
    // for (size_t i = 0; i < size_; ++i)
    // {   
    //     field.drawFigure(display, entities_[i]);

    //     WALL_COLLISION_TYPE edge_collision = entities_[i]->collisionDetect(field);
    //     if (edge_collision != NO_COLLISION)
    //     {
    //         entities_[i]->collisionResponse(field, edge_collision);
    //     }
    //     for (size_t j = 0; j < size_; ++j)
    //     {
    //         while (entities_[i]->collisionDetect(entities_[j]))
    //         {   
    //             // printf("Entity collision! : %d, %d\n", i, j);
    //             entities_[i]->collisionResponse(entities_[j]);
    //             entities_[i]->coord(entities_[i]->coord() + entities_[i]->velocity() * tick);
    //             entities_[j]->coord(entities_[j]->coord() + entities_[j]->velocity() * tick);
    //             // printf("velocity[%d] = (%lg, %lg)\n", i, entities_[i]->velocity().x, entities_[i]->velocity().y);
    //             // printf("velocity[%d] = (%lg, %lg)\n", j, entities_[j]->velocity().x, entities_[j]->velocity().y);
    //         }
    //     }
    //     entities_[i]->coord(entities_[i]->coord() + entities_[i]->velocity() * tick);
    //     // printf("Entity[%d]: (x, y) = (%lg, %lg)\nvelocity = (%lg, %lg)\n---\n", i, entities_[i]->coord().x, 
    //                                                                             //  entities_[i]->coord().y,
    //                                                                             //  entities_[i]->velocity().x,
    //                                                                             //  entities_[i]->velocity().y);
    // }
}

EntityManager::~EntityManager()
{
    for (size_t i = 0; i < size_; ++i)
    {
        delete entities_[i];
    }
    delete[] entities_;
}