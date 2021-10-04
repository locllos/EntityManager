#pragma once

#include "vector.h"
#include "display.h"

class PhysicalComponent;
class Field;

enum COLLISION_TYPE
{
    NO_COLLISION = 0,
    WALL_COLLISION_LEFT,
    WALL_COLLISION_RIGHT,
    WALL_COLLISION_UP,
    WALL_COLLISION_DOWN,

    ENTITY_COLLISION,

    AMOUNT_COLLISIONS
};


enum GRAPHICAL_TYPE
{

    FILLED_CIRCLE,
    FILLED_SQUARE,

    AMOUNT_GRAPHICAL_COMPONENTS,
    NO_GRAPHIC, 
};

enum PHYSICAL_TYPE
{

    PHYSICAL_CIRCLE,

    AMOUNT_PHYSICAL_COMPONENTS,
    NO_PHYSIC, 
};

enum REACTION_TYPE
{
    REACTION_CIRCLE,
    REACTION_SQUARE,

    AMOUNT_REACTION_TYPES,
    NO_REACTION, 
};

class GraphicalComponent
{
protected:

    GRAPHICAL_TYPE type_;

public:

    PixelPoint position;
    Color color;

public:

    GraphicalComponent() = default;

    virtual void Draw(Display& display) = 0;

    GRAPHICAL_TYPE type() {return type_;}

    virtual bool isWithin(const PixelPoint& point) = 0;

    virtual ~GraphicalComponent() = default;
    
};

class PhysicalComponent
{
protected:

    PHYSICAL_TYPE type_;
    REACTION_TYPE react_type_;

public:
    
    Vector2 coord;

public:
    bool was_collide;

    PhysicalComponent() = default;    

    virtual void nextMovement(float tick) = 0;
    virtual COLLISION_TYPE collisionWallDetect(Field& field, float tick) = 0;
    virtual void collisionWallResponse(const Field& field, COLLISION_TYPE collision_type) = 0;
    virtual Vector2 getNextMovement(float tick) const = 0;
    virtual float getKineticEnergy() const = 0;

    PHYSICAL_TYPE type() const {return type_;}
    REACTION_TYPE react_type() const {return react_type_;}

    virtual ~PhysicalComponent() = default;
};

class Entity
{
private:

    GraphicalComponent* graph_;
    PhysicalComponent*  phys_;

    void connectComponents(Field& field);

public:

    Entity() = delete;
    
    Entity(GraphicalComponent* graph_comp, PhysicalComponent* phys_comp, Field& field);
    Entity(const Entity& other);
    Entity(const Entity* other);

    GraphicalComponent* graph();
    PhysicalComponent* phys();

    ~Entity();
};