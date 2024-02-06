#include "ParamArc.h"
#include "Pages/GuiUtility.h"
#include "Colors.h"

// binding table for ParamArc
ParamArc *paramArcBindingTable[4] = {NULL, NULL, NULL, NULL};

// lvgl callback function
void ParamArc::lvglCallback(lv_event_t *event)
{
    ParamArc *paramArc = (ParamArc *)lv_event_get_user_data(event);
    lv_obj_t *arc = lv_event_get_target(event);
    int16_t value = lv_arc_get_value(arc);
    // do target stuff
    // *this is responsible for updating the target controll value and the value text
    if (paramArc->targetPointer != NULL && paramArc->callback != NULL)
        paramArc->callback(paramArc->targetPointer, paramArc->valueText, value + paramArc->rangeOffset, paramArc->encoderIndex);
    // update hardware binding if any
    if (paramArc->encoderIndex >= 0)
        enc[paramArc->encoderIndex]->setCurrentReading(value);
};

// hardware binding callback function
void ParamArc::encoderCallback(int16_t value)
{
    // update lvgl object
    lv_arc_set_value(arc, value);
    // do target stuff
    // *this is responsible for updating the target controll value and the value text
    if (targetPointer != NULL && callback != NULL)
        callback(targetPointer, valueText, value + rangeOffset, encoderIndex);
};

// other private methods
void ParamArc::createArc(lv_obj_t *parent, uint8_t color, const char* title, const char* unit, bool padding)
{
    // create arc
    arc = lv_arc_create(parent);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_value(arc, 0);
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_arc_width(arc, 8, 0);
    if (padding)
    {
        lv_obj_set_style_size(arc, 80, 0);
        lv_obj_set_style_pad_all(arc, 10, 0);
    }
    else
    {
        lv_obj_set_style_size(arc, 60, 0);
        lv_obj_set_style_pad_all(arc, 0, 0);
    }
    // indicator part
    lv_obj_set_style_arc_width(arc, 8, LV_PART_INDICATOR);
    // knob part
    lv_obj_set_style_pad_all(arc, 2, LV_PART_KNOB);
    
    lv_obj_add_flag(arc, LV_OBJ_FLAG_OVERFLOW_VISIBLE);

    // create value
    valueText = lv_label_create(arc);
    lv_obj_center(valueText);
    // create title
    if (title != NULL)
    {
        titleText = lv_label_create(arc);
        lv_label_set_text(titleText, title);
        lv_obj_align(titleText, LV_ALIGN_CENTER, 0, -42);
        lv_obj_set_style_text_align(titleText, LV_TEXT_ALIGN_CENTER, 0);
    }
    // create unit
    if (unit != NULL)
    {
        unitText = lv_label_create(arc);
        lv_label_set_text(unitText, unit);
        lv_obj_set_style_text_font(unitText, font_small, 0);
        lv_obj_align(unitText, LV_ALIGN_BOTTOM_MID, 0, 0);
    }
    // set color
    switch (color)
    {
    case 1:
        lv_obj_set_style_arc_color(arc, color_RedDark, LV_PART_MAIN);
        lv_obj_set_style_arc_color(arc, color_Red, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(arc, color_Red, LV_PART_KNOB);
        break;
    case 2:
        lv_obj_set_style_arc_color(arc, color_YellowDark, LV_PART_MAIN);
        lv_obj_set_style_arc_color(arc, color_Yellow, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(arc, color_Yellow, LV_PART_KNOB);
        break;
    case 3:
        lv_obj_set_style_arc_color(arc, color_BlueDark, LV_PART_MAIN);
        lv_obj_set_style_arc_color(arc, color_Blue, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(arc, color_Blue, LV_PART_KNOB);
        break;
    case 4:
        lv_obj_set_style_arc_color(arc, color_GreenDark, LV_PART_MAIN);
        lv_obj_set_style_arc_color(arc, color_Green, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(arc, color_Green, LV_PART_KNOB);
        break;
    default:
        lv_obj_set_style_arc_color(arc, lv_color_white(), LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(arc, lv_color_white(), LV_PART_KNOB);
        break;
    }
};

// constructor
ParamArc::ParamArc(lv_obj_t *parent, uint8_t color, const char* title, const char* unit, bool padding)
{
    createArc(parent, color, title, unit, padding);
    lv_obj_add_event_cb(arc, lvglCallback, LV_EVENT_VALUE_CHANGED, this);
}

// destructor
ParamArc::~ParamArc()
{
    lv_obj_del(arc);
    // unbind encoder
    if (encoderIndex >= 0)
        paramArcBindingTable[encoderIndex] = NULL;
}

// methods
void ParamArc::setValue(int16_t value)
{
    // set lvgl object
    lv_arc_set_value(arc, value - rangeOffset);
    // do target stuff
    if (targetPointer != NULL && callback != NULL)
        callback(targetPointer, valueText, value, encoderIndex);
    // update hardware binding if any
    if (encoderIndex >= 0)
        enc[encoderIndex]->setCurrentReading(value - rangeOffset);
}

void ParamArc::setRange(int16_t rangeMin, int16_t rangeMax)
{
    // set range offset
    rangeOffset = rangeMin;
    // set lvgl object
    lv_arc_set_range(arc, 0, rangeMax - rangeMin);
    if (encoderIndex >= 0)
        enc[encoderIndex]->changePrecision(rangeMax - rangeMin, lv_arc_get_value(arc), false);
}

void ParamArc::setCallback(ParamArcCallback_t callback, void *targetPointer)
{
    this->callback = callback;
    this->targetPointer = targetPointer;
}

void ParamArc::bindEncoder(int8_t encoderIndex)
{
    // unbind previous encoder
    if (this->encoderIndex >= 0)
        paramArcBindingTable[this->encoderIndex] = NULL;
    // bind new encoder
    this->encoderIndex = encoderIndex;
    paramArcBindingTable[encoderIndex] = this;
    // set encoder value and range
    enc[encoderIndex]->setCurrentReading(lv_arc_get_value(arc));
    enc[encoderIndex]->changePrecision(lv_arc_get_max_value(arc), lv_arc_get_value(arc), false);
}

void encoderBindCallback(uint8_t encoderId, int value)
{
    if (paramArcBindingTable[encoderId] != nullptr)
        paramArcBindingTable[encoderId]->encoderCallback(value);
}
