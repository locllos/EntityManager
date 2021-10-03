#include "hdr/collision_processor.h"

PhysicalCircle::PhysicalCircle()
{
    type_ = PHYSICAL_CIRCLE;
    was_collide = false;
}

PhysicalCircle::PhysicalCircle(float init_radius, float init_mass, Vector2 init_velocity, Vector2 init_coord, REACTION_TYPE react_type) : radius(init_radius), mass(init_mass), velocity(init_velocity) 
{
    coord = init_coord; 
    type_ = PHYSICAL_CIRCLE;
    was_collide = false;
    react_type_ = react_type;
}
 
Vector2 PhysicalCircle::getNextMovement(float tick) const
{
    return coord + velocity * tick;
}


void PhysicalCircle::nextMovement(float tick)
{
    coord += velocity * tick;
}

float PhysicalCircle::getKineticEnergy() const
{
    return 0.5 * mass * (velocity * velocity);
}

COLLISION_TYPE PhysicalCircle::collisionWallDetect(const Field& field, float tick)
{
    if (!field.isWithin(field.coord_system().getAbsolute(this->coord + Vector2(this->radius, 0))))
    {
        return WALL_COLLISION_LEFT;
    }
    if (!field.isWithin(field.coord_system().getAbsolute(this->coord + Vector2((-1) * this->radius, 0))))
    {
        return WALL_COLLISION_RIGHT;
    }
    if (!field.isWithin(field.coord_system().getAbsolute(this->coord + Vector2(0, this->radius))))
    {
        return WALL_COLLISION_UP;
    }
    if (!field.isWithin(field.coord_system().getAbsolute(this->coord + Vector2(0, (-1) * this->radius))))
    {
        return WALL_COLLISION_DOWN;
    }
    return NO_COLLISION;
}

void PhysicalCircle::collisionWallResponse(const Field& field, COLLISION_TYPE collision_type)
{
    int x_factor_velocity = 1;
    int y_factor_velocity = 1;
    
    if (collision_type == WALL_COLLISION_UP || collision_type == WALL_COLLISION_DOWN)
    {
        y_factor_velocity = -1;
    }
    else if (collision_type == WALL_COLLISION_LEFT || collision_type == WALL_COLLISION_RIGHT)
    {
        x_factor_velocity = -1;
    }
    velocity.mulXY(x_factor_velocity, y_factor_velocity);
}
