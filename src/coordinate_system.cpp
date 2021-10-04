#include "hdr/display.h"
#include "hdr/coordinate_system.h"

CoordinateSystem::CoordinateSystem() : 
    min_coord_({}), max_coord_({}), abs_origin_point_({}), x_scale_(0), y_scale_(0) {};

CoordinateSystem::CoordinateSystem(const Rectangle& area, 
                                   const Vector2& origin_point, float scale) :
                                   x_scale_(scale), y_scale_(scale)
{   
    abs_origin_point_ = { (int)(x_scale_ * origin_point.x + area.x), 
                          (int)(y_scale_ * origin_point.y + area.y) };
    
    min_coord_ = getRelative({area.x, area.y + area.height - 1});
    max_coord_ = getRelative({area.x + area.width - 1, area.y});

}

CoordinateSystem::CoordinateSystem(const Rectangle& area, 
                                   PixelPoint abs_origin_point, float scale) :
                                   x_scale_(scale), y_scale_(scale)
{   
    abs_origin_point_ = {abs_origin_point.x + area.x, abs_origin_point.y + area.y};

    min_coord_ = getRelative({area.x, area.y + area.height - 1});
    max_coord_ = getRelative({area.x + area.width - 1, area.y});
}

void CoordinateSystem::updateXScale(const Rectangle& area, float upd_scale)
{   
    x_scale_ = upd_scale;

    min_coord_ = getRelative({area.x, area.y + area.height - 1});
    max_coord_ = getRelative({area.x + area.width - 1, area.y});
}

void CoordinateSystem::updateYScale(const Rectangle& area, float upd_scale)
{   
    y_scale_ = upd_scale;

    min_coord_ = getRelative({area.x, area.y + area.height - 1});
    max_coord_ = getRelative({area.x + area.width - 1, area.y});
}

PixelPoint  CoordinateSystem::abs_origin_point() const { return abs_origin_point_; };
float      CoordinateSystem::scale() const { return ((x_scale_ == y_scale_) ? x_scale_ : -1); };
float      CoordinateSystem::x_scale() const { return x_scale_; };
float      CoordinateSystem::y_scale() const { return y_scale_; };
Vector2     CoordinateSystem::min_coord() const { return min_coord_; };
Vector2     CoordinateSystem::max_coord() const { return max_coord_; };

PixelPoint CoordinateSystem::getAbsolute(const Vector2& rel_point) const
{
    return { (int)(rel_point.x  * x_scale_) + abs_origin_point_.x,  
             (int)(-rel_point.y * y_scale_) + abs_origin_point_.y};
}

Vector2 CoordinateSystem::getRelative(PixelPoint abs_point) const
{   
    float delta_x = ((float)abs_point.x  - (float)abs_origin_point_.x);
    float delta_y = ((-1) * (float)abs_point.y + (float)abs_origin_point_.y);
    return Vector2( delta_x / x_scale_, 
                    delta_y / y_scale_);
}


bool CoordinateSystem::isWithin(const Rectangle& rect, Vector2 point) const
{
    return rect.isWithin(getAbsolute(point));
}
