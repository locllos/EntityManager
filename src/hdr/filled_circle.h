#pragma once

#include "display.h"
#include "entity.h"


class FilledCircle : public GraphicalComponent
{
private:

    PixelPoint position_;

public:

    int pixel_radius_;
    Color color_;

public:

    FilledCircle() = default;
    FilledCircle(PixelPoint position, Color color, float radius);
    FilledCircle(Color color);

    void Move(PixelPoint position) override;
    void Draw(Display& display) override;
    

    virtual ~FilledCircle() = default;
};