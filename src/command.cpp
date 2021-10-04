#include "hdr/command.h"

SpawnCircle::SpawnCircle(EntityManager* manager, Field* field) : manager_(manager), field_(field) {}

void SpawnCircle::Execute()
{   
    printf("spawn circle!\n");
    manager_->addFilledCirclePhysCircle(*field_, getRandomColor(), 1, 1, 
                                                 {rand() % 20 - 10, rand() % 20 - 10}, 
                                                 getRandomDirection() * (rand() % 200), 
                                                 REACTION_CIRCLE);

}

SpawnCircle::~SpawnCircle()
{
    manager_ = nullptr;
    field_ = nullptr;
}

SpawnSquare::SpawnSquare(EntityManager* manager, Field* field) : manager_(manager), field_(field) {}

void SpawnSquare::Execute()
{   
    printf("spawn square!\n");
    manager_->addFilledSquarePhysCircle(*field_, getRandomColor(), 2, 1, 
                                                 {rand() % 20 - 10, rand() % 20 - 10}, 
                                                 getRandomDirection() * (rand() % 200 + 200), 
                                                 REACTION_SQUARE);
}

SpawnSquare::~SpawnSquare()
{
    manager_ = nullptr;
    field_ = nullptr;
}