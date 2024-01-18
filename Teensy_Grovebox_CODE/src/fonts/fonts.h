# ifndef FONTS_H
# define FONTS_H

#include "lvgl.h"

// define custom fonts
extern lv_font_t symbol_extra_18;

// * Global Fonts for use in GUI objects
static const lv_font_t *font_small = &lv_font_montserrat_12;
static const lv_font_t *font_medium = &lv_font_montserrat_14;
static const lv_font_t *font_large = &lv_font_montserrat_18;
static const lv_font_t *font_extraSymbol = &symbol_extra_18;

// * Extra symbols
#define MY_HEADPHONE_SYMBOL "\xEF\x80\xA5"


#endif