#pragma once

#include "entity.h"
#include "physical_circle.h"
#include "filled_circle.h"

class FilledSquare;

typedef void (*connectComponents)(PhysicalComponent*, GraphicalComponent*, const Field&);


void connectPhysCircleFilledCircle(PhysicalCircle* phys_circle, FilledCircle* graph_circle, const Field& field);
void connectPhysCircleFilledSquare(PhysicalCircle* phys_circle, FilledSquare* graph_square, const Field& field);

const connectComponents COMPONENT_CONNECTORS[AMOUNT_PHYSICAL_COMPONENTS - 1][AMOUNT_GRAPHICAL_COMPONENTS - 1] = 
{
    {(connectComponents)connectPhysCircleFilledCircle, (connectComponents)connectPhysCircleFilledSquare},
};
