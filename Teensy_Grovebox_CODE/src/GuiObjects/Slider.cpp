#include "Slider.h"
#include "Colors.h"

void Slider::lvglCallback(lv_event_t *event)
{
    Slider *slider = (Slider *)lv_event_get_user_data(event);
    // do target stuff
    if (slider->callback != NULL && slider->targetPointer != NULL)
        slider->callback(slider->targetPointer, lv_slider_get_value(slider->slider));
}

void Slider::createSlider(lv_obj_t *parent, int16_t w, int16_t h)
{
    slider = lv_slider_create(parent);
    lv_obj_set_size(slider, w, h);
    lv_obj_set_style_bg_color(slider, color_Grey, 0);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_KNOB);
    lv_obj_set_style_pad_all(slider, 2, LV_PART_KNOB);
}

Slider::Slider(lv_obj_t *parent, int16_t w, int16_t h)
{
    createSlider(parent, w, h);
    lv_obj_add_event_cb(slider, lvglCallback, LV_EVENT_VALUE_CHANGED, this);
}

Slider::~Slider()
{
    lv_obj_del(slider);
}

void Slider::setCallback(SliderCallback_t callback, void *targetPointer)
{
    this->callback = callback;
    this->targetPointer = targetPointer;
}

void Slider::setValue(int value)
{
    lv_slider_set_value(slider, value, LV_ANIM_OFF);
    // do target stuff
    if (callback != NULL && targetPointer != NULL)
        callback(targetPointer, value);
}

void Slider::setRange(int min, int max)
{
    lv_slider_set_range(slider, min, max);
}
