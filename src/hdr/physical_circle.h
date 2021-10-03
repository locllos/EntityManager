#pragma once

#include "field.h"
#include "entity.h"
#include "filled_circle.h"

class FilledRectangle;

class PhysicalCircle : public PhysicalComponent
{
public:

    float radius;
    float mass;
    Vector2 velocity;

public:

    PhysicalCircle();
    PhysicalCircle(float init_radius, float init_mass, Vector2 init_velocity, Vector2 init_coord, REACTION_TYPE react_type = NO_REACTION); 
    
    void nextMovement(float tick) override;
    Vector2 getNextMovement(float tick) const override;

    float getKineticEnergy() const override;

    COLLISION_TYPE collisionWallDetect(const Field& field, float tick) override;
    void collisionWallResponse(const Field& field, COLLISION_TYPE collision_type) override;

    virtual ~PhysicalCircle() = default;
};