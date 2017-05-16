
#ifndef COMMON_H
#define COMMON_H

///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

typedef unsigned int uint;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

///////////////////////////////////////////////////////////////////////////////

#define SW_EN 1
#define HW_EN 1

///////////////////////////////////////////////////////////////////////////////

typedef struct {
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} Color;

typedef struct {
	// Upper-left corner is (0, 0).
	u16 x;
	u16 y;
	u16 w;
	u16 h;
} Rect;

#define DRAW_LIST_LEN 512
typedef struct {
	Rect rects[DRAW_LIST_LEN];
	Color colors[DRAW_LIST_LEN];
	u16 list_end;
} DrawList;

extern DrawList* _draw_list;

///////////////////////////////////////////////////////////////////////////////

#define WIDTH 640
#define HEIGHT 480

///////////////////////////////////////////////////////////////////////////////

#define TILE_BITS 5
#define TILE_LIST_LEN 7

#define TILE_MAT_WIDTH (WIDTH >> TILE_BITS)
#define TILE_MAT_HEIGHT (HEIGHT >> TILE_BITS)

typedef struct {
	u8 list_end;
	u8 list[TILE_LIST_LEN]; // Indices to draw list.
} TileList;
typedef struct {
	TileList mat[TILE_MAT_WIDTH][TILE_MAT_HEIGHT];
} TileMat;
extern TileMat* _tile_mat;

///////////////////////////////////////////////////////////////////////////////

void basic_renderer();
void reverse_renderer();
void tile_renderer();

///////////////////////////////////////////////////////////////////////////////

#endif // COMMON_H
