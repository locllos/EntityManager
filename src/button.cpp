#include "hdr/button.h"

IlluminatedButton::IlluminatedButton(Command* command, GraphicalComponent* init_graph) : illuminated_factor_(50), smooth_fading_factor_(-1), decrease_factor_(0), color_changed(false) 
{
    command_ = command; 
    graph = init_graph; 

    new_color_ = graph->color;

    new_color_.red += (graph->color.red) == 0 ? 0 : illuminated_factor_;
    new_color_.green += (graph->color.green) == 0 ? 0 : illuminated_factor_;
    new_color_.blue += (graph->color.blue) == 0 ? 0 : illuminated_factor_;

};

void IlluminatedButton::Action(const MouseState& status)
{   
    if (graph->isWithin(status.position) && status.isClickedLeftButton())
    {   
        actionClick();
        Delay(100);
    }
    else if (graph->isWithin(status.position))
    {
        graph->color = new_color_;

        color_changed = true;
        printf("change color\n");
        decrease_factor_ = 10;
        smooth_fading_factor_ = illuminated_factor_ * decrease_factor_;
    }
    else if (!graph->isWithin(status.position) && color_changed)
    {
        actionSmoothFading();
    }
}

void IlluminatedButton::actionSmoothFading()
{
    if (smooth_fading_factor_ > -1 &&
        smooth_fading_factor_ % decrease_factor_ == 0)
    {
        graph->color.red -= (graph->color.red) == 0 ? 0 : 1;
        graph->color.green -= (graph->color.green) == 0 ? 0 : 1;
        graph->color.blue -= (graph->color.blue) == 0 ? 0 : 1;
    }
    if (smooth_fading_factor_ > -1)
    {
        --smooth_fading_factor_;
    }
    else 
    {
        color_changed = false;
        printf("unchange color\n");
    }
}

void IlluminatedButton::actionClick()
{
    command_->Execute();
}

IlluminatedButton::~IlluminatedButton()
{
    delete graph;
    delete command_;
}