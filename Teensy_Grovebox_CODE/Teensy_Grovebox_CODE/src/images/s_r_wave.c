#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_S_R_WAVE
#define LV_ATTRIBUTE_IMG_S_R_WAVE
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_S_R_WAVE uint8_t s_r_wave_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x3f, 0xc0, 0x00, 0x00, 
  0x3f, 0xc0, 0x00, 0x00, 
  0x30, 0xc0, 0x00, 0x00, 
  0x30, 0xc0, 0x00, 0x00, 
  0x30, 0xc0, 0x7e, 0x00, 
  0x30, 0xc0, 0x7e, 0x00, 
  0x30, 0xf8, 0x66, 0x00, 
  0x30, 0xf8, 0x66, 0x00, 
  0x30, 0x18, 0x66, 0x00, 
  0x30, 0x18, 0x66, 0x00, 
  0x30, 0x18, 0x67, 0x80, 
  0x30, 0x18, 0x67, 0x80, 
  0x30, 0x18, 0x60, 0x00, 
  0x30, 0x18, 0x60, 0x00, 
  0x30, 0x19, 0xe0, 0x00, 
  0xf0, 0x19, 0xe0, 0x00, 
  0xf0, 0x19, 0x80, 0x00, 
  0x00, 0x1f, 0x80, 0x00, 
  0x00, 0x1f, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t s_r_wave = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 25,
  .header.h = 25,
  .data_size = 108,
  .data = s_r_wave_map,
};
