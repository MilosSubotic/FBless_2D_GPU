
///////////////////////////////////////////////////////////////////////////////

#include "common.h"

#include <stdlib.h>
#include "ppm.h"

#define FIX_POINT 1

///////////////////////////////////////////////////////////////////////////////

void reverse_renderer() {
#if SW_EN

#if FIX_POINT
	const int shift = 13;
	const u16 fix_one = 0x1 << shift; // 1b.13b
	const u16 half = 0x1 << (shift-1);
#endif
	
	u8* vga = malloc(WIDTH*HEIGHT*3);

	for(u16 y = 0; y < HEIGHT; y++){
		for(u16 x = 0; x < WIDTH; x++){
			int idx = (y*WIDTH+x)*3;
			u8 acc_r = 0;
			u8 acc_g = 0;
			u8 acc_b = 0;
#if FIX_POINT
			u16 weight = fix_one; // 1b.13b
#else
			float weight = 1;
#endif
			for(int i = _draw_list->list_end-1; i >= 0; i--){
				Rect r = _draw_list->rects[i];
				if(
					r.x <= x &&
					x < r.x+r.w &&
					r.y <= y &&
					y < r.y+r.h
				){
					// Have rect over that pixel.
					Color c = _draw_list->colors[i];
#if FIX_POINT					
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
#else
					float w = (float)c.a/255;
					float iw = 1-w;
					float m = weight*w;
					acc_r += m*c.r;
					acc_g += m*c.g;
					acc_b += m*c.b;
					weight *= iw;
#endif
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

	save_ppm("reverse.ppm", vga, WIDTH, HEIGHT);

	free(vga);
	
#endif
}

///////////////////////////////////////////////////////////////////////////////
