#include "Buttons.h"
#include "Pages/GuiUtility.h" 
#include "Colors.h"

void Button::lvglCallback(lv_event_t *event)
{
    Button *button = (Button *)lv_event_get_user_data(event);
    // distinguish between short click and long press
    if (event->code == LV_EVENT_SHORT_CLICKED)
    {
        // do target stuff
        // *this is responsible for updating the target controll value and the label text
        if (button->pressedTargetPointer != NULL && button->pressedCallback != NULL)
            button->pressedCallback(button->pressedTargetPointer, button->label, lv_obj_has_state(button->button, LV_STATE_CHECKED));
    }
    else if (event->code == LV_EVENT_LONG_PRESSED)
    {
        // reverse toggle state since long press also toggles lvgl object's LV_STATE_CHECKED state
        button->setToggle(!lv_obj_has_state(button->button, LV_STATE_CHECKED));
        // do target stuff
        // *this is responsible for updating the target controll value and the label text
        if (button->holdTargetPointer != NULL && button->holdCallback != NULL)
            button->holdCallback(button->holdTargetPointer, button->label);
    }
}

void Button::createButton(lv_obj_t *parent, int16_t w, int16_t h, const char *text, uint8_t color)
{
    button = lv_btn_create(parent);
    if (w >= 0)
        lv_obj_set_width(button, w);
    if (h >= 0)
        lv_obj_set_height(button, h);
    if (text != NULL)
    {
        label = lv_label_create(button);
        lv_label_set_text(label, text);
        lv_obj_center(label);
    }
    switch (color)
    {
    case 1:
        lv_obj_set_style_bg_color(button, color_RedDark, 0);
        lv_obj_set_style_bg_color(button, color_Red, LV_STATE_CHECKED);
        break;
    case 2:
        lv_obj_set_style_bg_color(button, color_YellowDark, 0);
        lv_obj_set_style_bg_color(button, color_Yellow, LV_STATE_CHECKED);
        break;
    case 3:
        lv_obj_set_style_bg_color(button, color_BlueDark, 0);
        lv_obj_set_style_bg_color(button, color_Blue, LV_STATE_CHECKED);
        break;
    case 4:
        lv_obj_set_style_bg_color(button, color_GreenDark, 0);
        lv_obj_set_style_bg_color(button, color_Green, LV_STATE_CHECKED);
        break;
    default:
        lv_obj_set_style_bg_color(button, color_Grey, 0);
        lv_obj_set_style_bg_color(button, lv_color_white(), LV_STATE_CHECKED);
        lv_obj_set_style_text_color(button, lv_color_black(), LV_STATE_CHECKED);
        break;
    }
}

Button::Button(lv_obj_t *parent, int16_t w, int16_t h, const char *text, bool toggle, uint8_t color)
{
    createButton(parent, w, h, text, color);
    lv_obj_add_event_cb(button, lvglCallback, LV_EVENT_SHORT_CLICKED, this);
    lv_obj_add_event_cb(button, lvglCallback, LV_EVENT_LONG_PRESSED, this);
    isToggleButton = toggle;
    if (isToggleButton)
        lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
}

Button::~Button()
{
    lv_obj_del(button);
}

void Button::setPressedCallback(ButtonPressedCallback_t pressedCallback, void *targetPointer)
{
    this->pressedCallback = pressedCallback;
    this->pressedTargetPointer = targetPointer;
}

void Button::setHoldCallback(ButtonHoldCallback_t holdCallback, void *targetPointer)
{
    this->holdCallback = holdCallback;
    this->holdTargetPointer = targetPointer;
}

void Button::pressButton()
{
    lv_event_send(button, LV_EVENT_SHORT_CLICKED, NULL);
}

void Button::holdButton()
{
    lv_event_send(button, LV_EVENT_LONG_PRESSED, NULL);
}

void Button::setToggle(bool toggle)
{
    if (isToggleButton)
    {
        if (toggle)
            lv_obj_add_state(button, LV_STATE_CHECKED);
        else
            lv_obj_clear_state(button, LV_STATE_CHECKED);
    }
}
