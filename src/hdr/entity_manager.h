#include "entity.h"
#include "field.h"

class EntityManager
{
private:

    Entity** entities_;

    size_t size_;
    size_t capacity_;

public:

    EntityManager() = default;
    EntityManager(size_t capacity = 4);

    void addEntity(Entity* ball);
    void processEntities(Display& display, Field& field, float tick);

    ~EntityManager();
};