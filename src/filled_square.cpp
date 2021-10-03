#include "hdr/filled_square.h"

FilledSquare::FilledSquare(Color init_color) {color = init_color; type_ = FILLED_SQUARE;}
FilledSquare::FilledSquare(Color init_color, int pixel_length) : pixel_length(pixel_length) {color = init_color; type_ = FILLED_SQUARE;}
FilledSquare::FilledSquare(PixelPoint init_position, Color init_color, int init_pixel_length) : pixel_length(init_pixel_length) {position = init_position; color = init_color;}

void FilledSquare::Draw(Display& display)
{
    // because fill rect draws from edge not from center
    display.fillRect({position.x - pixel_length / 2, position.y - pixel_length / 2, pixel_length, pixel_length}, color);
}

bool FilledSquare::isWithin(const PixelPoint& point)
{
    Rectangle square = {position.x - pixel_length / 2, 
                        position.y - pixel_length / 2, 
                        pixel_length, pixel_length};

    return square.isWithin(point);
}
