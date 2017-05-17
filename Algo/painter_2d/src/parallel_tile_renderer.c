
///////////////////////////////////////////////////////////////////////////////

#include "common.h"

#include <stdbool.h>

#include <stdlib.h>
#include "ppm.h"

///////////////////////////////////////////////////////////////////////////////

void parallel_tile_renderer() {
#if SW_EN

	// Partitioning.
	tile_partitioning();


	// Rendering.
	const int shift = 13;
	const u16 fix_one = 0x1 << shift; // 1b.13b
	const u16 half = 0x1 << (shift-1);

	u8* vga = malloc(WIDTH*HEIGHT*3);

	for(u16 y = 0; y < HEIGHT; y++){
		u16 ty = y >> TILE_BITS;
		
		for(u16 tx = 0; tx < (WIDTH>>TILE_BITS); tx++){
			TileList* tl = &_tile_mat->mat[tx][ty];
			
			u8 acc_r[TILE_LINE];
			u8 acc_g[TILE_LINE];
			u8 acc_b[TILE_LINE];
			u16 weight[TILE_LINE];
			for(u16 ix = 0; ix < TILE_LINE; ix++){
				acc_r[ix] = 0;
				acc_g[ix] = 0;
				acc_b[ix] = 0;
				weight[ix] = fix_one; // 1b.13b
			}

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
				// Have rect over that pixel.
				Color c = _draw_list->colors[i];
				
				for(u16 ix = 0; ix < TILE_LINE; ix++){
					u16 x = (tx<<TILE_BITS) | ix;
					if(
						r.x <= x &&
						x < r.x+r.w &&
						r.y <= y &&
						y < r.y+r.h
					){
						// Fix-point.
						u16 w = (u16)c.a << (shift - 8); // 8b.0b -> 0b.13b
						u16 iw = fix_one - w; // 1b.13b + 0b.13b = 1b.13b
						// 1b.13b*1b.13b = 1b.26b round to nearest up -> 1b.13b
						u16 m = (w*weight[ix] + half) >> shift;
						//8b.0b * 1b.13b = 8b.13b >> 13 = 8b.0b
						acc_r[ix] += m*c.r >> shift;
						acc_g[ix] += m*c.g >> shift;
						acc_b[ix] += m*c.b >> shift;
						// 1b.13b*1b.13b = 1b.26b round to nearest up -> 1b.13b
						weight[ix] = (iw*weight[ix] + half) >> shift;
					}
				}
				
				// Escape if all 0.
				bool all_zeros = true;
				for(u16 ix = 0; ix < TILE_LINE; ix++){
					if(weight[ix] != 0){
						all_zeros = false;
						break;
					}
				}
				if(all_zeros){
					break;
				}
			}

			for(u16 ix = 0; ix < TILE_LINE; ix++){
				u16 x = (tx<<TILE_BITS) | ix;
				int idx = (y*WIDTH+x)*3;
				vga[idx + 0] = acc_r[ix];
				vga[idx + 1] = acc_g[ix];
				vga[idx + 2] = acc_b[ix];
			}
		}
	}

	save_ppm("parallel_tile.ppm", vga, WIDTH, HEIGHT);

	free(vga);
	
#endif
}

///////////////////////////////////////////////////////////////////////////////
