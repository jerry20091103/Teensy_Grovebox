#include "GuiUtility.h"

void Gui_InitStyles()
{
    // Parameters arc main part
    lv_style_init(&style_paramArcMain);
    lv_style_set_size(&style_paramArcMain, 80);
    lv_style_set_pad_all(&style_paramArcMain, 10);
    lv_style_set_arc_width(&style_paramArcMain, 8);

    // Parameters arc indicator part
    lv_style_init(&style_paramArcInd);
    lv_style_set_arc_width(&style_paramArcInd, 8);

    // Parameters arc knob part
    lv_style_init(&style_paramArcKnob);
    lv_style_set_pad_all(&style_paramArcKnob, 2);
}

// creat a standard parameter arc, with color = 1~4, 0 is the default color
lv_obj_t *Gui_CreateParamArc(lv_obj_t *parent, uint8_t color)
{
    lv_obj_t *arc = lv_arc_create(parent);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_value(arc, 0);
    lv_obj_add_style(arc, &style_paramArcMain, LV_PART_MAIN);
    lv_obj_add_style(arc, &style_paramArcInd, LV_PART_INDICATOR);
    lv_obj_add_style(arc, &style_paramArcKnob, LV_PART_KNOB);
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