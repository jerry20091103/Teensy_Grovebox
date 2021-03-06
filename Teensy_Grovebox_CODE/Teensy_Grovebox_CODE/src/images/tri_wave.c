#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_TRI_WAVE
#define LV_ATTRIBUTE_IMG_TRI_WAVE
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_TRI_WAVE uint8_t tri_wave_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x02, 0x00, 0x00, 0x00, 
  0x07, 0x00, 0x00, 0x00, 
  0x07, 0x00, 0x00, 0x00, 
  0x0d, 0x80, 0x00, 0x80, 
  0x0d, 0x80, 0x00, 0x80, 
  0x18, 0xc0, 0x01, 0x80, 
  0x18, 0xc0, 0x01, 0x80, 
  0x30, 0x60, 0x03, 0x00, 
  0x30, 0x60, 0x03, 0x00, 
  0x60, 0x30, 0x06, 0x00, 
  0x60, 0x30, 0x06, 0x00, 
  0xc0, 0x18, 0x0c, 0x00, 
  0xc0, 0x18, 0x0c, 0x00, 
  0x80, 0x0c, 0x18, 0x00, 
  0x80, 0x0c, 0x18, 0x00, 
  0x00, 0x06, 0x30, 0x00, 
  0x00, 0x06, 0x30, 0x00, 
  0x00, 0x03, 0x60, 0x00, 
  0x00, 0x03, 0x60, 0x00, 
  0x00, 0x01, 0xc0, 0x00, 
  0x00, 0x01, 0xc0, 0x00, 
  0x00, 0x00, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t tri_wave = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 25,
  .header.h = 25,
  .data_size = 108,
  .data = tri_wave_map,
};
