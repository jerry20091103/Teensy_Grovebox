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

// create a ADSR envelope graph 
lv_obj_t *Gui_CreateEnvelopeGraph(lv_obj_t *parent, int16_t w, int16_t h)
{
    lv_obj_t* graph = lv_obj_create(parent);
    lv_obj_remove_style_all(graph);
    lv_obj_set_size(graph, w, h);
    lv_obj_set_style_pad_all(graph, 5, 0);
    lv_obj_set_align(graph, LV_ALIGN_TOP_LEFT);

    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 8);
    lv_style_set_line_rounded(&style_line, true);

    lv_obj_t* line = lv_line_create(graph);
    lv_obj_set_style_line_color(line, lv_color_white(), 0);   // delay
    lv_obj_add_style(line, &style_line, 0);
    lv_line_set_y_invert(line, true);
    line = lv_line_create(graph);
    lv_obj_set_style_line_color(line, color_Red, 0);    // attack
    lv_obj_add_style(line, &style_line, 0);
    lv_line_set_y_invert(line, true);
    line = lv_line_create(graph);
    lv_obj_set_style_line_color(line, color_Yellow, 0); // decay
    lv_obj_add_style(line, &style_line, 0);
    lv_line_set_y_invert(line, true);
    line = lv_line_create(graph);
    lv_obj_set_style_line_color(line, color_Blue, 0);   // sustain
    lv_obj_add_style(line, &style_line, 0);
    lv_line_set_y_invert(line, true);
    line = lv_line_create(graph);
    lv_obj_set_style_line_color(line, color_Green, 0);  // release
    lv_obj_add_style(line, &style_line, 0);
    lv_line_set_y_invert(line, true);

    return graph;
}

// set the graph curve with DADSR values, in ms (sustain is 0~1)
void Gui_SetEnvelopeGraph(lv_obj_t *graph, lv_point_t *points, float delay, float attack, float decay, float sustain, float release)
{
    int16_t w = lv_obj_get_width(graph) - 20; // minus the padding
    int16_t h = lv_obj_get_height(graph) - 10;
    Serial.println(w);
    Serial.println(h);
    // get the total length in ms 
    float total = delay + attack + decay + release;
    // add padding if the total length is less than 200ms
    if(total < 200)
    {
        total = 200;
    }
    // get absolute pos
    int16_t sustain_abs = w/5 - total/40000 * w/10; // sustain_abs is between w/5 and w/10, it gets smaller as total time increases
    int16_t w_remain = w - sustain_abs;
    int16_t delay_abs = delay / total * w_remain;
    int16_t attack_abs = attack / total * w_remain;
    int16_t decay_abs = decay / total * w_remain;
    int16_t release_abs = release / total * w_remain;
    // *draw the graph
    lv_obj_t *line;
    points[0] = {0, 0};
    points[1] = {delay_abs, 0};
    points[2] = {0, 0};
    points[3] = {attack_abs, h};
    points[4] = {0, h}; 
    points[5] = {decay_abs, (int16_t)(sustain * h)};
    points[6] = {0, (int16_t)(sustain * h)};
    points[7] = {sustain_abs, (int16_t)(sustain * h)};
    points[8] = {0, (int16_t)(sustain * h)};
    points[9] = {release_abs, 0};
    // delay line
    line = lv_obj_get_child(graph, 0);
    lv_obj_set_size(line, delay_abs, h);
    lv_line_set_points(line, &points[0], 2);
    // attack line
    line = lv_obj_get_child(graph, 1);
    lv_obj_set_size(line, attack_abs, h);
    lv_line_set_points(line, &points[2], 2);
    lv_obj_set_x(line, delay_abs);
    // decay line
    line = lv_obj_get_child(graph, 2);
    lv_obj_set_size(line, decay_abs, h);
    lv_line_set_points(line, &points[4], 2);
    lv_obj_set_x(line, delay_abs + attack_abs);
    // sustain line
    line = lv_obj_get_child(graph, 3);
    lv_obj_set_size(line, sustain_abs, h);
    lv_line_set_points(line, &points[6], 2);
    lv_obj_set_x(line, delay_abs + attack_abs + decay_abs);
    // release line
    line = lv_obj_get_child(graph, 4);
    lv_obj_set_size(line, release_abs, h);
    lv_line_set_points(line, &points[8], 2);
    lv_obj_set_x(line, delay_abs + attack_abs + decay_abs + sustain_abs);
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
