#pragma once

#include "vector.h"

struct PixelPoint;
class PhysicalComponent;
class Field;

enum GRAPHICAL_TYPE
{
    NO_GRAPHIC, 

    FILLED_CIRCLE,
    FILLED_SQUARE,

    AMOUNT_GRAPHICAL_COMPONENTS,
};

enum PHYSICAL_TYPE
{
    NO_PHYSIC, 

    PHYSICAL_CIRCLE,

    AMOUNT_PHYSICAL_COMPONENTS,
};

//TODO: двумерную таблицу виртуальных функций взаимодействий физических и графический компонент

class GraphicalComponent
{
protected:

    GRAPHICAL_TYPE type_;

public:

    GraphicalComponent() = default;

    virtual void Draw(Display& display) = 0;
    virtual void Move(PixelPoint pixelpoint) = 0;

    GRAPHICAL_TYPE type() {return type_;}

    virtual ~GraphicalComponent() = default;
    
};

class PhysicalComponent
{
protected:

    PHYSICAL_TYPE type_;

public:
    
    Vector2 coord;

public:

    PhysicalComponent() = default;    

    virtual void nextMovement(float tick) = 0;

    PHYSICAL_TYPE type() {return type_;}

    virtual ~PhysicalComponent() = default;
};

class Entity
{
private:

    GraphicalComponent* graphical_component_;
    PhysicalComponent* physical_component_;

    void connectComponents(const Field& field);

public:

    Entity() = delete;

    Entity(GraphicalComponent* graph_comp, PhysicalComponent* phys_comp, const Field& field);

    GraphicalComponent* graphical_component();
    PhysicalComponent* physical_component();

    ~Entity();
};