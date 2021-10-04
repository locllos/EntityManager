#include "field.h"
#include "array.hpp"

class DynamicGraphic : public Field
{
private:

    Rectangle area_;
    CoordinateSystem system_;
    Array<float> points_;

    Color foreground_color_;
    Color background_color_;

    float prev_value;

    int queue_idx_;

public:

    DynamicGraphic(Rectangle& area, Color foreground_color, Color background_color, float scale);
    
    void pushValue(float value);
    void increaseScale(float scale);
    void decreaseScale(float scale);
    void Draw(Display& display);

    // ~DynamicGraphic() = default;
};