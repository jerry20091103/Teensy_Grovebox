#include "GuiUtility.h"
#include "GuiObjects/Colors.h"

// create a standard button, with color = 1~4, 0 is the default color, size = -1 to use default size
lv_obj_t *Gui_CreateButton(lv_obj_t *parent, int16_t w, int16_t h, const char *text, bool toggle, uint8_t color)
{
    lv_obj_t *button = lv_btn_create(parent);
    if (w >= 0)
        lv_obj_set_width(button, w);
    if (h >= 0)
        lv_obj_set_height(button, h);
    if (text != NULL)
    {
        lv_obj_t *label = lv_label_create(button);
        lv_label_set_text(label, text);
        lv_obj_center(label);
    }
    if (toggle)
        lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
    // set color
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
    return button;
}

// Simple wareform chart
lv_obj_t *Gui_CreateWaveformChart(lv_obj_t *parent, int16_t w, int16_t h, lv_chart_series_t **serMax, lv_chart_series_t **serMin, int16_t *arrMax, int16_t *arrMin)
{
    lv_obj_t *chart = lv_chart_create(parent);
    lv_obj_set_size(chart, w, h);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -32768, 32767);
    lv_obj_set_style_bg_color(chart, lv_color_black(), 0);

    /*Do not display points on the data*/
    lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(chart, 1, LV_PART_ITEMS);

    *serMax = lv_chart_add_series(chart, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);
    *serMin = lv_chart_add_series(chart, lv_color_white(), LV_CHART_AXIS_PRIMARY_Y);

    lv_chart_set_ext_y_array(chart, *serMax, arrMax);
    lv_chart_set_ext_y_array(chart, *serMin, arrMin);

    return chart;
}

void Gui_WaveFormChartSetPoints(lv_obj_t *chart, lv_chart_series_t *serMax, lv_chart_series_t *serMin, int16_t *data, int length)
{
    // downsample to 1000 points
    int16_t *arrMax = (int16_t *)lv_chart_get_y_array(chart, serMax);
    int16_t *arrMin = (int16_t *)lv_chart_get_y_array(chart, serMin);
    if (length < 1000)
    {
        lv_chart_set_point_count(chart, length);
        for (int i = 0; i < length; i++)
        {
            arrMax[i] = data[i];
            arrMin[i] = data[i];
        }
    }
    else
    {
        lv_chart_set_point_count(chart, 1000);
        int hop = length / 1000.0f;
        for (int i = 0; i < 1000; i++)
        {
            // find max
            int16_t max = 0;
            for (int j = 0; j < hop; j++)
            {
                if (data[i * hop + j] > max)
                {
                    max = data[i * hop + j];
                }
            }
            arrMax[i] = max;
            // find min
            int16_t min = 0;
            for (int j = 0; j < hop; j++)
            {
                if (data[i * hop + j] < min)
                {
                    min = data[i * hop + j];
                }
            }
            arrMin[i] = min;
        }
    }
    lv_chart_refresh(chart);
}

// use 4 user flags to store custom object id
void Gui_setObjIdFlag(lv_obj_t *objRef, uint8_t id)
{
    bool f1, f2, f3, f4;
    f1 = id & 0b00000001;
    f2 = id & 0b00000010;
    f3 = id & 0b00000100;
    f4 = id & 0b00001000;

    if (f1)
        lv_obj_add_flag(objRef, LV_OBJ_FLAG_USER_1);
    else
        lv_obj_clear_flag(objRef, LV_OBJ_FLAG_USER_1);
    if (f2)
        lv_obj_add_flag(objRef, LV_OBJ_FLAG_USER_2);
    else
        lv_obj_clear_flag(objRef, LV_OBJ_FLAG_USER_2);
    if (f3)
        lv_obj_add_flag(objRef, LV_OBJ_FLAG_USER_3);
    else
        lv_obj_clear_flag(objRef, LV_OBJ_FLAG_USER_3);
    if (f4)
        lv_obj_add_flag(objRef, LV_OBJ_FLAG_USER_4);
    else
        lv_obj_clear_flag(objRef, LV_OBJ_FLAG_USER_4);
}
uint8_t Gui_getObjIdFlag(lv_obj_t *objRef)
{
    return ((uint8_t)lv_obj_has_flag(objRef, LV_OBJ_FLAG_USER_1) << 0) +
           ((uint8_t)lv_obj_has_flag(objRef, LV_OBJ_FLAG_USER_2) << 1) +
           ((uint8_t)lv_obj_has_flag(objRef, LV_OBJ_FLAG_USER_3) << 2) +
           ((uint8_t)lv_obj_has_flag(objRef, LV_OBJ_FLAG_USER_4) << 3);
}
