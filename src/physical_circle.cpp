#include "hdr/physical_circle.h"

PhysicalCircle::PhysicalCircle()
{
    type_ = PHYSICAL_CIRCLE;
}

PhysicalCircle::PhysicalCircle(float init_radius, float init_mass, Vector2 init_velocity, Vector2 init_coord) : radius(init_radius), mass(init_mass), velocity(init_velocity) 
{
    coord = init_coord; 
    type_ = PHYSICAL_CIRCLE;
}
 

void PhysicalCircle::nextMovement(float tick)
{
    coord += velocity * tick;
}