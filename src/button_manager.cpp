#include "hdr/button_manager.h"

void ButtonManager::addButton(Button* button)
{
    data_.Append(button);
}

void ButtonManager::buttonProcessing(Display& display)
{   
    size_t size = data_.size();
    MouseState mouse_status = display.getMouseState();
    // printf("mouse status: (x, y) = (%d, %d)\n", mouse_status.position.x, mouse_status.position.y);
    for (size_t i = 0; i < size; ++i)
    {
        data_[i]->Action(mouse_status);

        data_[i]->graph->Draw(display);
    }
}