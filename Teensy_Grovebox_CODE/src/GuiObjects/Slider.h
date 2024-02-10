#ifndef SLIDER_H
#define SLIDER_H

#include "lvgl.h"
/* Slider GUI object
    A white horizontal slider.
    Wraps the lvgl slider and target callback function.
*/

typedef void (*SliderCallback_t)(void *targetPointer, int value);

class Slider
{
private:
    // lvgl objects
    lv_obj_t *slider = NULL;
    // target to control
    void *targetPointer = NULL;
    // generic callback function
    SliderCallback_t callback = NULL;
    // lvgl callback function
    static void lvglCallback(lv_event_t *event);
    // other private methods
    void createSlider(lv_obj_t *parent, int16_t w, int16_t h);
public:
    Slider(lv_obj_t *parent, int16_t w, int16_t h);
    ~Slider();
    // methods
    void setCallback(SliderCallback_t callback, void *targetPointer);
    void setValue(int value);
    void setRange(int min, int max);

    lv_obj_t* getLvglObject() { return slider; }
    int getValue() { return lv_slider_get_value(slider); }
};

#endif // SLIDER_H