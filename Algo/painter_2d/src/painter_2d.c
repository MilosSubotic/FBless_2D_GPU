
///////////////////////////////////////////////////////////////////////////////

#include "painter_2d.h"
#include "renderers.h"

///////////////////////////////////////////////////////////////////////////////

Rect rect_list[RECT_LIST_LEN];
unsigned rect_list_cur = 0;

///////////////////////////////////////////////////////////////////////////////

void clean() {
	rect_list_cur = 0;
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
	rect_list[rect_list_cur].x = x;
	rect_list[rect_list_cur].y = y;
	rect_list[rect_list_cur].w = w;
	rect_list[rect_list_cur].h = h;
	rect_list[rect_list_cur].c.r = r;
	rect_list[rect_list_cur].c.g = g;
	rect_list[rect_list_cur].c.b = b;
	rect_list[rect_list_cur].c.a = a;
	rect_list_cur++;
}

void flush(int renderer) {
	if(renderer == 0){
		basic_rederer();		
	}
}

///////////////////////////////////////////////////////////////////////////////

