
#ifndef RENDERERS_H
#define RENDERERS_H

///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////

#define SW_EN 1
#define HW_EN 1

///////////////////////////////////////////////////////////////////////////////

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Color;

typedef struct {
	// Upper-left corner is (0, 0).
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
} Rect;

#define DRAW_LIST_LEN 256
typedef struct {
	Rect rects[DRAW_LIST_LEN];
	Color colors[DRAW_LIST_LEN];
	uint16_t list_end;
} DrawList;

extern DrawList* _draw_list;

///////////////////////////////////////////////////////////////////////////////

#define WIDTH 640
#define HEIGHT 480

///////////////////////////////////////////////////////////////////////////////

//#define TILE_BITS 5
#define TILE_BITS 3
#define TILE_LIST_LEN 4

#define TILE_MAT_WIDTH (WIDTH >> TILE_BITS)
#define TILE_MAT_HEIGHT (HEIGHT >> TILE_BITS)

typedef struct {
	uint8_t end;
	uint8_t list[TILE_LIST_LEN];
} TileList;
extern short tile_mat[TILE_MAT_WIDTH][TILE_MAT_HEIGHT];

///////////////////////////////////////////////////////////////////////////////

void basic_renderer();
void tile_renderer();

///////////////////////////////////////////////////////////////////////////////

#endif // RENDERERS_H
