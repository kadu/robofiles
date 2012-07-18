/* rface_glcd bitmap file for GLCD library */
/* Bitmap created from rface_glcd.bmp      */
/* Date: 18 Mar 2012      */
/* Image Pixels = 8192    */
/* Image Bytes  = 1024     */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef rface_glcd_H
#define rface_glcd_H

static uint8_t rface_glcd[] PROGMEM = {
  128, // width
  64, // height

  /* page 0 (lines 0-7) */
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,
  0xc0,0x40,0x60,0x20,0x30,0x10,0x18,0x8,0x8,0x8,0xc,0x4,0x4,0x4,0x4,0x4,
  0x4,0x4,0x4,0x4,0x4,0xc,0x8,0x8,0x8,0x18,0x10,0x30,0x30,0x60,0x60,0xc0,
  0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
  /* page 1 (lines 8-15) */
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xe0,0xf0,0x78,0x1c,0xe,0x7,0x3,0x1,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x1,0x1,0x3,0xe,0x1c,0x78,0xf0,0xe0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
  /* page 2 (lines 16-23) */
  0x0,0x0,0x0,0x80,0xf0,0xfc,0x7f,0xf,0x3,0x0,0x0,0x0,0x0,0x80,0x82,0x82,
  0x81,0x81,0x81,0x83,0x83,0x82,0x2,0x6,0x6,0xc,0x18,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x18,0xc,0xc,0x6,0x2,0x82,0x83,0x83,0x81,0x81,0x81,
  0x82,0x82,0x80,0x0,0x0,0x0,0x0,0x3,0x7,0x3f,0xfc,0xf0,0xc0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
  /* page 3 (lines 24-31) */
  0x0,0x0,0xe0,0xff,0xff,0x3,0x0,0x0,0x0,0x0,0x6,0x6,0xf,0x19,0x19,0x31,
  0x33,0x37,0x3c,0x3c,0x37,0x33,0x31,0x13,0x1e,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1e,0x13,0x31,0x31,0x33,0x34,0x3c,0x37,0x37,
  0x31,0x11,0x19,0x9,0xf,0x6,0x0,0x0,0x0,0x0,0x1,0x7f,0xff,0xf8,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
  /* page 4 (lines 32-39) */
  0x0,0x0,0x3,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x38,0x60,0xc0,0xc0,0xc0,0x80,0x0,
  0x0,0x80,0xc0,0x40,0x40,0x70,0x38,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0xfe,0xff,0xf,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
  /* page 5 (lines 40-47) */
  0x0,0x0,0x0,0x0,0x7,0x1f,0x7e,0xf0,0xc0,0x80,0x0,0x0,0x0,0x0,0x0,0x10,
  0x7c,0x1e,0x7,0x47,0x44,0xc8,0xc8,0x80,0x80,0x0,0x20,0x20,0x20,0x20,0x27,0x67,
  0x67,0x63,0x20,0x20,0x20,0x20,0x20,0x80,0x80,0x80,0xc0,0xc8,0x44,0x7,0x3f,0x3c,
  0x10,0x0,0x0,0x0,0x0,0x0,0x80,0xc0,0xf0,0xfc,0x3f,0xf,0x1,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
  /* page 6 (lines 48-55) */
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x3,0x7,0xf,0x1c,0x38,0x70,0xe0,0xe0,
  0xc0,0x80,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x3,0x3,0x7,0x7,0x6,0xe,0xe,
  0xe,0xe,0xe,0x7,0x7,0x7,0x3,0x3,0x1,0x0,0x0,0x0,0x0,0x0,0x80,0xc0,
  0xc0,0xe0,0x70,0x78,0x3c,0x1e,0x7,0x7,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
  /* page 7 (lines 56-63) */
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,
  0x1,0x3,0x3,0x7,0x7,0xe,0xe,0x1c,0x1c,0x1c,0x18,0x18,0x18,0x38,0x38,0x38,
  0x38,0x38,0x38,0x18,0x18,0x18,0x1c,0x1c,0x1c,0xe,0xe,0x6,0x7,0x7,0x3,0x1,
  0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
};
#endif