
///////////////////////////////////////////////////////////////////////////////

#include "common.h"

#include <stdlib.h>
#include "ppm.h"

///////////////////////////////////////////////////////////////////////////////

void tile_renderer() {
	// TODO Move to separate file.
	// Partitioning.
	for(u16 ty = 0; ty < TILE_MAT_HEIGHT; ty++){
		for(u16 tx = 0; tx < TILE_MAT_WIDTH; tx++){
			_tile_mat->mat[tx][ty].list_end = 0;
		}
	}

	for(i16 i = _draw_list->list_end-1; i >= 0; i--){
		Rect r = _draw_list->rects[i];
		u16 tx_beg = r.x >> TILE_BITS;
		u16 ty_beg = r.y >> TILE_BITS;
		u16 tx_end = (r.x + r.w) >> TILE_BITS;
		u16 ty_end = (r.y + r.h) >> TILE_BITS;
	
		for(u16 ty = ty_beg; ty <= ty_end; ty++){
			for(u16 tx = tx_beg; tx <= tx_end; tx++){
				TileList* tl = &_tile_mat->mat[tx][ty];
				if(tl->list_end < TILE_LIST_LEN){
					// List is not full.
					tl->list[tl->list_end++] = i;
				}
			}
		}
	}


	// Rendering.
	const int shift = 13;
	const u16 fix_one = 0x1 << shift; // 1b.13b
	const u16 half = 0x1 << (shift-1);

	u8* vga = malloc(WIDTH*HEIGHT*3);

	for(u16 y = 0; y < HEIGHT; y++){
		for(u16 x = 0; x < WIDTH; x++){
			int idx = (y*WIDTH+x)*3;
			
			u16 tx = x >> TILE_BITS;
			u16 ty = y >> TILE_BITS;
			TileList* tl = &_tile_mat->mat[tx][ty];
			
			u8 acc_r = 0;
			u8 acc_g = 0;
			u8 acc_b = 0;
			u16 weight = fix_one; // 1b.13b

			u8 ti = 0;
			i16 i;
			while(1){
				if(ti < TILE_LIST_LEN){
					if(ti == tl->list_end){
						// Tile list end reached and it is not full.
						break;
					}
					i = tl->list[ti];
					ti++;
				}else{
					// Tile list is full. Failback to draw list.
					if(i == 0){
						break;
					}
					i--;
				}

				Rect r = _draw_list->rects[i];
				if(
					r.x <= x &&
					x < r.x+r.w &&
					r.y <= y &&
					y < r.y+r.h
				){
					// Have rect over that pixel.
					Color c = _draw_list->colors[i];
	
					// Fix-point.
					u16 w = (u16)c.a << (shift - 8); // 8b.0b -> 0b.13b
					u16 iw = fix_one - w; // 1b.13b + 0b.13b = 1b.13b
					// 1b.13b*1b.13b = 1b.26b round to nearest up -> 1b.13b
					u16 m = (w*weight + half) >> shift;
					//8b.0b * 1b.13b = 8b.13b >> 13 = 8b.0b
					acc_r += m*c.r >> shift;
					acc_g += m*c.g >> shift;
					acc_b += m*c.b >> shift;
					// 1b.13b*1b.13b = 1b.26b round to nearest up -> 1b.13b
					weight = (iw*weight + half) >> shift;

					if(weight == 0){
						break;
					}
				}

			}

			vga[idx + 0] = acc_r;
			vga[idx + 1] = acc_g;
			vga[idx + 2] = acc_b;
		}
	}

	save_ppm("tile.ppm", vga, WIDTH, HEIGHT);

	free(vga);
}

///////////////////////////////////////////////////////////////////////////////
