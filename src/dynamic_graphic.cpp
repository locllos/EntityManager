#include "hdr/dynamic_graphic.h"

DynamicGraphic::DynamicGraphic(Rectangle& area, Color foreground_color, Color background_color, float scale)
    :
    area_(area), system_(area, (PixelPoint){0, area.height - 1}, scale), foreground_color_(foreground_color), background_color_(background_color)
{
    int size = system_.max_coord().x - system_.min_coord().x + 1.5;
    for (int i = 0; i < size; ++i)
    {
        points_.Append(0);
    }
}

void DynamicGraphic::pushValue(float value)
{   
    if (prev_value == value) return;

    points_.data(queue_idx_, value);

    queue_idx_ = (queue_idx_ + 1) % points_.size();

    prev_value = value;
}

void DynamicGraphic::Draw(Display& display)
{   
    display.clipRect(area_);
    display.fillRect(area_, background_color_);

    int size = (int)points_.size();
    int normal_idx = 0;
    for (int i = (queue_idx_ + 1) % size; (i + 1) % size != queue_idx_; i = (i + 1) % size)
    {   
        display.drawLine(system_.getAbsolute(Vector2(normal_idx, points_[i])), 
                         system_.getAbsolute(Vector2(normal_idx + 1, points_[(i + 1) % size])), 
                         foreground_color_, 2);
        ++normal_idx;
    }
    display.unClipRect();
}

void DynamicGraphic::increaseScale(float scale)
{
    system_.updateYScale(area_, system_.y_scale() + scale);
}

void DynamicGraphic::decreaseScale(float scale)
{
    system_.updateYScale(area_, system_.y_scale() - scale);
}