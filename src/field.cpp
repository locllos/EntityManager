#include "hdr/field.h"

bool isCentered(const Vector2& point)
{
    return isnan(point.x) && isnan(point.y);
}

Field::Field(Rectangle area, Color color,
             Vector2 origin_point, float scale) :
    area_(area), 
    color_(color)
{   
    if (isCentered(origin_point))
    {
        coord_system_ = CoordinateSystem(area, (PixelPoint){area.width / 2 - 1, area.height / 2 - 1}, scale);
    }
    else
    {
        coord_system_ = CoordinateSystem(area, origin_point, scale);
    }
}

Field::Field(Rectangle area, Color color,
             PixelPoint abs_origin_point, float scale) :
    area_(area), 
    color_(color)
{
    coord_system_ = CoordinateSystem(area, abs_origin_point, scale);
}

CoordinateSystem& Field::coord_system()
{
    return coord_system_;
}

const Rectangle& Field::area() const
{
    return area_;
}

void Field::Draw(Display& display)
{   
    // Color display_color = display.getColor();

    // display.setColor(color_);
    // display.setClipRect(area_);
    display.fillRect(area_, color_);

    // display.setColor(display_color);
}

void Field::drawFigure(Display& display, Entity* entity)
{
    entity->graph()->position = coord_system_.getAbsolute(entity->phys()->coord);

    display.clipRect(area_);

    entity->graph()->Draw(display);

    display.unClipRect();
}

void Field::drawPoint(Display& display, Vector2& point, Color& color)
{
    display.drawPoint(coord_system_.getAbsolute(point), color);
}

void Field::drawLine(Display& display, Vector2& first_point, Vector2& second_point, Color& color)
{
    display.drawLine(coord_system_.getAbsolute(first_point),
                      coord_system_.getAbsolute(second_point), color);
}

Vector2 Field::getRandomCoord() const
{
    PixelPoint rand_pixel = {(size_t)rand() % area_.width, (size_t)rand() % area_.height};

    return coord_system_.getRelative(rand_pixel);
}

bool Field::isWithin(PixelPoint point) const
{
    return area_.isWithin(point);
}

