#include "hdr/entity_manager.h"
#include "hdr/filled_circle.h"
#include "hdr/physical_circle.h"

const Color kQuietYellow = {255, 250, 208, 255};
const Color kQuietBlue = {203, 252, 255, 255};
const Color RED = {255, 0, 0, 255};
const Color BLUE = {0, 0, 255, 255};
const Color YELLOW = {255, 255, 0, 255};
const Color GREEN = {0, 255, 0, 255};

int main()
{
    Display display("Help me pls");

    int width = 0;
    int height = 0;

    display.getWindowSize(&width, &height);

    Field field({20, 20, width * 2 / 3, height * 2 / 3}, kQuietYellow, CENTERED_ORIGIN_POINT, 20);

    EntityManager manager{};

    manager.addFilledCirclePhysCircle(field, BLUE, 1, 1, {8, -8}, {-400, -400}, REACTION_CIRCLE);
    manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {-1, 9}, {-100, 100}, REACTION_CIRCLE);
    manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {2, 1}, {100, 100}, REACTION_CIRCLE);
    manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {3, -4}, {100, -100}, REACTION_CIRCLE);
    manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {-4, 7}, {100, -100}, REACTION_CIRCLE);
    manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {5, -5}, {-100, -100}, REACTION_CIRCLE);
    manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {-6, 3}, {-100, 100}, REACTION_CIRCLE);
    manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {7, -2}, {-100, 100}, REACTION_CIRCLE);
    

    bool quit = false;
    SDL_Event event = {};
    
    float tick = 0.00001;
    while (!quit)
    {   
        display.Clear();
        while (SDL_PollEvent(&event))
        {
            quit = event.type == SDL_QUIT;
            switch (event.key.keysym.scancode)
            {
                case SDL_SCANCODE_UP:
                    tick += 0.0000001;
                    break;

                case SDL_SCANCODE_DOWN:
                    tick -= 0.0000001;
                    break;
                default:
                    break;
            }
        }
        field.Draw(display);
        manager.processEntities(display, field, tick);
        display.Present();
    }

    return 0;
}