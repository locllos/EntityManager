#pragma once


#include "display.h"
#include "command.h"
#include "entity.h"

class Button
{
protected:

    Command* command_;

public:

    GraphicalComponent* graph;

public:

    virtual void Action(const MouseState& status) = 0;

    virtual ~Button() = default;
};

class IlluminatedButton : public Button
{
private:

    Color new_color_;
    bool color_changed;
    size_t illuminated_factor_;
    int decrease_factor_;
    int smooth_fading_factor_;

    void actionSmoothFading();
    void actionClick();

public:

    IlluminatedButton(Command* command, GraphicalComponent* graph);

    void Action(const MouseState& status) override;

    ~IlluminatedButton() override;
};




