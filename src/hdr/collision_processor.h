#include "field.h"
#include "physical_circle.h"

enum WALL_COLLISION_TYPE
{
    NO_COLLISION = 0,
    COLLISION_LEFT,
    COLLISION_RIGHT,
    COLLISION_UP,
    COLLISION_DOWN,
};


WALL_COLLISION_TYPE collisionDetect(const PhysicalComponent* phys_comp, const Field& field);
bool collisionDetect(const PhysicalCircle* self, const PhysicalCircle* other);

void collisionResponse(PhysicalComponent* phys_comp, const Field& field, WALL_COLLISION_TYPE collision_type);
void collisionResponse(PhysicalCircle* self, PhysicalCircle* other); 