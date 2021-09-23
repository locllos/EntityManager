#include "hdr/entity.h"
#include "hdr/component_connector.h"


void Entity::connectComponents(const Field& field)
{
    COMPONENT_CONNECTORS[physical_component_->type() - 1]
                        [graphical_component_->type() - 1](physical_component_, graphical_component_, field);
}

GraphicalComponent* Entity::graphical_component()
{
    return graphical_component_;
}

PhysicalComponent* Entity::physical_component()
{
    return physical_component_;
}

Entity::Entity(GraphicalComponent* graph_comp, PhysicalComponent* phys_comp, const Field& field)
{
    graphical_component_ = graph_comp;
    physical_component_  = phys_comp;

    connectComponents(field);
}

Entity::~Entity()
{
    delete physical_component_;
    delete graphical_component_;
}