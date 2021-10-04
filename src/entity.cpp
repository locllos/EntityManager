#include "hdr/entity.h"
#include "hdr/component_connector.h"


void Entity::connectComponents(Field& field)
{
    COMPONENT_CONNECTORS[phys_->type()]
                        [graph_->type()](phys_, graph_, field);
}

GraphicalComponent* Entity::graph()
{
    return graph_;
}

PhysicalComponent* Entity::phys()
{
    return phys_;
}

Entity::Entity(GraphicalComponent* graph_comp, PhysicalComponent* phys_comp, Field& field)
{
    graph_ = graph_comp;
    phys_  = phys_comp;

    connectComponents(field);
}

Entity::Entity(const Entity* other)
{
    this->graph_ = other->graph_;
    this->phys_  = other->phys_;
}

Entity::Entity(const Entity& other)
{
    this->graph_ = other.graph_;
    this->phys_  = other.phys_;
}

Entity::~Entity()
{
    delete phys_;
    delete graph_;
}