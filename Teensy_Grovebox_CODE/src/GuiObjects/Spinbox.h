#ifndef SPINBOX_H
#define SPINBOX_H

#include "lvgl.h"
#include "Buttons.h"
/* Spinbox GUI object
Wraps lvgl objects, target callback function and value.
Includes a -/+ button and a value text. Buttons created from Button class.
*/

typedef void (*SpinboxCallback_t)(void *targetPointer, lv_obj_t *valueTextObj, int16_t value);

class Spinbox
{
private:
    lv_obj_t *spinbox = NULL;
    Button *buttonMinus = NULL;
    Button *buttonPlus = NULL;
    lv_obj_t *valueText = NULL;
    // target to control
    void *targetPointer = NULL;
    // generic callback function
    SpinboxCallback_t callback = NULL;
    // button callback function
    static void buttonMinusCallback(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    static void buttonPlusCallback(void *targetPointer, lv_obj_t *labelObj, bool isToggled);
    // other private methods
    void createSpinbox(lv_obj_t *parent, uint8_t color);
    // other variables
    int16_t value = 0;
    int16_t rangeMin = 0;
    int16_t rangeMax = 100;
public:
    // constructor
    Spinbox(lv_obj_t *parent, uint8_t color = 0);
    // destructor
    ~Spinbox();
    // methods
    void setValue(int16_t value);
    void setRange(int16_t rangeMin, int16_t rangeMax);
    void setCallback(SpinboxCallback_t callback, void *targetPointer);
    void pressButtonMinus();
    void pressButtonPlus();

    lv_obj_t* getLvglObject() { return spinbox; }
    lv_obj_t* getValueTextObject() { return valueText; }
    int16_t getValue() { return value; }
};

#endif // SPINBOX_H