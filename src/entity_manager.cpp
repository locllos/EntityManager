#include "hdr/entity_manager.h"
#include "hdr/array.hpp"


EntityManager::EntityManager() : size_(0), entity_list_() {}

void EntityManager::addEntity(Entity* entity)
{
    entity_list_.Append(entity);
    ++size_;
}

bool isEnoughKineticEnergy(const PhysicalComponent* first, const PhysicalComponent* second)
{
    return (first->getKineticEnergy() + second->getKineticEnergy() > 0);
}

void EntityManager::addFilledCirclePhysCircle(Field& field, Color color, float radius, float mass, Vector2 coord, Vector2 velocity, REACTION_TYPE react_type)
{
    entity_list_.Append(new Entity(new FilledCircle(color), 
                                   new PhysicalCircle(radius, mass, velocity, coord, react_type), field));
}
void EntityManager::addFilledSquarePhysCircle(Field& field, Color color, float length, float mass, Vector2 coord, Vector2 velocity, REACTION_TYPE react_type)
{
    entity_list_.Append(new Entity(new FilledSquare(color), 
                                   new PhysicalCircle(length, mass, velocity, coord, react_type), field));
}

void entityListDump(List<Entity*>& list)
{
    printf("entity dump:\n");
    for (Node<Entity*>* current = list.getHead(); current != nullptr; current = current->next)
    {   
        switch (current->value->phys()->react_type())
        {
            case REACTION_CIRCLE:
            {
                printf("(circle)");
                break;
            }
            case REACTION_SQUARE:
            {
                printf("(square)");
                break;
            }
            default:
            {
                printf("(unknown)");
            }
        }
        printf("%s", current->next != nullptr ? "->" : "|");
    }
    printf("\n");
}

void EntityManager::drawProcessing(Display& display, Field& field)
{
    for (Node<Entity*>* entity = entity_list_.getHead(); 
                        entity != nullptr; entity = entity->next)
    {
        field.drawFigure(display, entity->value);
    }
}

void EntityManager::detectCollisionProcessing(Array<Collision>& collisions, Field& field, float tick)
{
    for (Node<Entity*>* first_node = entity_list_.getHead(); 
                        first_node != nullptr; first_node = first_node->next)
    {
        Entity* first = first_node->value;
        COLLISION_TYPE wall_collision_type = first->phys()->collisionWallDetect(field, tick);
        if (wall_collision_type != NO_COLLISION) 
        {
            collisions.Append({first_node, nullptr, wall_collision_type});
        }
        for (Node<Entity*>* second_node = first_node; 
                            second_node != nullptr; second_node = second_node->next)
        {
            Entity* second = second_node->value;
            bool entity_collision_detect = COLL_DETECT[first->phys()->type()]
                                                      [second->phys()->type()]
                                                      (first->phys(), second->phys(), tick);
            if (entity_collision_detect == true)
            {
                collisions.Append({first_node, second_node, ENTITY_COLLISION});
            }
        }
    }
}

void EntityManager::responseCollisionProcessing(Array<Collision>& collisions, Field& field)
{   
    entityListDump(entity_list_);

    size_t amount_collisions = collisions.size();
    for (size_t i = 0; i < amount_collisions; ++i)
    {
        if (collisions[i].type != ENTITY_COLLISION)
        {   
            collisions[i].first_entity->value->phys()->collisionWallResponse(field, collisions[i].type);
        }
        else 
        {
            PhysicalComponent* first = collisions[i].first_entity->value->phys();
            PhysicalComponent* second = collisions[i].second_entity->value->phys();
            if (!isEnoughKineticEnergy(first, second))
            {
                COLL_RESPONSE[first->type()][second->type()](first, second);
            }
            else
            {
                            REACT_RESPONCE[first->react_type()][second->react_type()]
                                                  (collisions[i].first_entity->value, 
                                                   collisions[i].second_entity->value, field, &entity_list_);
                // entityListDump(entity_list_);
                entity_list_.Delete(collisions[i].first_entity);
                entity_list_.Delete(collisions[i].second_entity);
            }
        }
    }
    entityListDump(entity_list_);

}

void EntityManager::nextMovementProcessing(float tick)
{
    for (Node<Entity*>* entity = entity_list_.getHead(); 
                        entity != nullptr; entity = entity->next)
    {
        entity->value->phys()->nextMovement(tick);
    }
}

void EntityManager::processEntities(Display& display, Field& field, float tick)
{   
    Array<Collision> collisions(size_ / 3);

    drawProcessing(display, field);
    detectCollisionProcessing(collisions, field, tick);
    responseCollisionProcessing(collisions, field);
    nextMovementProcessing(tick);
}

