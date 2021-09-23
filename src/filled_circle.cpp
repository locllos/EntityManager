#include "hdr/filled_circle.h"

FilledCircle::FilledCircle(PixelPoint position, Color color, float radius) : color_(color), pixel_radius_(radius) 
{
    position_ = position;
    type_ = FILLED_CIRCLE;
};

FilledCircle::FilledCircle(Color color) : position_({}), color_(color), pixel_radius_(0) {};


void FilledCircle::Move(PixelPoint point)
{
    position_ = point;
}


void FilledCircle::Draw(Display& display)
{   
    Color old_color = display.getColor();
    display.setColor(color_);

    
    PixelPoint point = {position_.x - pixel_radius_, position_.y - pixel_radius_};

    for (; point.x < position_.x; ++point.x)
    {   
        for (; point.y < position_.y; ++point.y)
        {   
            PixelPoint result = position_ - point;
            if (result.x * result.x + result.y * result.y <= pixel_radius_ * pixel_radius_)
            {   
                display.drawPoint(point);
                display.drawPoint({point.x, point.y + 2 * result.y - 1});
                display.drawPoint({point.x + 2 * result.x - 1, point.y});
                display.drawPoint({point.x + 2 * result.x - 1, point.y + 2 * result.y - 1});
            } 
        }
        point.y = position_.y - pixel_radius_;
    }
    
    display.setColor(old_color);
}