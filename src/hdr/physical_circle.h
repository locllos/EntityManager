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
    PhysicalCircle(float init_radius, float init_mass, Vector2 init_velocity, Vector2 init_coord); 
    
    void nextMovement(float tick) override;

    virtual ~PhysicalCircle() = default;
};