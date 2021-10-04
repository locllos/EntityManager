#include "hdr/entity_manager.h"
#include "hdr/button_manager.h"
#include "hdr/filled_circle.h"
#include "hdr/dynamic_graphic.h"
#include "hdr/physical_circle.h"

const Color kQuietYellow = {255, 250, 208, 255};
const Color kQuietBlue = {203, 252, 255, 255};
const Color RED = {255, 0, 0, 255};
const Color BLUE = {0, 0, 255, 255};
const Color YELLOW = {255, 255, 0, 255};
const Color GREEN = {0, 255, 0, 255};
const Color BLACK = {0, 0, 0, 255};
const Color WHITE = {255, 255, 255, 255};

Rectangle GRAPHIC_POS = {50, 786 * 2 / 3 + 50, 300, 100};

int main()
{
    Display display("Help me pls");

    int width = 0;
    int height = 0;

    display.getWindowSize(&width, &height);

    Field field({20, 20, width * 2 / 3, height * 2 / 3}, kQuietYellow, CENTERED_ORIGIN_POINT, 10);
    DynamicGraphic graphic(GRAPHIC_POS, GREEN, YELLOW, 10);
    EntityManager ent_manager{};
    ButtonManager button_manager{};

    button_manager.addButton(new IlluminatedButton(new SpawnCircle(&ent_manager, &field), 
                                                   new FilledCircle((PixelPoint){75 + width * 2 / 3, 60},
                                                                    {0, 200, 200, 255}, 50)));
    button_manager.addButton(new IlluminatedButton(new SpawnSquare(&ent_manager, &field), 
                                                   new FilledSquare((PixelPoint){75 + 120 + width * 2 / 3, 60},
                                                                    {200, 0, 200, 255}, 100)));

    ent_manager.addFilledCirclePhysCircle(field, BLUE, 1, 1, {8, -8}, {-400, -400}, REACTION_CIRCLE);
    
    bool quit = false;
    SDL_Event event = {};
    
    float tick = 0.0002 / 2;
    bool delay = 0;
    int num = 0;
    int prev = 0;
    while (!quit)
    {   
        while (SDL_PollEvent(&event))
        {
            quit = event.type == SDL_QUIT;
            switch (event.key.keysym.scancode)
            {
                case SDL_SCANCODE_UP:
                    graphic.increaseScale(1);
                    // tick += 0.0000001;
                    // delay = true;
                    break;

                case SDL_SCANCODE_DOWN:
                    graphic.decreaseScale(1);
                    // tick -= 0.0000001;
                    // delay = false;
                    break;
                default:
                    break;
            }
        }
        display.Clear();
        button_manager.buttonProcessing(display);
        field.Draw(display);
        ent_manager.processEntities(display, field, tick);
        graphic.pushValue(ent_manager.getAmountCircles());
        graphic.Draw(display);
        display.Present();

        if (delay) SDL_Delay(100);
    }

    return 0;
}