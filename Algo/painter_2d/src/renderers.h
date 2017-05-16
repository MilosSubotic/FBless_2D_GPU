
#ifndef RENDERERS_H
#define RENDERERS_H

///////////////////////////////////////////////////////////////////////////////

#include "common.h"

///////////////////////////////////////////////////////////////////////////////

#define RECT_LIST_LEN 256
extern Rect rect_list[];
extern uint8_t rect_list_end;

///////////////////////////////////////////////////////////////////////////////

#define WIDTH 640
#define HEIGHT 480

///////////////////////////////////////////////////////////////////////////////

#define TILE_BITS 5
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

