#include "hdr/filled_circle.h"

FilledCircle::FilledCircle(PixelPoint init_position, Color init_color, float radius) : pixel_radius(radius) 
{
    color = init_color;
    position = init_position;
    type_ = FILLED_CIRCLE;
};

FilledCircle::FilledCircle(Color init_color) : pixel_radius(0) {color = init_color; type_ = FILLED_CIRCLE;};


void FilledCircle::Draw(Display& display)
{   
    Color old_color = display.getColor();
    display.setColor(color);

    
    PixelPoint point = {position.x - pixel_radius, position.y - pixel_radius};

    for (; point.x < position.x; ++point.x)
    {   
        for (; point.y < position.y; ++point.y)
        {   
            PixelPoint result = position - point;
            if (result.x * result.x + result.y * result.y <= pixel_radius * pixel_radius)
            {   
                display.drawPoint(point);
                display.drawPoint({point.x, point.y + 2 * result.y - 1});
                display.drawPoint({point.x + 2 * result.x - 1, point.y});
                display.drawPoint({point.x + 2 * result.x - 1, point.y + 2 * result.y - 1});
            } 
        }
        point.y = position.y - pixel_radius;
    }
    
    display.setColor(old_color);
}

bool FilledCircle::isWithin(const PixelPoint& point)
{   
    PixelPoint result = {(point.x - position.x), (point.y - position.y)};
    return ( result.x * result.x + result.y * result.y <= pixel_radius * pixel_radius);
}