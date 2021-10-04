#pragma once

#include "vector.h"
#include "display.h"

bool isWithinRectangle(const Rectangle& rect, PixelPoint point);

class CoordinateSystem
{
private:
    
    Vector2 min_coord_;
    Vector2 max_coord_;

    PixelPoint abs_origin_point_;
    float x_scale_;              // сколько пикселей вмещает единица координаты
    float y_scale_;              // сколько пикселей вмещает единица координаты

public:

    CoordinateSystem();

    CoordinateSystem(const Rectangle& area, 
                     const Vector2& origin_point, float scale);
    CoordinateSystem(const Rectangle& area, 
                     PixelPoint abs_origin_point, float scale);

    void updateXScale(const Rectangle& area, float scale);
    void updateYScale(const Rectangle& area, float scale);
    
    Vector2 min_coord() const;
    Vector2 max_coord() const;
    PixelPoint abs_origin_point() const;
    
    float scale() const;
    float x_scale() const;
    float y_scale() const;

    PixelPoint getAbsolute(const Vector2& rel_point) const;
    Vector2 getRelative(PixelPoint abs_point) const;

    bool isWithin(const Rectangle& rect, Vector2 point) const;

    ~CoordinateSystem() = default;
};
