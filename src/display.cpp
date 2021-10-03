#include "hdr/display.h"

const float PI = 3.14159265359;
const float ARROW_ANGLE = PI / 12;

Color::Color(uint8_t init_red,  uint8_t init_green, uint8_t init_blue, uint8_t init_alpha) : red(init_red), blue(init_blue), green(init_green), alpha(init_alpha) {}; 


bool areColorsEqual(Color color_a, Color color_b)
{
    return ((color_a.red   == color_b.red) &&
            (color_a.blue  == color_b.blue) &&
            (color_a.green == color_b.green) &&
            (color_a.alpha == color_b.alpha));
}

Color getRandomColor()
{
    return Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
}

void Color::decreaseRGB(uint8_t value)
{
    red -= value;
    green -= value;
    blue -= value;
}

void Color::increaseRGB(uint8_t value)
{
    red += value;
    green += value;
    blue += value;
}

Color convertSDLColorToDefault(SDL_Color sdl_color)
{
    Color color = {sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a};

    return color;
}

SDL_Color convertDefaultColorToSDL(Color color)
{
    return (SDL_Color){color.red, color.green, color.blue, color.alpha};
}

bool MouseState::isClickedLeftButton() const
{
    return status & SDL_BUTTON_LMASK;
}

bool MouseState::isClickedMiddleButton() const
{
    return status & SDL_BUTTON_MMASK;
}

bool MouseState::isClickedRightButton() const
{
    return status & SDL_BUTTON_RMASK;
}

Rectangle convertSDLRectangleToDefault(SDL_Rect sdl_rect)
{
    return {(size_t)sdl_rect.x, (size_t)sdl_rect.y, sdl_rect.w, sdl_rect.h};
}

SDL_Rect convertDefaultRectangleToSDL(Rectangle rectangle)
{
    return (SDL_Rect){rectangle.x, rectangle.y, rectangle.width, rectangle.height};
}

PixelPoint PixelPoint::Add(size_t x, size_t y)
{       
    return this->operator+({x, y});
}

PixelPoint PixelPoint::operator+(PixelPoint rhs_point)
{
    return {x + rhs_point.x, y + rhs_point.y};
}

PixelPoint PixelPoint::operator-(PixelPoint rhs_point)
{
    return {x - rhs_point.x, y - rhs_point.y};
}

const PixelPoint& PixelPoint::operator=(const PixelPoint& rhs_point)
{
    x = rhs_point.x;
    y = rhs_point.y;

    return *this;
}

bool Rectangle::isWithin(PixelPoint point) const
{
    return x <= point.x && (x + width - 1) >= point.x &&
           y <= point.y && (y + height - 1) >= point.y;
}

Display::Display(const char* title,
                 size_t x_pos, size_t y_pos, 
                 size_t width, size_t height, 
                 uint32_t window_flags, uint32_t renderer_flags)
{    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }
    
    window_ = SDL_CreateWindow(title, x_pos, y_pos, width, height, window_flags);
    renderer_ = SDL_CreateRenderer(window_, -1, renderer_flags);
}

bool Display::isWithinWindow(PixelPoint point)
{   
    int width = 0;
    int height = 0;

    SDL_GetWindowSize(window_, &width, &height);

    return (point.x >= 0 && point.x <  width &&
            point.y >= 0 && point.y <  height);
}

void Display::drawBoldLine(PixelPoint first, PixelPoint second, size_t thickness)
{
    size_t thickness_factor_y = 0;
    size_t thickness_factor_x = 0;

    if ((first.x - second.x) * (first.x - second.x) >
        (first.y - second.y) * (first.y - second.y))
    {
        thickness_factor_y = 1;
    }
    else
    {
        thickness_factor_x = 1;
    }

    for (size_t i = 0; i < thickness; ++i)
    {   
        first.x = fabs(first.x + thickness_factor_x * i);
        second.x = fabs(second.x + thickness_factor_x * i);
        first.y = fabs(first.y + thickness_factor_y * i);
        second.y = fabs(second.y + thickness_factor_y * i);

        drawLine(first, second);

        thickness_factor_x *= (-1);
        thickness_factor_y *= (-1);
    }
}




void Display::getWindowSize(int* width, int* height) const
{
    SDL_GetWindowSize(window_, width, height);
}

void Display::Clear()
{
    SDL_RenderClear(renderer_);
}

void Display::Present()
{
    SDL_RenderPresent(renderer_);
}

Color Display::getColor()
{   
    SDL_Color color{};
    
    SDL_GetRenderDrawColor(renderer_, &color.r, &color.g, &color.b, &color.a);

    return convertSDLColorToDefault(color);
}

void Display::setColor(Color color)
{   
    SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, color.alpha);
}

void Display::drawPoint(PixelPoint point, Color color)
{    
    // if (!isWithinWindow(point)) {printf("Warning!\n");}
    int width = 0;
    int height = 0;
    getWindowSize(&width, &height);

    bool is_current_color = areColorsEqual(color, CURRENT_COLOR);

    Color old_color{};
    if (!is_current_color) 
    {   
        old_color = getColor();
        setColor(color);
    }

    SDL_RenderDrawPoint(renderer_, point.x % width, point.y % height);

    if (!is_current_color) setColor(old_color);

}

void Display::drawLine(PixelPoint first, PixelPoint second, Color color, size_t thickness)
{   
    if (!isWithinWindow(first) && !isWithinWindow(second)) return;
    
    bool is_current_color = areColorsEqual(color, CURRENT_COLOR);

    Color old_color{};
    if (!is_current_color) 
    {   
        old_color = getColor();
        setColor(color);
    }

    if (thickness > 1) drawBoldLine(first, second, thickness);
    else SDL_RenderDrawLine(renderer_, first.x, first.y, second.x, second.y);

    if (!is_current_color) setColor(old_color);
}

void Display::fillRect(const Rectangle& rectangle, Color color)
{
    if (!isWithinWindow({rectangle.x, rectangle.y})) return;
    
    bool is_current_color = areColorsEqual(color, CURRENT_COLOR);

    Color old_color{};
    if (!is_current_color) 
    {   
        old_color = getColor();
        setColor(color);
    }

    SDL_Rect sdl_rect = convertDefaultRectangleToSDL(rectangle);
    SDL_RenderFillRect(renderer_, &sdl_rect);

    if (!is_current_color) setColor(old_color);
}

void Display::setClipRect(const Rectangle& rect)
{   
    SDL_Rect sdl_rect = convertDefaultRectangleToSDL(rect);
    SDL_RenderSetClipRect(renderer_, &sdl_rect);
}

MouseState Display::getMouseState() const
{
    MouseState state = {};
    
    int x_pos = 0;
    int y_pos = 0;
    
    state.status = SDL_GetMouseState(&x_pos, &y_pos);
    
    state.position.x = x_pos;
    state.position.y = y_pos;

    return state;
}

void Delay(int time)
{
    SDL_Delay(time);
}

Display::~Display()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}