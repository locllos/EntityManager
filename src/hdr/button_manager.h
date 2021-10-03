#include "array.hpp"
#include "button.h"

class ButtonManager
{

private:

    Array<Button*> data_;

public:

    ButtonManager() = default;

    void addButton(Button* button);

    void buttonProcessing(Display& display);

    ~ButtonManager() = default;
};