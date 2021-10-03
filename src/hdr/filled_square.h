#include "entity.h"
#include "display.h"


class FilledSquare : public GraphicalComponent
{
public:

    int pixel_length;

public:

    FilledSquare() = default;
    FilledSquare(Color color);
    FilledSquare(Color color, int pixel_length);
    FilledSquare(PixelPoint position, Color color, int pixel_length);

    void Draw(Display& display) override;

    bool isWithin(const PixelPoint& point) override; 

    virtual ~FilledSquare() = default;
};