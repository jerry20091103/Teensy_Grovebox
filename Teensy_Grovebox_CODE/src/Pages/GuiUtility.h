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
// Paramsters arc
PROGMEM lv_obj_t *Gui_CreateParamArc(lv_obj_t *parent, uint8_t color = 0, const char* title = NULL, const char* unit = NULL, bool padding = true);
lv_obj_t *Gui_ParamArcGetValueText(lv_obj_t *arc);
lv_obj_t *Gui_ParamArcGetTitleText(lv_obj_t *arc);
lv_obj_t *Gui_ParamArcGetUnitText(lv_obj_t *arc);

// Button
PROGMEM lv_obj_t *Gui_CreateButton(lv_obj_t *parent, int16_t w, int16_t h, const char* text = NULL, bool toggle = false, uint8_t color = 0);

// Volume meter bar
PROGMEM lv_obj_t *Gui_CreateVolumeMeter(lv_obj_t *parent, uint8_t w, uint8_t h, uint8_t color = 0);

// Peak led
PROGMEM lv_obj_t *Gui_CreatePeakLed(lv_obj_t *parent, uint8_t w, uint8_t h);
void Gui_PeakLedOn(lv_obj_t *led);
void Gui_PeakLedOff(lv_obj_t *led);

// Spinbox (value seletor with -/+ on the side)
PROGMEM lv_obj_t *Gui_CreateSpinbox(lv_obj_t *parent, lv_event_cb_t onBtnPressedCb, void *cbUserData, uint8_t color = 0);
void Gui_SpinboxSetValue(lv_obj_t *spinbox, int value);

// ADSR Envelope graph
PROGMEM lv_obj_t *Gui_CreateEnvelopeGraph(lv_obj_t *parent, int16_t w, int16_t h);
void Gui_SetEnvelopeGraph(lv_obj_t *graph, lv_point_t *points, float delay, float attack, float decay, float sustain, float release);

// Simple wareform chart
PROGMEM lv_obj_t *Gui_CreateWaveformChart(lv_obj_t *parent, int16_t w, int16_t h, lv_chart_series_t **serMax, lv_chart_series_t **serMin, int16_t *arrMax, int16_t *arrMin);
void Gui_WaveFormChartSetPoints(lv_obj_t *chart, lv_chart_series_t *serMax, lv_chart_series_t *serMin, int16_t *data, int length);

PROGMEM void Gui_InitStyles();

// helper functions
void Gui_setObjIdFlag(lv_obj_t *&arcRef, uint8_t id);
uint8_t Gui_getObjIdFlag(lv_obj_t *&arcRef);
