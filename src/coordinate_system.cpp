#include "hdr/display.h"
#include "hdr/coordinate_system.h"

CoordinateSystem::CoordinateSystem() : 
    min_coord_({}), max_coord_({}), abs_origin_point_({}), scale_(0) {};

CoordinateSystem::CoordinateSystem(const Rectangle& area, 
                                   const Vector2& origin_point, float scale) :
                                   scale_(scale)
{   
    abs_origin_point_ = { (int)(scale_ * origin_point.x + area.x), 
                          (int)(scale_ * origin_point.y + area.y) };
    
    min_coord_ = getRelative({area.x, area.y + area.height - 1});
    max_coord_ = getRelative({area.x + area.width - 1, area.y});

}

CoordinateSystem::CoordinateSystem(const Rectangle& area, 
                                   PixelPoint abs_origin_point, float scale) :
                                   scale_(scale)
{   
    abs_origin_point_ = {abs_origin_point.x + area.x, abs_origin_point.y + area.y};

    min_coord_ = getRelative({area.x, area.y + area.height - 1});
    max_coord_ = getRelative({area.x + area.width - 1, area.y});
}

PixelPoint  CoordinateSystem::abs_origin_point() const { return abs_origin_point_; };
float      CoordinateSystem::scale()            const { return scale_; };
Vector2     CoordinateSystem::min_coord()        const { return min_coord_; };
Vector2     CoordinateSystem::max_coord()        const { return max_coord_; };

PixelPoint CoordinateSystem::getAbsolute(const Vector2& rel_point) const
{
    return { (int)(rel_point.x  * scale_) + abs_origin_point_.x,  
             (int)(-rel_point.y * scale_) + abs_origin_point_.y};
}

Vector2 CoordinateSystem::getRelative(PixelPoint abs_point) const
{
    return Vector2((abs_point.x  - abs_origin_point_.x) / scale_, 
                  (-abs_point.y  + abs_origin_point_.y) / scale_);
}


bool CoordinateSystem::isWithin(const Rectangle& rect, Vector2 point) const
{
    return rect.isWithin(getAbsolute(point));
}
