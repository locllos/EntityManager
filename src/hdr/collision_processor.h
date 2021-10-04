#pragma once

#include "list.hpp"
#include "array.hpp"
#include "field.h"
#include "physical_circle.h"
#include "filled_square.h"

struct Collision
{
    Node<Entity*>* first_entity  = nullptr;
    Node<Entity*>* second_entity = nullptr;

    COLLISION_TYPE type = NO_COLLISION;

};

const float KINETIC_ENERGY_THRESHOLD = 1;

typedef bool (*CollisionDetect)  (PhysicalComponent*, PhysicalComponent*, float tick);
typedef void (*CollisionResponce)(PhysicalComponent*, PhysicalComponent*);
typedef void (*ReactionResponce) (Entity*, Entity*, Field&, List<Entity*>* list, int& amount_circles);

// detect::
bool detectPhysCirclePhysCircle(PhysicalCircle* first, PhysicalCircle* second, float tick);


const CollisionDetect COLL_DETECT[AMOUNT_PHYSICAL_COMPONENTS][AMOUNT_PHYSICAL_COMPONENTS] = 
{
    {(CollisionDetect)detectPhysCirclePhysCircle},
};

// response::
void collisionPhysCirclePhysCircle(PhysicalCircle* first, PhysicalCircle* second);

const CollisionResponce COLL_RESPONSE[AMOUNT_PHYSICAL_COMPONENTS][AMOUNT_PHYSICAL_COMPONENTS] = 
{
    (CollisionResponce)collisionPhysCirclePhysCircle,
};

// reaction::
void reactionCircleCircle(Entity* first, Entity* second, Field& field, List<Entity*>* list, int& amount_circles);
void reactionCircleSquare(Entity* first, Entity* second, Field& field, List<Entity*>* list, int& amount_circles);
void reactionSquareCircle(Entity* first, Entity* second, Field& field, List<Entity*>* list, int& amount_circles);
void reactionSquareSquare(Entity* first, Entity* second, Field& field, List<Entity*>* list, int& amount_circles);

const ReactionResponce REACT_RESPONCE[AMOUNT_REACTION_TYPES][AMOUNT_REACTION_TYPES] = 
{
    {(ReactionResponce)reactionCircleCircle, (ReactionResponce)reactionCircleSquare},
    {(ReactionResponce)reactionSquareCircle, (ReactionResponce)reactionSquareSquare},
};


