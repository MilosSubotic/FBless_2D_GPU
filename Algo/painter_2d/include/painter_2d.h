
#ifndef PAINTER_2D_H
#define PAINTER_2D_H

///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////

void init_renderer(int renderer);

void clear();

void paint_rect(
	uint16_t x,
	uint16_t y,
	uint16_t w,
	uint16_t h,
	uint8_t r,
	uint8_t g,
	uint8_t b
);

void paint_rect_transp(
	uint16_t x,
	uint16_t y,
	uint16_t w,
	uint16_t h,
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t a
);

void flush();

///////////////////////////////////////////////////////////////////////////////

#endif // PAINTER_2D_H
