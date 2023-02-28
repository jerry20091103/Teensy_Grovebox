#include "lvgl.h"
#include "Arduino.h"
#include "fonts/fonts.h"
#include "Audio/AudioObjects.h"

// * Global Colors
static const lv_color_t color_Red = lv_palette_main(LV_PALETTE_RED);
static const lv_color_t color_RedDark = lv_color_hex(0x8c1515);
static const lv_color_t color_Yellow = lv_palette_main(LV_PALETTE_YELLOW);
static const lv_color_t color_YellowDark = lv_color_hex(0xb58a14);
static const lv_color_t color_Blue = lv_palette_main(LV_PALETTE_BLUE);
static const lv_color_t color_BlueDark = lv_palette_darken(LV_PALETTE_BLUE, 4);
static const lv_color_t color_Green = lv_palette_main(LV_PALETTE_GREEN);
static const lv_color_t color_GreenDark = lv_palette_darken(LV_PALETTE_GREEN, 4);
static const lv_color_t color_Grey = lv_palette_darken(LV_PALETTE_GREY, 3);
static const lv_color_t color_GreyDark = lv_palette_darken(LV_PALETTE_GREY, 4);
static const lv_color_t color_LightGreen = lv_palette_main(LV_PALETTE_LIGHT_GREEN);
static const lv_color_t color_LightGreenDark = lv_palette_darken(LV_PALETTE_LIGHT_GREEN, 3);
// * Global Fonts
static const lv_font_t *font_small = &lv_font_montserrat_12;
static const lv_font_t *font_medium = &lv_font_montserrat_14;
static const lv_font_t *font_large = &lv_font_montserrat_18;
static const lv_font_t *font_extraSymbol = &symbol_extra_18;

// * Extra symbols
#define MY_HEADPHONE_SYMBOL "\xEF\x80\xA5"

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
