#include "hdr/collision_processor.h"

float getChangedVelocityProjection(float this_mass, float this_velocity, 
                                   float other_mass, float other_velocity)
{
    return (this_velocity * (this_mass - other_mass) - 2 * other_mass * other_velocity) 
                                                     /
                                          (this_mass + other_mass);
}


WALL_COLLISION_TYPE collisionDetect(const PhysicalCircle* self, const Field& field)
{
    if (!field.isWithin(field.coord_system().getAbsolute(self->coord + Vector2(self->radius, 0))))
    {
        return COLLISION_LEFT;
    }
    if (!field.isWithin(field.coord_system().getAbsolute(self->coord + Vector2((-1) * self->radius, 0))))
    {
        return COLLISION_RIGHT;
    }
    if (!field.isWithin(field.coord_system().getAbsolute(self->coord + Vector2(0, self->radius))))
    {
        return COLLISION_UP;
    }
    if (!field.isWithin(field.coord_system().getAbsolute(self->coord + Vector2(0, (-1) * self->radius))))
    {
        return COLLISION_DOWN;
    }
    return NO_COLLISION;
}

// bool PhysicalCircle::collisionDetect(const PhysicalCircle* other) const
// {
//     if (this == other) return false;

//     Vector2 collision_vector = this->coord_ - other->coord_;
//     float collision_distance = collision_vector.getLength();

//     return (collision_distance <= this->radius_ + other->radius_);
// }

// void PhysicalCircle::collisionResponse(PhysicalCircle* other)
// {
//     Vector2 normal_vector = this->coord_ - other->coord_;
//     normal_vector.Normalize();

//     Vector2 tangential_vector((-1) * normal_vector.y, normal_vector.y);

//     float this_tan_velocity  = this->velocity_  * tangential_vector; 
//     float other_tan_velocity = other->velocity_ * tangential_vector;

//     float this_normal_velocity  = this->velocity_  * normal_vector;
//     float other_normal_velocity = other->velocity_ * normal_vector;

//     float upd_this_normal_velocity  = getChangedVelocityProjection(this->mass_, this_normal_velocity, 
//                                                                    other->mass_, other_normal_velocity);
//     float upd_other_normal_velocity = getChangedVelocityProjection(other->mass_, other_normal_velocity, 
//                                                                    this->mass_, this_normal_velocity);
    
//     this->velocity_ = normal_vector * upd_this_normal_velocity * (-1) + tangential_vector * this_tan_velocity;
//     other->velocity_ = normal_vector * upd_other_normal_velocity  + tangential_vector * other_tan_velocity;
// }


// void PhysicalCircle::collisionResponse(const Field& field, COLLISION_TYPE collision_type)
// {   
//     int x_factor_velocity = 1;
//     int y_factor_velocity = 1;
    
//     if (collision_type == COLLISION_UP || collision_type == COLLISION_DOWN)
//     {
//         y_factor_velocity = -1;
//     }
//     else if (collision_type == COLLISION_LEFT || collision_type == COLLISION_RIGHT)
//     {
//         x_factor_velocity = -1;
//     }
//     velocity_.mulXY(x_factor_velocity, y_factor_velocity);
// }
