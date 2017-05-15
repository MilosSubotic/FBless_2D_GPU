
///////////////////////////////////////////////////////////////////////////////

#include "renderers.h"

#include <stdlib.h>
#include "ppm.h"

///////////////////////////////////////////////////////////////////////////////

void basic_rederer() {
	uint8_t* vga = malloc(WIDTH*HEIGHT*3);

	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			int idx = (y*WIDTH+x)*3;
			Color c = {0, 0, 0, 0};
			for(int i = 0; i < rect_list_end; i++){
				Rect r = rect_list[i];
				if(
					r.x <= x &&
					x < r.x+r.w &&
					r.y <= y &&
					y < r.y+r.h
				){
					// Have rect over that pixel.
					float new = (float)r.c.a/255;
					float old = 1-new;
					c.r = c.r*old + r.c.r*new;
					c.g = c.g*old + r.c.g*new;
					c.b = c.b*old + r.c.b*new;
				}
			}
			vga[idx + 0] = c.r;
			vga[idx + 1] = c.g;
			vga[idx + 2] = c.b;
		}
	}

	save_ppm("basic.ppm", vga, WIDTH, HEIGHT);

	free(vga);
}

///////////////////////////////////////////////////////////////////////////////

