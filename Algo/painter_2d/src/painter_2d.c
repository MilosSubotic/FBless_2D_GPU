
///////////////////////////////////////////////////////////////////////////////

#include "painter_2d.h"
#include "common.h"

///////////////////////////////////////////////////////////////////////////////
// Pointers to SW/HW data structures.

DrawList* _draw_list = 0;
TileMat* _tile_mat = 0;

///////////////////////////////////////////////////////////////////////////////
// SW data structures.

#if SW_EN
static DrawList _sw_draw_list;
static TileMat _sw_tile_mat;
#endif

///////////////////////////////////////////////////////////////////////////////
// Other data.

static int _renderer;

///////////////////////////////////////////////////////////////////////////////

void init_renderer(int renderer) {
	_renderer = renderer;
	if(renderer <= 3){
#if SW_EN
		_draw_list = &_sw_draw_list;
		_tile_mat = &_sw_tile_mat;
#endif
	}else{
#if HW_EN
		_draw_list = 0; //TODO From xparameters.h, don't use volatile.
		_tile_mat = 0;
#endif
	}
	_draw_list->list_end = 0;
}

void clear() {
	_draw_list->list_end = 0;
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
	int e = _draw_list->list_end;
	if(e == DRAW_LIST_LEN){
		// No more space.
		return;
	}

	_draw_list->rects[e].x = x;
	_draw_list->rects[e].y = y;
	_draw_list->rects[e].w = w;
	_draw_list->rects[e].h = h;
	_draw_list->colors[e].r = r;
	_draw_list->colors[e].g = g;
	_draw_list->colors[e].b = b;
	_draw_list->colors[e].a = a;
	_draw_list->list_end++;
}

void flush() {
	if(_renderer == 0){
		basic_renderer();
	}else if(_renderer == 1){
		reverse_renderer();
	}else if(_renderer == 2){
		tile_renderer();
	}else if(_renderer == 3){
		parallel_tile_renderer();
	}else if(_renderer == 4){
		hw_tile_renderer();
	}
}

///////////////////////////////////////////////////////////////////////////////
