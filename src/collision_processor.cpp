#include "hdr/collision_processor.h"

const float PI = 3.14159265359;

float getChangedVelocityProjection(float this_mass, float this_velocity, 
                                   float other_mass, float other_velocity)
{
    return (this_velocity * (this_mass - other_mass) - 2 * other_mass * other_velocity) 
                                                     /
                                          (this_mass + other_mass);
}

Color getMixedColor(Color first, float first_ratio, 
                    Color second, float second_ratio)
{
    return Color((first.red   * first_ratio + second.red   * second_ratio), 
                 (first.green * first_ratio + second.green * second_ratio),
                 (first.blue  * first_ratio + second.blue  * second_ratio),
                 (first.alpha * first_ratio + second.alpha * second_ratio));
}

float getFloatRand(size_t accuracy)
{
    return (rand() % accuracy) / accuracy;
}

// detect::
bool detectPhysCirclePhysCircle(PhysicalCircle* first, PhysicalCircle* second, float tick)
{   
    if (first->was_collide || second->was_collide) return false;

    if (first == second) return false;

    Vector2 next_coord_first  = first->getNextMovement(tick);
    Vector2 next_coord_second = second->getNextMovement(tick);

    Vector2 collision_vector = next_coord_first - next_coord_second;
    float collision_distance = collision_vector.getLength();

    if (collision_distance <= first->radius + second->radius)
    {
        first->was_collide = true;
        second->was_collide = true;
        return true;
    }

    return false;
}

// collision::
void collisionPhysCirclePhysCircle(PhysicalCircle* first, PhysicalCircle* second)
{
    Vector2 normal_vector = first->coord - second->coord;
    normal_vector.Normalize();

    Vector2 tangential_vector((-1) * normal_vector.y, normal_vector.x);

    float this_tan_velocity  = first->velocity  * tangential_vector; 
    float other_tan_velocity = second->velocity * tangential_vector;

    float this_normal_velocity  = first->velocity  * normal_vector;
    float other_normal_velocity = second->velocity * normal_vector;

    float upd_this_normal_velocity  = getChangedVelocityProjection(first->mass, this_normal_velocity, 
                                                                   second->mass, other_normal_velocity);
    float upd_other_normal_velocity = getChangedVelocityProjection(second->mass, other_normal_velocity, 
                                                                   first->mass, this_normal_velocity);
    
    first->velocity  = normal_vector * upd_this_normal_velocity + tangential_vector * this_tan_velocity;
    second->velocity = normal_vector * upd_other_normal_velocity * (-1) + tangential_vector * other_tan_velocity;
}


// reaction::

void reactionCircleCircle(Entity* first, Entity* second, const Field& field, List<Entity*>* list)
{
    // List<Entity*>* entity_list = new List<Entity*>();

    PhysicalCircle* first_phys  = (PhysicalCircle*)first->phys();
    PhysicalCircle* second_phys = (PhysicalCircle*)second->phys(); 

    Vector2 result_coord = (first_phys->coord + second_phys->coord) * 0.5;
    Vector2 normal_vector = first_phys->coord - second_phys->coord;
    normal_vector.Normalize();

    float result_mass = first_phys->mass + second_phys->mass;
    float first_mass_ratio = first_phys->mass / result_mass;
    float second_mass_ratio = second_phys->mass / result_mass;
    Vector2 result_velocity = (first_phys->velocity * first_phys->mass - second_phys->velocity * second_phys->mass) * (1 
                                                                       /
                                                                  result_mass);

    Color result_color = getMixedColor(first->graph()->color, first_mass_ratio,
                                       second->graph()->color, second_mass_ratio);
    float result_radius = (first_phys->radius + second_phys->radius);

    list->Append(new Entity((GraphicalComponent*)(new FilledSquare(result_color)), 
                            (PhysicalComponent*) (new PhysicalCircle(result_radius, result_mass, result_velocity, result_coord, REACTION_SQUARE)), field));
    // return entity_list;
}


void reactionCircleSquare(Entity* first, Entity* second, const Field& field, List<Entity*>* list)
{
    // List<Entity*>* entity_list = new List<Entity*>();

    PhysicalCircle* first_phys  = (PhysicalCircle*)first->phys();
    PhysicalCircle* second_phys = (PhysicalCircle*)second->phys(); 

    Vector2 result_coord = second_phys->coord;
    Vector2 normal_vector = first_phys->coord - second_phys->coord;
    normal_vector.Normalize();

    float result_mass = first_phys->mass + second_phys->mass;
    float first_mass_ratio = first_phys->mass / result_mass;
    float second_mass_ratio = second_phys->mass / result_mass;
    Vector2 result_velocity = (first_phys->velocity * first_mass_ratio - second_phys->velocity * second_mass_ratio);

    Color result_color = getMixedColor(first->graph()->color, first_mass_ratio,
                                       second->graph()->color, second_mass_ratio);
    float result_radius = first_phys->radius / 4 + second_phys->radius;

    list->Append(new Entity((GraphicalComponent*)(new FilledSquare(result_color)), 
                            (PhysicalComponent*) (new PhysicalCircle(result_radius, result_mass, result_velocity, result_coord, REACTION_SQUARE)), field));
    // return entity_list;
}

void reactionSquareCircle(Entity* first, Entity* second, const Field& field, List<Entity*>* list)
{
    /*return*/ reactionCircleSquare(second, first, field, list);
}

void reactionSquareSquare(Entity* first, Entity* second, const Field& field, List<Entity*>* list)
{
    // List<Entity*>* entity_list = new List<Entity*>();

    PhysicalCircle* first_phys  = (PhysicalCircle*)first->phys();
    PhysicalCircle* second_phys = (PhysicalCircle*)second->phys();

    Vector2 direction = getRandomDirection();
    Vector2 result_coord = (first_phys->coord + second_phys->coord) * 0.5;
    float result_mass = first_phys->mass + second_phys->mass;
    size_t amount_balls = result_mass + 0.5; // in real life usually 2 balls, but this is a model
    float result_radius = 1;
    float rotatable_angle = 2 * PI / amount_balls;
    float velocity_coeff = ((first_phys->velocity   * first_phys->mass - 
                              second_phys->velocity * second_phys->mass) * (1 / (float)amount_balls)).getLength();


    Color result_color = getMixedColor(first->graph()->color, first_phys->mass / result_mass,
                                       second->graph()->color, second_phys->mass / result_mass);
    
    float current_angle = direction.getAngle();
    for (size_t i = 0; i < amount_balls; ++i)
    {   
        PhysicalComponent* new_phys_comp = new PhysicalCircle(result_radius, 
                                                              1, 
                                                              direction * velocity_coeff, 
                                                              result_coord + direction * 2, 
                                                              REACTION_CIRCLE);
        GraphicalComponent* new_graph_comp = new FilledCircle(result_color);
        list->Append(new Entity(new_graph_comp, new_phys_comp, field));
        
        direction.Rotate(current_angle);
        current_angle += rotatable_angle;
    }
    // return entity_list;
}


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


// void collisionResponse(Phyconst Field& field, COLLISION_TYPE collision_type)
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
