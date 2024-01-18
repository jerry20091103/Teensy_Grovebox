#ifndef BUTTONS_H
#define BUTTONS_H

#include "lvgl.h"
/* Button GUI object
Wraps lvgl objects and target callback function.
*/

typedef void (*ButtonPressedCallback_t)(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
typedef void (*ButtonHoldCallback_t)(void *targetPointer, lv_obj_t *labelObj);

class Button
{
private:
    // lvgl objects
    lv_obj_t *button = NULL;
    lv_obj_t *label = NULL;
    // target to control
    void *pressedTargetPointer = NULL;
    void *holdTargetPointer = NULL;
    // generic callback function
    ButtonPressedCallback_t pressedCallback = NULL;
    ButtonHoldCallback_t holdCallback = NULL;
    // lvgl callback function
    static void lvglCallback(lv_event_t *event);
    // other private methods
    void createButton(lv_obj_t *parent, int16_t w, int16_t h, const char *text, uint8_t color);
    // other variables
    bool isToggleButton = false; // (the toggle state is stored in lvgl object's LV_STATE_CHECKED state)
public:
    // constructor
    Button(lv_obj_t *parent, int16_t w, int16_t h, const char* text = NULL, bool toggle = false, uint8_t color = 0);
    // destructor
    ~Button();
    // methods
    void setPressedCallback(ButtonPressedCallback_t pressedCallback, void *targetPointer);
    void setHoldCallback(ButtonHoldCallback_t holdCallback, void *targetPointer);
    void pressButton();
    void holdButton();
    void setToggle(bool toggle);

    lv_obj_t* getLvglObject() { return button; }
    lv_obj_t* getLabelObject() { return label; }
    bool getIsToggled() { return lv_obj_has_state(button, LV_STATE_CHECKED); }
};


#endif // BUTTONS_H