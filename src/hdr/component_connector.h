#pragma once

#include "entity.h"
#include "physical_circle.h"
#include "filled_circle.h"
#include "filled_square.h"

typedef void (*connectComponents)(PhysicalComponent*, GraphicalComponent*, Field&);


void connectPhysCircleFilledCircle(PhysicalCircle* phys_circle, FilledCircle* graph_circle, Field& field);
void connectPhysCircleFilledSquare(PhysicalCircle* phys_circle, FilledSquare* graph_square, Field& field);

const connectComponents COMPONENT_CONNECTORS[AMOUNT_PHYSICAL_COMPONENTS][AMOUNT_GRAPHICAL_COMPONENTS] = 
{
    {(connectComponents)connectPhysCircleFilledCircle, (connectComponents)connectPhysCircleFilledSquare},
};
