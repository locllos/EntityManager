#pragma once

#include "entity_manager.h"

class Command
{
public:
    bool is_executed_;

    virtual void Execute() = 0;

    virtual ~Command() = default;
};


class SpawnCircle : public Command
{
private:

    EntityManager* manager_;
    Field* field_;

public:

    SpawnCircle(EntityManager* manager, Field* field);

    void Execute() override;

    ~SpawnCircle() override;
};

class SpawnSquare: public Command
{
private:

    EntityManager* manager_;
    Field* field_;

public:

    SpawnSquare(EntityManager* manager, Field* field);

    void Execute() override;

    ~SpawnSquare() override;
};
