#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_REV_SAW_WAVE
#define LV_ATTRIBUTE_IMG_REV_SAW_WAVE
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_REV_SAW_WAVE uint8_t rev_saw_wave_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x40, 0x08, 0x00, 0x00, 
  0x60, 0x0c, 0x00, 0x00, 
  0x70, 0x0e, 0x00, 0x00, 
  0x7c, 0x0f, 0x00, 0x00, 
  0x7c, 0x0f, 0x80, 0x00, 
  0x6e, 0x0d, 0xc0, 0x00, 
  0x67, 0x0c, 0xe0, 0x00, 
  0x63, 0x8c, 0x70, 0x00, 
  0x61, 0xcc, 0x38, 0x00, 
  0x60, 0xec, 0x1c, 0x00, 
  0x60, 0x7c, 0x0e, 0x00, 
  0xe0, 0x3c, 0x07, 0x00, 
  0xe0, 0x1c, 0x03, 0x80, 
  0x60, 0x0c, 0x01, 0x80, 
  0x20, 0x04, 0x00, 0x80, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t rev_saw_wave = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 25,
  .header.h = 25,
  .data_size = 108,
  .data = rev_saw_wave_map,
};
