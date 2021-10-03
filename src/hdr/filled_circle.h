#pragma once

#include "display.h"
#include "entity.h"


class FilledCircle : public GraphicalComponent
{
public:

    int pixel_radius;

public:

    FilledCircle() = default;
    FilledCircle(PixelPoint position, Color color, float radius);
    FilledCircle(Color color);

    void Draw(Display& display) override;    

    virtual ~FilledCircle() = default;
};