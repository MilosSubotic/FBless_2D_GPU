
///////////////////////////////////////////////////////////////////////////////

#include "painter_2d.h"
#include "renderers.h"

///////////////////////////////////////////////////////////////////////////////

Rect rect_list[RECT_LIST_LEN];
uint8_t rect_list_end = 0;

///////////////////////////////////////////////////////////////////////////////

void clear() {
	rect_list_end = 0;
}

void paint_rect(
	uint16_t x,
	uint16_t y,
	uint16_t w,
	uint16_t h,
	uint8_t r,
	uint8_t g,
	uint8_t b
) {
	paint_rect_transp(x, y, w, h, r, g, b, 255);
}

void paint_rect_transp(
	uint16_t x,
	uint16_t y,
	uint16_t w,
	uint16_t h,
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t a
) {
	if(rect_list_end == RECT_LIST_LEN){
		// No more space.
		return;
	}

	rect_list[rect_list_end].x = x;
	rect_list[rect_list_end].y = y;
	rect_list[rect_list_end].w = w;
	rect_list[rect_list_end].h = h;
	rect_list[rect_list_end].c.r = r;
	rect_list[rect_list_end].c.g = g;
	rect_list[rect_list_end].c.b = b;
	rect_list[rect_list_end].c.a = a;
	rect_list_end++;
}

void flush(int renderer) {
	if(renderer == 0){
		basic_renderer();		
	}else if(renderer == 1){
		tile_renderer();		
	}
}

///////////////////////////////////////////////////////////////////////////////

