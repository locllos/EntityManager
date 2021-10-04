#pragma once

#include "entity.h"
#include "field.h"
#include "collision_processor.h"


class EntityManager
{
private:

    List<Entity*> entity_list_;

    size_t size_;
    int amount_circles_;

    void drawProcessing(Display& display, Field& field);
    void detectCollisionProcessing(Array<Collision>& collisions, Field& field, float tick);
    void responseCollisionProcessing(Array<Collision>& collisions, Field& field);
    void nextMovementProcessing(float tick);


public:

    EntityManager();

    void addEntity(Entity* entity);
    void addFilledCirclePhysCircle(Field& field, Color color, float radius, float mass, Vector2 coord, Vector2 velocity, REACTION_TYPE react_type = NO_REACTION);
    void addFilledSquarePhysCircle(Field& field, Color color, float length, float mass, Vector2 coord, Vector2 velocity, REACTION_TYPE react_type = NO_REACTION);
    void processEntities(Display& display, Field& field, float tick);

    int getAmountCircles() const;
    int getAmountSquares() const;

    ~EntityManager() = default;
};