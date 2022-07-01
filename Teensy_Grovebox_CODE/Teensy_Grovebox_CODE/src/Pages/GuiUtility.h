#include "lvgl.h"
#include "Arduino.h"

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
// * Global Fonts
static const lv_font_t *font_small = &lv_font_montserrat_10;
static const lv_font_t *font_medium = &lv_font_montserrat_14;
static const lv_font_t *font_large = &lv_font_montserrat_18;

// * Object Global styles and creator
// Paramsters arc
static lv_style_t style_paramArcMain;
static lv_style_t style_paramArcInd;
static lv_style_t style_paramArcKnob;
PROGMEM lv_obj_t *Gui_CreateParamArc(lv_obj_t *parent, uint8_t color = 0);

// Button
PROGMEM lv_obj_t *Gui_CreateButton(lv_obj_t *parent, bool toggle = false, uint8_t color = 0);

PROGMEM void Gui_InitStyles();
