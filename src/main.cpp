#include "hdr/entity_manager.h"
#include "hdr/button_manager.h"
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

    EntityManager ent_manager{};
    ButtonManager button_manager{};

    button_manager.addButton(new IlluminatedButton(new SpawnCircle(&ent_manager, &field), 
                                                   new FilledCircle({50, 700},
                                                                    {0, 200, 200, 255}, 30)));
    button_manager.addButton(new IlluminatedButton(new SpawnSquare(&ent_manager, &field), 
                                                   new FilledSquare({120, 700},
                                                                    {200, 0, 200, 255}, 60)));

    ent_manager.addFilledCirclePhysCircle(field, BLUE, 1, 1, {8, -8}, {-400, -400}, REACTION_CIRCLE);
    // ent_manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {-1, 9}, {-100, 100}, REACTION_CIRCLE);
    // ent_manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {2, 1}, {100, 100}, REACTION_CIRCLE);
    // ent_manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {3, -4}, {100, -100}, REACTION_CIRCLE);
    // ent_manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {-4, 7}, {100, -100}, REACTION_CIRCLE);
    // ent_manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {5, -5}, {-100, -100}, REACTION_CIRCLE);
    // ent_manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {-6, 3}, {-100, 100}, REACTION_CIRCLE);
    // ent_manager.addFilledCirclePhysCircle(field, YELLOW, 1, 1, {7, -2}, {-100, 100}, REACTION_CIRCLE);
    
    bool quit = false;
    SDL_Event event = {};
    
    float tick = 0.00002;
    bool delay = 0;
    while (!quit)
    {   
        while (SDL_PollEvent(&event))
        {
            quit = event.type == SDL_QUIT;
            switch (event.key.keysym.scancode)
            {
                case SDL_SCANCODE_UP:
                    // tick += 0.0000001;
                    delay = true;
                    break;

                case SDL_SCANCODE_DOWN:
                    // tick -= 0.0000001;
                    delay = false;
                    break;
                default:
                    break;
            }
        }
        display.Clear();
        button_manager.buttonProcessing(display);
        field.Draw(display);
        ent_manager.processEntities(display, field, tick);
        display.Present();

        if (delay) SDL_Delay(100);
    }

    return 0;
}