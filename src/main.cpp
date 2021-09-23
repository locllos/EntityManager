#include "hdr/entity_manager.h"
#include "hdr/filled_circle.h"
#include "hdr/physical_circle.h"

const Color kQuietYellow = {255, 250, 208, 255};
const Color kQuietBlue = {203, 252, 255, 255};
const Color RED = {255, 0, 0, 255};
const Color BLUE = {0, 0, 255, 255};

int main()
{
    Display display("Help me pls");

    int width = 0;
    int height = 0;

    display.getWindowSize(&width, &height);

    Field field({0, 0, width, height}, kQuietYellow, CENTERED_ORIGIN_POINT, 20);

    EntityManager Entity_master(4);

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
                    tick += 0.000001;
                    break;

                case SDL_SCANCODE_DOWN:
                    tick -= 0.000001;
                    break;
                default:
                    break;
            }
        }
        field.Draw(display);
        Entity_master.processEntities(display, field, tick);
        display.Present();
    
    }


    return 0;
}