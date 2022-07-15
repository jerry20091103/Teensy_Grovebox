#include "GuiUtility.h"

void Gui_InitStyles()
{
    // Parameters arc main part
    lv_style_init(&style_paramArcMain);
    lv_style_set_size(&style_paramArcMain, 80);
    lv_style_set_pad_all(&style_paramArcMain, 10);
    lv_style_set_arc_width(&style_paramArcMain, 8);

    // Parameters arc main part (no padding)
    lv_style_init(&style_paramArcMainNoPad);
    lv_style_set_size(&style_paramArcMainNoPad, 60);
    lv_style_set_pad_all(&style_paramArcMainNoPad, 0);
    lv_style_set_arc_width(&style_paramArcMainNoPad, 8);

    // Parameters arc indicator part
    lv_style_init(&style_paramArcInd);
    lv_style_set_arc_width(&style_paramArcInd, 8);

    // Parameters arc knob part
    lv_style_init(&style_paramArcKnob);
    lv_style_set_pad_all(&style_paramArcKnob, 2);
}

// create a standard parameter arc, with color = 1~4, 0 is the default color
lv_obj_t *Gui_CreateParamArc(lv_obj_t *parent, uint8_t color, const char* title, const char* unit, bool padding)
{
    lv_obj_t *arc = lv_arc_create(parent);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_value(arc, 0);
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_SCROLLABLE);
    if(padding)
        lv_obj_add_style(arc, &style_paramArcMain, LV_PART_MAIN);
    else
        lv_obj_add_style(arc, &style_paramArcMainNoPad, LV_PART_MAIN);

    lv_obj_add_style(arc, &style_paramArcInd, LV_PART_INDICATOR);
    lv_obj_add_style(arc, &style_paramArcKnob, LV_PART_KNOB);
    lv_obj_add_flag(arc, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    // add title
    if(title != NULL)
    {
        lv_obj_t *label = lv_label_create(arc);
        lv_label_set_text(label, title);
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -20);
    }
    // add unit
    if(unit != NULL)
    {
        lv_obj_t *label = lv_label_create(arc);
        lv_label_set_text(label, unit);
        lv_obj_set_style_text_font(label, font_small, 0);
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
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
    return arc;
}

// create a standard button, with color = 1~4, 0 is the default color
lv_obj_t *Gui_CreateButton(lv_obj_t *parent, bool toggle, uint8_t color)
{
    lv_obj_t *button = lv_btn_create(parent);
    if(toggle)
        lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
    // set color
    switch (color)
    {
    case 1:
        lv_obj_set_style_bg_color(button, color_RedDark, 0);
        break;
    case 2:
        lv_obj_set_style_bg_color(button, color_YellowDark, 0);
        break;
    case 3:
        lv_obj_set_style_bg_color(button, color_BlueDark, 0);
        break;
    case 4:
        lv_obj_set_style_bg_color(button, color_GreenDark, 0);
        break;
    default:
        lv_obj_set_style_bg_color(button, color_Grey, 0);
        lv_obj_set_style_bg_color(button, lv_color_white(), LV_STATE_CHECKED);
        lv_obj_set_style_text_color(button, lv_color_black(), LV_STATE_CHECKED);
        break;
    }
    return button;
}

// create a volume meter bar, with color = 0 or 1
lv_obj_t *Gui_CreateVolumeMeter(lv_obj_t *parent, uint8_t w, uint8_t h, uint8_t color)
{
    lv_obj_t *bar = lv_bar_create(parent);
    lv_obj_set_size(bar, w, h);
    lv_bar_set_range(bar, -50, 0);
    lv_bar_set_value(bar, 0, LV_ANIM_ON);
    lv_obj_set_style_anim_time(bar, 100, 0);
    lv_obj_add_flag(bar, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
    lv_obj_clear_flag(bar, LV_OBJ_FLAG_SCROLLABLE);
    // set color
    switch (color)
    {
    case 1:
        lv_obj_set_style_bg_color(bar, color_RedDark, LV_PART_MAIN);
        lv_obj_set_style_bg_color(bar, color_Red, LV_PART_INDICATOR);
        break;
    default:
        lv_obj_set_style_bg_color(bar, color_LightGreenDark, LV_PART_MAIN);
        lv_obj_set_style_bg_color(bar, color_LightGreen, LV_PART_INDICATOR);
        break;
    }
    return bar;
}

// create a peak led
lv_obj_t *Gui_CreatePeakLed(lv_obj_t *parent, uint8_t w, uint8_t h)
{
    lv_obj_t *led = lv_led_create(parent);
    lv_obj_set_size(led, w, h);
    lv_led_set_color(led, color_Red);
    lv_obj_set_style_shadow_spread(led, 0, 0);
    lv_obj_set_style_bg_color(led, color_Red, 0);
    return led;
}

// use 4 user flags to store arc id
void Gui_setArcIdFlag(lv_obj_t *&arcRef, uint8_t id)
{
    bool f1, f2, f3, f4;
    f1 = id & 0b00000001;
    f2 = id & 0b00000010;
    f3 = id & 0b00000100;
    f4 = id & 0b00001000;

    if (f1)
        lv_obj_add_flag(arcRef, LV_OBJ_FLAG_USER_1);
    else
        lv_obj_clear_flag(arcRef, LV_OBJ_FLAG_USER_1);
    if (f2)
        lv_obj_add_flag(arcRef, LV_OBJ_FLAG_USER_2);
    else
        lv_obj_clear_flag(arcRef, LV_OBJ_FLAG_USER_2);
    if (f3)
        lv_obj_add_flag(arcRef, LV_OBJ_FLAG_USER_3);
    else
        lv_obj_clear_flag(arcRef, LV_OBJ_FLAG_USER_3);
    if (f4)
        lv_obj_add_flag(arcRef, LV_OBJ_FLAG_USER_4);
    else
        lv_obj_clear_flag(arcRef, LV_OBJ_FLAG_USER_4);
}
uint8_t Gui_getArcIdFlag(lv_obj_t *&arcRef)
{
    return ((uint8_t)lv_obj_has_flag(arcRef, LV_OBJ_FLAG_USER_1) << 0) + 
           ((uint8_t)lv_obj_has_flag(arcRef, LV_OBJ_FLAG_USER_2) << 1) + 
           ((uint8_t)lv_obj_has_flag(arcRef, LV_OBJ_FLAG_USER_3) << 2) + 
           ((uint8_t)lv_obj_has_flag(arcRef, LV_OBJ_FLAG_USER_4) << 3);
}
