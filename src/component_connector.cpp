#include "hdr/component_connector.h"

void connectPhysCircleFilledCircle(PhysicalCircle* phys_circle, FilledCircle* graph_circle, const Field& field)
{
    graph_circle->pixel_radius = (float)phys_circle->radius * field.coord_system().scale();

    graph_circle->position = field.coord_system().getAbsolute(phys_circle->coord);
}

void connectPhysCircleFilledSquare(PhysicalCircle* phys_circle, FilledSquare* graph_square, const Field& field)
{
    graph_square->pixel_length = 2 * (float)phys_circle->radius * field.coord_system().scale();

    graph_square->position = field.coord_system().getAbsolute(phys_circle->coord);
}