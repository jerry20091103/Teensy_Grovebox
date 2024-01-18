#include "Spinbox.h"
#include "Pages/GuiUtility.h"

void Spinbox::buttonMinusCallback(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    Spinbox *spinbox = (Spinbox *)targetPointer;
    spinbox->pressButtonMinus();
}

void Spinbox::buttonPlusCallback(void *targetPointer, lv_obj_t *labelObj, bool isToggled)
{
    Spinbox *spinbox = (Spinbox *)targetPointer;
    spinbox->pressButtonPlus();
}

void Spinbox::createSpinbox(lv_obj_t *parent, uint8_t color)
{
    spinbox = lv_obj_create(parent);
    lv_obj_remove_style_all(spinbox);
    lv_obj_set_size(spinbox, 90, 30);
    lv_obj_add_flag(spinbox, LV_OBJ_FLAG_OVERFLOW_VISIBLE);

    buttonMinus = new Button(spinbox, 30, 30, LV_SYMBOL_MINUS, false, color);
    lv_obj_align(buttonMinus->getLvglObject(), LV_ALIGN_CENTER, -30, 0);
    buttonMinus->setPressedCallback(buttonMinusCallback, this);

    buttonPlus = new Button(spinbox, 30, 30, LV_SYMBOL_PLUS, false, color);
    lv_obj_align(buttonPlus->getLvglObject(), LV_ALIGN_CENTER, 30, 0);
    buttonPlus->setPressedCallback(buttonPlusCallback, this);

    valueText = lv_label_create(spinbox);
    lv_label_set_text_fmt(valueText, "%d", value);
    lv_obj_align(valueText, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(valueText, font_large, 0);
}

Spinbox::Spinbox(lv_obj_t *parent, uint8_t color)
{
    createSpinbox(parent, color);
}

Spinbox::~Spinbox()
{
    delete buttonMinus;
    delete buttonPlus;
    lv_obj_del(spinbox);
}

void Spinbox::setValue(int16_t value)
{
    this->value = value;
    if (value < rangeMin)
        this->value = rangeMin;
    if (value > rangeMax)
        this->value = rangeMax;
    // do target callback
    if (targetPointer != NULL && callback != NULL)
        callback(targetPointer, valueText, this->value);
}

void Spinbox::setRange(int16_t rangeMin, int16_t rangeMax)
{
    this->rangeMin = rangeMin;
    this->rangeMax = rangeMax;
    if (value < rangeMin)
        setValue(rangeMin);
    if (value > rangeMax)
        setValue(rangeMax);
}

void Spinbox::setCallback(SpinboxCallback_t callback, void *targetPointer)
{
    this->callback = callback;
    this->targetPointer = targetPointer;
}

void Spinbox::pressButtonMinus()
{
    setValue(value-1);
}

void Spinbox::pressButtonPlus()
{
    setValue(value+1);
}
