
///////////////////////////////////////////////////////////////////////////////

#include "common.h"

#include <stdlib.h>
#include "ppm.h"

///////////////////////////////////////////////////////////////////////////////

void basic_renderer() {
	uint8_t* vga = malloc(WIDTH*HEIGHT*3);

	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			int idx = (y*WIDTH+x)*3;
			Color c_acc = {0, 0, 0, 0};
			for(int i = 0; i < _draw_list->list_end; i++){
				Rect r = _draw_list->rects[i];
				if(
					r.x <= x &&
					x < r.x+r.w &&
					r.y <= y &&
					y < r.y+r.h
				){
					// Have rect over that pixel.
					Color c = _draw_list->colors[i];
					float new = (float)c.a/255;
					float old = 1-new;
					c_acc.r = c_acc.r*old + c.r*new;
					c_acc.g = c_acc.g*old + c.g*new;
					c_acc.b = c_acc.b*old + c.b*new;
					
					//TODO Fix-point.
				}
			}
			vga[idx + 0] = c_acc.r;
			vga[idx + 1] = c_acc.g;
			vga[idx + 2] = c_acc.b;
		}
	}

	save_ppm("basic.ppm", vga, WIDTH, HEIGHT);

	free(vga);
}

///////////////////////////////////////////////////////////////////////////////
