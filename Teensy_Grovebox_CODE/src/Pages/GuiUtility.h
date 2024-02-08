#include "lvgl.h"
#include "Arduino.h"
#include "fonts/fonts.h"
#include "Audio/AudioObjects.h"



// * Images
LV_IMG_DECLARE(rev_saw_wave);
LV_IMG_DECLARE(saw_wave);
LV_IMG_DECLARE(sqr_wave);
LV_IMG_DECLARE(tri_wave);
LV_IMG_DECLARE(sin_wave);
LV_IMG_DECLARE(s_r_wave);

// * Object Global styles and object creator
// Create a lvgl button without using GUI objects
// A standard button, with color = 1~4, 0 is the default color, size = -1 to use default size
PROGMEM lv_obj_t *Gui_CreateButton(lv_obj_t *parent, int16_t w, int16_t h, const char* text = NULL, bool toggle = false, uint8_t color = 0);

// Simple wareform chart
PROGMEM lv_obj_t *Gui_CreateWaveformChart(lv_obj_t *parent, int16_t w, int16_t h, lv_chart_series_t **serMax, lv_chart_series_t **serMin, int16_t *arrMax, int16_t *arrMin);
void Gui_WaveFormChartSetPoints(lv_obj_t *chart, lv_chart_series_t *serMax, lv_chart_series_t *serMin, int16_t *data, int length);

// helper functions
void Gui_setObjIdFlag(lv_obj_t *objRef, uint8_t id);
uint8_t Gui_getObjIdFlag(lv_obj_t *objRef);
